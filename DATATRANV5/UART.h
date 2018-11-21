#ifndef _UART_H_
#define _UART_H_
 
//定義TXD RXD
#define TXD _pc2
#define RXD _pc3
//定義接收字串長度
#define num 16
 
void UART_INIT(void);
void Waitflag();
void WByte(unsigned char input);
unsigned char RByte(void);
void Send(char *buf);//發送
void Send_num(unsigned int s,char *buf);//發送s個字串
void Send_Array(void);//發送緩衝區
void Receive(void);//送num字元到緩衝區
void Receive_num(unsigned int s,char *buf);//接收s個字元
void Receive_if(char *buf);//以'\n'結尾的條件接收
 
#endif