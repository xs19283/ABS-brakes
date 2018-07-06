// PROGRAM	: 3-1.c									2013.1025
/* FUNCTION	: LED Scanning Demo Program for 
				  C-Language Introduction			By Steven*/
#define		SW0		   	_pe0		//PE0
#define		SW0C		_pec0		//PEC0
#define		SW0PU	 	_pepu0		//PEPU0
#include <HT66F70A.h>

void Delay100us(unsigned short);
void LED(void);
void main()
{	
	int i=0;
	_pdc=0x00;
	_wdtc=0b10101111;							//關閉看們狗計時器
	SW0C=1; SW0PU=1;                      		//規劃SW0接腳為輸入並啟用提升電阻
	while(1)
	{	
		if(SW0) _pd=0b01010101;						//延遲 120 mSec; 		            	//判斷彈跳是否結束
		else _pd=0b11111111;
	}
}

//////////////
//時間控制
//////////////
void Delay100us(unsigned short del)					//延遲del*200指令週期
{	
	unsigned short i,j;								//@fSYS=8MH,延遲del*100us
	for(i=0;i<del;i++)
		for(j=0;j<=25;j++) GCC_NOP();
}

//////////////
//LED控制
//////////////
void LED()
{
	unsigned char i,j;
	for(j=0;j<7;j++)	
		{	
			Delay100us(1000);
			_pd=_pd<<1|0x01;						//PG左移並補1至LSB
		}
		do	
		{	
			Delay100us(1000); _pd=_pd>>1|0x80;		//PG右移並補1至MSB
		}while(_pd!=0b11111110);
}