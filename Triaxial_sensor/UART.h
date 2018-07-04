#include "HT66F70A.h"
#include "MyType.h"
#define fsys 8000000                             //系統頻率8MHz
#define	_TX			_pa1
#define	_TXC		_pac1
#define	_RX			_pa3
#define	_RXC		_pac3			
#define	fSYS		8000000	
#define	BaudRate	9600	
#define	BITC		(fSYS/BaudRate)					//Bit Interval Time Constant
void UARTTxData(u8);
//void delay_ms(u16);
volatile unsigned int Volt;
volatile u8 ADH_Byte;
volatile u8 ADL_Byte;
volatile u8 buff;
volatile u8	RxData; 
volatile _Bool b_RX;

DEFINE_ISR(ISR_ExtINT0,0x04)
{	u8 temp=0b00000001;
	_tm0al=(BITC/2)%256; _tm0ah=(BITC/2)/256;	//0.5T
	_t0on=1;
	_t0af=0;
	RxData=0;
	while(!_t0af)			
	_tm0al=BITC%256; _tm0ah=BITC/256;			//等待0.5T
	_t0af=0;	                              	//T
	do 
	{	while(!_t0af);								//等待1T時間
		_t0af=0;
		if(_RX==1) RxData|=temp;					//擷取資料
		temp<<=1;									//RxData左移
	} while (temp);									//若temp不為0接收下一位元
	b_RX=1;											//設定接收完成旗標
	while(!_t0af);									//等待1T時間
	_t0on=0;
	_int0f=0;
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