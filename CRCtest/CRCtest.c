#include "HT66F70A.h"
#include "math.h"
unsigned char crc;
unsigned char a = 0x55;
unsigned char b = 0x14;
unsigned char c = 0x64;
unsigned char sum;
unsigned char Tran(unsigned a,unsigned b,unsigned c);
void main()
{
	Tran(a,b,c);
}
unsigned char Tran(unsigned a,unsigned b,unsigned c){
	sum = a+b+c;
	crc = ~sum;
	crc++;
}