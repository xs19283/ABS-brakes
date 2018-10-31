#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_
#endif
 
#define ISR_TMR0//定義TM0 TM2
 
void __attribute((interrupt(0x14))) ISR_tmr0_tmr2(void)//TM0和TM2中斷
{
	//定義ISR_TMR0
	#ifdef ISR_TMR0
	extern volatile unsigned int flag;
	_emi = 0;
	_t0af = 0;
	flag = 1;
	_emi = 1;
	//定義ISR_TMR2
	#else
	_emi = 0;
	_t2af = 0;
	_emi = 1;
	#endif
	
}
