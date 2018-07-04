#include <HT66F70A.h>

#define SDO _pa5	//以盛群為基準
#define SDA _pa6	//以盛群為基準
#define SCK _pa7
#define CS  _pb5

#define SDOC _pac5	//以盛群為基準
#define SDAC _pac6
#define SCKC _pac7
#define CSC  _pbc5

#define SDOPU _papu5	//盛群為基準
#define SDAPU _papu6
#define SCKPU _papu7
#define CSPU  _pbpu5

void Master(unsigned short);
void Delay100us(short);	

void main()
{
	_pa5s0=1;
	_pa5s1=0;
	_pa5s2=0;
	_pa5s3=0;
	
	_pa6s0=0;
	_pa6s1=1;
	_pa6s2=0;
	_pa6s3=0;
	
	_pa7s0=0;
	_pa7s1=1;
	_pa7s2=0;
	_pa7s3=0;
	
	_pb5s0=1;
	_pb5s1=0;
	_pb5s2=0;
	_pb5s3=0;
	
	
}

void Master(unsigned short Data)
{	unsigned short temp=0b00000001;
	do
	{	
		SDO=Data & temp;						//Set SDO State
		SCK=1; Delay100us(3); SCK=0; //Generate SCK Clock
		temp<<=1;									   //Next Bit
	} while (temp!=0);
}

void Delay100us(short del)						//延遲del*200指令週期
{	short i,j;									//@fSYS=8MH,延遲del*100us
	for(i=0;i<del;i++)
		for(j=0;j<=25;j++) GCC_NOP();
}	