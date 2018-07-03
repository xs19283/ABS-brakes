// PROGRAM	: 3-1.c									2013.1025
/* FUNCTION	: LED Scanning Demo Program for 
				  C-Language Introduction			By Steven*/
#include <HT66F70A.h>
void Delay100us(unsigned short);					//函式原型宣告
void main()
{	unsigned char i,j;	
	_wdtc=0b10101111;								//關閉看們狗計時器
	_pdc=0x00;										//規劃PC為輸出屬性
	_pd=0xFE;										//設定PC初值
	while(1)
	{	
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
}	
void Delay100us(unsigned short del)					//延遲del*200指令週期
{	
	unsigned short i,j;								//@fSYS=8MH,延遲del*100us
	for(i=0;i<del;i++)
		for(j=0;j<=25;j++) GCC_NOP();
}