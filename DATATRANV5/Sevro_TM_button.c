#include "HT66F70A.h"
#include <stdlib.h>
#include <math.h>

#define fsys 8000000                             //系統頻率8MHz
#define	_TX			_pc1
#define	_TXC		_pcc1			
#define	fSYS		8000000	
#define	BaudRate	9600	
#define	BITC		(fSYS/BaudRate)					//Bit Interval Time Constant

typedef	unsigned char	u8;
typedef	char			s8;
typedef	unsigned short	u16;
typedef	short			s16;
typedef	unsigned long	u32;
typedef	long			s32;
u8 AxisXH;
u8 AxisXL;
u8 SendXH;
u8 SendXL;
u16 AxisX;
u8 Head;
u8 HallHead;
u8 Axcount=0;
u8 Hacount=0;

unsigned char AXCRC,AXSUM;
unsigned char HallCRC,HallSUM;
u8 HallData = 0;
u8 HallCount = 0;
u16 XArr[5],ADx,XArrAvg=0;

#define led _pb6
#define ledc _pbc6
#define led2 _pb7
#define ledc2 _pbc7

#define  SW_P0			_pe0
#define	 SW_P1 		    _pe1
#define  SW_P0C			_pec0
#define	 SW_P1C			_pec1
#define  SW_P0PU		_pepu0
#define	 SW_P1PU		_pepu1		

u8 SEC,R1sec,AD10ms,Hall200ms,Whell,Whell100ms,i;
s16 temp,Index,auto1;
u16 XArrSort[5],tempx;
u16 SendX = 0;
//函式
void TM_Set();  	  //時間中斷設定
void Interrupt_Set(); //外部中斷設定
void Moto_Set();	  //馬達腳位設定
void Moto_C(u8 angle);//馬達控制設定
void AD_Set();		  //AD轉換設定
void Delay100us(u16);
void delay_ms(unsigned char);
void UARTTxData(u8);
void TranHall();
void TranAxis();
void XArrayPut();
void AxisCal();
void PutValueArray(u16[]);
void ShiftRightArray(u16[]);
void VariancePulsByLoad(u16[]);

void main()
{	
	_TX=1; _TXC=0;  //_TX為輸出模式(輸出Hi)		
    _wdtc = 0xab;   //關閉看門狗
	Head = 3;
	HallHead = 85;
	//ledc=0;
	_wdtc = 0xab; 
	AD10ms=1; Whell=0; Whell100ms=50;
	TM_Set();
	Interrupt_Set();
	Moto_Set();
	AD_Set();
	_emi=1;								//啟動中斷
	PutValueArray(XArr);
	Moto_C(107);
	while(1)
	{	
		//AxisCal();
		ShiftRightArray(XArr);
		qsort(XArrSort, 5, sizeof(u16));
		VariancePulsByLoad(XArrSort);
		TranAxis();
		TranHall();
		Moto_C(107);
		if(_pc5 == 1 && SendX >= 80)
		{
			//if()
			//{				
				while(SendX >= 60)
				{
					if(HallData <= 2)
					{
						Moto_C(80);
						delay_ms(300);
						//Moto_C(90);
						//delay_ms(30);
					}else
					{
						Moto_C(90);
					}
					AxisCal();
					ShiftRightArray(XArr);
					qsort(XArrSort, 5, sizeof(u16));
					VariancePulsByLoad(XArrSort);
					TranAxis();
					TranHall();
				}
			//}	
		}
	}
}

void TM_Set(){
	_tm4c0=0b00100000;
	_tm4c1=0b11000001;
	_tm4al=5000%256; _tm4ah=5000/256;
	_tm0c0=0b00010000;	//For Bit Rate,fINT=fSYS
	_tm0c1=0b11000001;	//T/C, TM0A Match Clear
	_tm2c0=0; _tm2c1=0b00110001;	//STM:比對吻合輸出模式,CCRA吻合清除
	_mf4e=1; _t4ae=1;
	_t4on=1;
	SEC=0; R1sec=100; AD10ms=1; Hall200ms=20;
}

void Interrupt_Set(){
	_pac3=1; _papu3=1;
	_pcc5=1;
	_integ=0b00000010; //INT0負緣處發、INT1正緣處發 00000110
	_int0e=1;
	_ifs0=0x00;
	//_int1e=1;
	//_ifs1=0x00;
}

