#include "HT66F70A.h"
#include "TM.h"
 
//專用于模組串口的定時器
void TM0_INIT(void)
{
	//TXD RXD初始化
	_pcc2 = 0;
	_pcc3 = 1;
	_pcpu3 = 1;
	_pcpu2 = 1;
	
    _tm0c0=0x10;//計數器暫停運行
    _tm0c1=0xc1;//清0               
    _tm0al=0x41;//buad rate 9600
    _tm0ah=0x03; 
 
       
    _t0ae = 1;
    _t0af = 0;
    _t0on = 0;
    _emi = 1;
    _mf0e = 1;
    _mf0f = 0;
	}
 
 
