#include "UART.h"
#include "HT66F70A.h"
#include "TM.h"
#include "String.h"
 
//全域變數
volatile unsigned int flag = 0;
char buff[num];
char Buff[32] = "\0";
unsigned int count = 0;
 
 
void UART_INIT(void)
{
  TM0_INIT();      
}
 
void Waitflag(void)
{
	while (!flag);
	flag=0;//計時器flag
}
 
 
void WByte(unsigned char input)
{
 
    unsigned char i=8;
    TXD=0;
    _t0on=1; //開始計時
    Waitflag();
    while(i--)
    {
        TXD=input & 0x01;         
        input >>= 1;
        Waitflag();
    }
    TXD=1;
    Waitflag();
    _t0on = 0;
        
}
 
void Send(char *buf)
{
	while(*buf != '\0')
	{
		WByte(*buf);
		buf++;
	}
}
 
void Send_num(unsigned int s,char *buf)
{
	while(s--)
	{
		WByte(*buf);
		buf++;
	}
}
 
	
void Send_Array(void)
{
	unsigned int i;
	for(i = 0;i < num;i++)
    WByte(buff[i]);		
}
 
unsigned char RByte(void)
{
    unsigned char receive;
    unsigned char i=8;
    while(RXD);
    _t0on=1;        //開始計時
    Waitflag();
    while(i--)
    {
        receive >>= 1;
        if(RXD)
        receive |= 0x80;
        Waitflag();
    }
    _t0on = 0;
    return receive;
}
 
void Receive(void)
{
    for(count = 0;count < num;count++)
    {		
	    
	    buff[count] = RByte();
	}
}
 
void Receive_num(unsigned int s,char *buf)
{
	while(s--)
	{
	*buf = RByte();
	buf++;
	}
}
 
void Receive_if(char *buf)
{
	char get;
	while(1)
	{
		get = RByte();
		if(get == '\n')
		break;
		else
		{
	    *buf = get;
	    buf++;
		}
	}
}