#include <HT66F70A.h>
#include "MyType.h"	
#define	 R_PinC	_pdc5     //PDC.5
#define	 R_Pin	_pd5      //PD.5
#define	Period  100									//PWM周期常數
u8	PCnt,R,RCnt;

DEFINE_ISR(ISR_STM,0x14)
{	
	if(PCnt--==0)									//判斷PWM周期是否已結束
	{	
		PCnt=Period;
		RCnt=R; 	                 	            //是，還原所有值
		R_Pin=(R==0)? 0 : 1;						//依Duty設定腳位初始狀態
	}
	else
	{	
		if(RCnt!=0) 
		{
		  RCnt--; 
		}
		else
		{ 
		  R_Pin = 0; 
		}			//判斷Duty若是結束設定接腳為0
	}
	_t2af=0;				  						//清除T2AF旗標
}

