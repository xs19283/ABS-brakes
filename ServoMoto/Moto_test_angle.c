#include "HT66F70A.h"
typedef	unsigned char	u8;
typedef	char			s8;
typedef	unsigned short	u16;
typedef	short			s16;
typedef	unsigned long	u32;
typedef	long			s32;

#define led _pb6
#define ledc _pbc6
#define led2 _pb7
#define ledc2 _pbc7

#define  SW_P0			_pe0
#define	 SW_P1 		    _pe1
#define  SW_P0C			_pec0
#define	 SW_P1C			_pec1
#define  SW_P0PU		_pepu0
#define	 SW_P1PU		_pepu1
#define  SW_P3		_pe3
#define  SW_P3C		_pec3
#define  SW_P3PU		_pepu3

s16 angle,temp,Index,auto1;

void Moto_Set();	  //���F�}��]�w
void Moto_C(u8 angle);//���F����]�w

void Delay100us(u16);
void delay_ms(unsigned char);
void main()
{
	auto1=0;
	_wdtc=0xaf; 
	ledc=0; ledc2=0;
	Moto_Set();
	Moto_C(79);
	while(1)
	{
		
		temp=Index*20+1000;
		_tm2al=temp%256;
		_tm2ah=temp/256;
		temp>>=1;
		delay_ms(50);						//����120ms
		while(1)
		{	
			_t2on=0;
			while(!SW_P0)
			{	
				_t2on=1;
				angle=Index;
				//Index=101;
				Index=72;		//�Y���U���W��,���л��W(�W��200) 
				break;   	
			}
		}
	}
}

void Moto_Set(){			//���F�]�w
	SW_P0C=1; SW_P0PU=1;	//�W������}�쬰��J�ݩʨñҥδ��ɹq��
	SW_P1C=1; SW_P1PU=1;
	_pds2=0x01;				//�]�wPD4��TP2�\��
	_tm2c0=0b00000000;
	_tm2c1=0b10101000;
	_tm2rp=160;
	_t2on=1;
}

void Moto_C(u8 angle){
		temp=Index*20+1000;
		_tm2al=temp%256;
		_tm2ah=temp/256;
		temp>>=1;
		Index=angle;
}

void Delay100us(u16 del){
	u16 a,k;;
	for(a=0;a<del;a++)
		for(k=0;k<=25;k++)
			GCC_NOP();
}

void delay_ms(unsigned char del){	
	unsigned char a;
	for(a=0;a<del;a++) 
		GCC_DELAY(2000);		//���ب禡�A����2000���O�g��
}