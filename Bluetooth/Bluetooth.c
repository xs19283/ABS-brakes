#include "HT66F70A.h"
#include "Interrupt.h"
#include "TM.h"
#include "UART.h"
#include "String.h"
 
 
//全域變數
extern char buff[num];
extern char Buff[32];
extern unsigned int count;
 
//函式
void delay1s(void);
 
 
//主程序入口
void main()
{
    //TO DO
    _wdtc = 0xab;//看門狗禁止
    unsigned char key;
    UART_INIT();
    while(1){
    Send("85");
    delay1s();
    }
    /*
    Receive();
    Send_Array();
    Receive_if(Buff);
    //Send_num(8,Buff);
    Send(Buff);	
    */
}
 
void delay1s(void)   //誤差 1us
{
    unsigned char a,b,c,n;
    for(c=205;c>0;c--)
        for(b=171;b>0;b--)
            for(a=8;a>0;a--);
    for(n=1;n>0;n--);
}
	
 