void Moto_Set(){			//馬達設定
	SW_P0C=1; SW_P0PU=1;	//規劃按鍵腳位為輸入屬性並啟用提升電阻
	SW_P1C=1; SW_P1PU=1;
	_pds2=0x01;				//設定PD4為TP2功能
	_tm2c0=0b00000000;
	_tm2c1=0b10101000;
	_tm2rp=160;
	_t2on=1;
}

void Moto_C(u8 angle){
		temp=Index*20+1000;
		_tm2al=temp%256;
		_tm2ah=temp/256;
		temp>>=1;
		Index=angle;
}

void AD_Set(){
	_adcr0 = 0b00000100;							//選擇AN4做轉換,設定轉換結果存放格式
	_adcr1 = 0b01100110;							//A/D Clock=fSYS/64,VREFS=0
	_pas2 = 0b00000011;   							//設定PA4更改AN4做AD通道
}

DEFINE_ISR(button_up,0x04){		//INT0 PA3中斷程式
	HallCount++;
	_int0f = 0;	
}

/*
DEFINE_ISR(Button_Down,0x08)
{	//INT1 PA4中斷程式 
	if(SendX >= 150)
	{
		while(HallData < 4)
		{
			Moto_C(107);
			delay_ms(100);
			Moto_C(135);
			delay_ms(100);
			//led2=1;
		}
	}
	_int1f = 0;
}*/

DEFINE_ISR(ISR_STM,0x38){		//時間中斷程式
	if(--AD10ms==0){
		AD10ms=1;
		_start=1; _start=0;						//起始ADC轉換
		GCC_NOP();
		AxisXH = _adrh;
		AxisXL = _adrl;
		AxisCal();
	}
	if(--Hall200ms==0){
		HallData = HallCount;
		HallCount = 0;
		Hall200ms=20;
	}
	/*if(--R1sec==0){	
		R1sec=100;
		led=1;

		if(++SEC==5)
		{
			SEC=0;
			led=0;
			
		}
	}*/
	_t4af=0;
}

void Delay100us(u16 del){
	u16 a,k;;
	for(a=0;a<del;a++)
		for(k=0;k<=25;k++)
			GCC_NOP();
}

void delay_ms(unsigned char del){	
	unsigned char a;
	for(a=0;a<del;a++) 
		GCC_DELAY(2000);		//內建函式，延遲2000指令週期
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

void TranAxis(void)
{
	SendXH = (u8)((SendX >> 8) & 0Xff);
	SendXL = (u8)(SendX & 0xFF);
	//AXSUM = AxisX + Head;
	//AXCRC = ~AXSUM;
	//AXCRC++;
	AXCRC = Head+SendXH;
	UARTTxData(Head);
	UARTTxData(SendXH);
	UARTTxData(SendXL);
	UARTTxData(Axcount);
	UARTTxData(AXCRC);
}

void TranHall(void)
{
	//u8 HalldataH,HalldataL;
	//HalldataH = (u8)((HallData>>8) & 0xff);
	//HalldataL = (u8)(HallData & 0xff);
	//HallSUM = HallData + HallHead;
	//HallCRC = ~HallSUM + Head;   ///等著改輪數數值
	//HallCRC++;
	HallCRC = HallHead+HallData;
	UARTTxData(HallHead);
	UARTTxData(HallData);
	UARTTxData(Axcount);
	UARTTxData(Hacount);
	UARTTxData(HallCRC);
}

void ShiftRightArray(u16 Array[])
{
	for(i=5;i>0;i--)
	{
		XArr[i]=XArr[i-1];
	}
 	XArr[0] = AxisX;
 	for(i = 0; i < 5; i++)
	{
		XArrSort[i] = Array[i];
	}
}

void AxisCal()
{
	AxisX = (u16)(AxisXH << 8);
	AxisX += AxisXL;
}

void PutValueArray(u16 Array[])
{
	for(i = 0; i < 5; i++)
	{
		AxisCal();
		Array[i] = AxisX;
	}
}

void VariancePulsByLoad(u16 SortArray[])
{
	u16 Sum1, Sum2, Total;
	
	Sum1 = pow(SortArray[1] - SortArray[2], 2);
	Sum2 = pow(SortArray[3] - SortArray[2], 2);
	Total = sqrt(Sum1 + Sum2);
	SendX = Total;
}
