#include <HT66F70A.h>

#define	DATA_BUS _pg
#define RS  _ph0
#define RW  _ph1
#define EN  _ph2

#define SDO _pa5	//以盛群為基準
#define SDA _pa6	//以盛群為基準
#define SCK _pa7
#define CS  _pb5

#define SDOC _pac5	//以盛群為基準
#define SDAC _pac6
#define SCKC _pac7
#define CSC  _pbc5

#define SDOPU _papu5	//盛群為基準
#define SDAPU _papu6
#define SCKPU _papu7
#define CSPU  _pbpu5

#define PAS2 _pas2	//pas 5 SDO
#define PAS3 _pas3	//pas 6 7 SDI SCL
#define PBS2 _pbs2	//pbs5 scs

void Master(unsigned short); 
void Delay100us(short);	
void _SPI_CS(unsigned short);
void _SPI_SCL(unsigned short);
unsigned char ADXL345_SPI_Read(unsigned char);
void LCD_Reset(void);
void delay_ms(unsigned char);
void LCD_Cmd(unsigned char);
void LCD_Senddata(unsigned char);

void main()
{
	volatile unsigned char i;
	_wdtc = 0xab;//關閉看門狗
	
	PAS2=0x10;  //設定各個腳位功能
	PAS3=0x22;  
	PBS2=0x10;  
	
	_phc0 = 0; _phc1 = 0; _phc2 = 0;
	_pgc = 0x00;
	
	SDOC=0; 	SDAC=1; 	SCKC=0;  //設定I/O
	SDAPU=1;	SCK=0;		CSC=0;
	CS=0;
	
	_cp0c = 0x00;	//類比比較器功能關閉
	_cp1c = 0x00;
	
	LCD_Reset();
	delay_ms(5);
	LCD_Cmd(0x80);
	
	unsigned char datax = ADXL345_SPI_Read(0x32);
	unsigned char datay = ADXL345_SPI_Read(0x34);
	datax = ADXL345_SPI_Read(0x32);
	for(i=0;i<=16;i++) //顯示Logo陣列資料
	{
		LCD_Senddata(datax);
	}
}

void Master(unsigned short Data)
{	unsigned short temp=0b00000001;
	do
	{	
		SDO=Data & temp;						//Set SDO State
		SCK=1; Delay100us(3); SCK=0; //Generate SCK Clock
		temp<<=1;									   //Next Bit
	} while (temp!=0);
}

void Delay100us(short del)						//延遲del*200指令週期
{	short i,j;									//@fSYS=8MH,延遲del*100us
	for(i=0;i<del;i++)
		for(j=0;j<=25;j++) GCC_NOP();
}	

void _SPI_CS(unsigned short isSelect)
{
    CS=isSelect;
    GCC_NOP();
}

void _SPI_SCL(unsigned short bLevel)
{
    SCK=bLevel;
    GCC_NOP();
}

unsigned char ADXL345_SPI_Read(unsigned char Address)
{
  unsigned char ReadData=0;
  unsigned char tempSDO;
  char i;
 
  _SPI_CS(0);
 
  for(i = 7; i >= 0; i-- )
  {
    // F-Edge
    _SPI_SCL(1);
    SDA = 0x1 & ((0x80 | Address) >> i);
    _SPI_SCL(0);
  }
 
  //===========================
  _SPI_SCL(1);
  //===========================
 
  for(i = 7; i >= 0; i-- )
  {
    // R-Edge
    _SPI_SCL(0);
    _SPI_SCL(1);
    tempSDO = SDO; // Read bit
 
    ReadData |= tempSDO << i;
  }
 
  _SPI_CS(1);
  return ReadData & 0xFF;
}
//---傳送命令到LCD
void LCD_Cmd(unsigned char data)
{
    DATA_BUS = data;  //命令送到BUS
    RS=0; RW=0; EN=1; //命令到LCD內 
    delay_ms(1);
    EN=0;           //禁能LCD
}
void delay_ms(unsigned char del)
{	
	unsigned char i;
	for(i=0;i<del;i++) GCC_DELAY(2000);		//內建函式，延遲2000指令週期
}
//---LCD的啟始程式  
void LCD_Reset(void)
{
    LCD_Cmd(0b00111000);//8bit傳輸,顯示2行,5*7字型
                        //bit4:DL=1,8bit傳輸,
                        //bit3:N=1,顯示2行
                        //bit2:F=0,5*7字型                        
    LCD_Cmd(0b00001100);//顯示幕ON,不顯示游標,游標不閃爍
                        //bit2:D=1,顯示幕ON
                        //bit1:C=0,不顯示游標                      
    LCD_Cmd(0b00000110);//顯示完游標右移,游標移位禁能 
                        //bit1:I/D=1,顯示完游標右移
                        //bit0:S=0,游標移位禁能                                   
    LCD_Cmd(0b00000001); //清除顯示幕
    LCD_Cmd(0b00000010); //游標回原位 
}
//---傳送資料到LCD
void LCD_Senddata(unsigned char data)
{
	DATA_BUS = data; //資料送到BUS
	RS=1; RW=0; EN=1; //資料到LCD內
	delay_ms(1);
	EN=0; //禁能LCD
}