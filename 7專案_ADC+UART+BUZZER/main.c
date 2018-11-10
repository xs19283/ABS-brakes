#include "HT66F70A.h"
#include "MyType.h"
#define fsys 8000000                             //系統頻率8MHz
#define	_TX			_pc1
#define	_TXC		_pcc1
#define	_RX			_pc3
#define	_RXC		_pcc3			
#define	fSYS		8000000	
#define	BaudRate	9600	
#define	BITC		(fSYS/BaudRate)					//Bit Interval Time Constant
u8 SUM=30;
void UARTTxData(u8);
void delay_ms(u16);
void main(void)
{
	_RXC=1;	//INT0負源觸發
	_TX=1; _TXC=0;					//_TX為輸出模式(輸出Hi)		
    _wdtc = 0xab;   //關閉看門狗
	_scomen = 0;    //關閉LCD介面
	_tm0c0=0b00010000;	//For Bit Rate,fINT=fSYS
	_tm0c1=0b11000001;	//T/C, TM0A Match Clear	    
	_tm2c0=0; _tm2c1=0b00110001;	//STM:比對吻合輸出模式,CCRA吻合清除
	_emi=1;	         //開啟中斷
	while(1)
	{
				UARTTxData(SUM);	   
				UARTTxData(20);	  
				delay_ms(1000);
				delay_ms(1000);
	}
}

void UARTTxData(u8 data)
{	u8 temp=0b00000001;
	_tm0al=BITC%256; _tm0ah=BITC/256;				//T
	_TX=0;											//起始位元
	_t0on=1;
	_t0af=0;
	while(!_t0af);									//等待T間
	_t0af=0;
	do 
	{	_TX=(data & temp)? 1 : 0 ;	  				//依資料位元設定腳位狀態
		while(!_t0af);								//等待T時間
		_t0af=0;
		temp<<=1;
	} while (temp);	
	_TX=1;											//結束位元
	while(!_t0af);
	_t0on=0;
}
void delay_ms(u16 del)
{	u16 i;
	for(i=0;i<del;i++) {GCC_DELAY(2000);}			//Delay del ms @fSYS=8MHz
}