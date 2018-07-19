#define Seven _pc
#define Sevenc _pcc
#define SW _pd4
#define SWc _pdc4
#define SW2 _pd6
#define SW2c _pdc6

const unsigned char Segnum[] ={0b10000000,0b11111001,0b01010100,0b01110000,0b00111001,0b00110010,0b00010011,0b10111000,0b00010000,0b00111000};
int num = 0;
void delay_ms(unsigned short);
void showLED(int,int);

int n = 0;
int j = 0;
int count = 0;

int state = 0;
int bool =0;

void initalize()
{
/*	SW = 1;
	SWc = 1;      //腳位輸入
	
	SW2 = 1;
	SW2c = 1;      //腳位輸入
	
	_pd7 = 1;
	_pdc7 =0;
	
	_pg = 0;        //LOW
	_pgc = 0;         //輸出
	_pc = 1;          //HIGH
	_pcc = 0;         //輸出
*/	
	_RXC=1; _integ=0x02; _int0e=1;	//INT0負源觸發
	_TX=1; _TXC=0;					//_TX為輸出模式(輸出Hi)		
    _wdtc = 0xab;   //關閉看門狗
	_scomen = 0;    //關閉LCD介面
	_tm0c0=0b00010000;	//For Bit Rate,fINT=fSYS
	_tm0c1=0b11000001;	//T/C, TM0A Match Clear	    
	_tm2c0=0; _tm2c1=0b00110001;	//STM:比對吻合輸出模式,CCRA吻合清除
	_emi=1;	         //開啟中斷
 	b_RX=0; 

 	///
 	_tm4c0=0b00000000;					//fINT=fSYS/16 -> 500KHz  /64 = 125KHZ
	_tm4c1=0b11000001;					//Timer/Counter模式,A吻合清除
	_tm4al=50000; _tm4ah=50000>>8;	//50000x2us=100ms	
	
	_t4ae=1; _mf4e=1; _emi=1;			//中斷致能
	_t4on=0;							//關閉TM4開始計數
	//

 	R_Pin=1 ;
	R_PinC=0;
 	_mf0e=1; _t2ae=1; 								//致能MF0、T2A中斷
	_tm2c0=0x00;									//fINT=fSYS/4
	_tm2c1=0b11000001;              				//Timer/Counter,TM2A吻合清除
	_tm2al=50%256;_tm2ah=50/256;   				//設定TM2A=200
	_t2af=0; _mf0f=0; _emi=1;    					//清除中斷旗標並致能中斷
	PCnt=Period; _t2on=1;							//設定PWM周期並開始計數
//	R = 15;

}