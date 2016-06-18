#include <DS1302_EX.h>
typedef unsigned char uChar;
typedef unsigned int uInt;

sbit SCK = P3^6;					//时钟	
sbit SDA = P3^4;					//数据	
sbit RST = P3^5;					// DS1302复位

sbit LS138A = P2^2;  
sbit LS138B = P2^3;
sbit LS138C = P2^4; 

uChar ReadRTC_Flag;						//定义读DS1302标志

uChar l_tmpdate[7]={8,0,1,12,1,6,13};	// 秒分时日月周年13-01-12 12:00:00
uChar l_tmpdisplay[8];

uChar code write_rtc_address[7]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c}; 
										//秒分时日月周年 最低位读写位
uChar code read_rtc_address[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};  

uChar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
							0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,
							0x40,0x01,0x1f}; // 闹铃标志停止，单一，循环
//共阴数码管 0-9  10-19（含点） '-' '熄灭'表

/******************************************************************/
/*                    函数声明                                    */
/******************************************************************/												
void Write_Ds1302_byte(unsigned char temp); 
void Write_Ds1302(unsigned char address, unsigned char dat);
unsigned char Read_Ds1302 (unsigned char address);
void Read_RTC(void);		//read RTC 
void Set_RTC(void); 		//set RTC 
void InitTIMER0(void);		//inital timer0


/******************************************************************/
/*                   定时器0初始化                                */
/******************************************************************/
void InitTIMER0(void)
{
	TMOD |= 0x01;			// 定时器设置方式一 16位定时计数
	// 2.5ms
	TH0 = 0xf7;		
	TL0 = 0x00;
	
	TR0 = 1;				// 定时器0运行控制位
	ET0 = 1;				// 打开T0中断
	EA = 1;					// 全局中断允许位
}

/******************************************************************/
/*                   读时钟数据                                   */
/******************************************************************/
void Read_RTC(void)	        	// 读取 日历
{

	SYSTEMTIME ct;
	//Initial_DS1302();
	DS1302_GetTime(&ct);
	l_tmpdate[0] = ct.Second;
	l_tmpdate[1] = ct.Minute;
	l_tmpdate[2] = ct.Hour;
	l_tmpdate[3] = ct.Day;
	l_tmpdate[4] = ct.Month;
	l_tmpdate[5] = ct.Week;
	l_tmpdate[6] = ct.Year;
	/*
	unsigned char i, *p, tmp;
	p = read_rtc_address; 	    // 地址传递
	for(i=0; i<7; i++)		    // 分7次读取 秒分时日月周年
	{
		l_tmpdate[i] = Read_Ds1302(*p);
		tmp = l_tmpdate[i]/16;
		l_tmpdate[i] = l_tmpdate[i]%16;
		l_tmpdate[i] = tmp*10 + l_tmpdate[i];
		p++;
	}
	*/
}

/******************************************************************/
/*                  设定时钟数据                                  */
/******************************************************************/
void Set_RTC(void)		    	//设定 日历
{
	unsigned char i, *p, tmp;
	for(i=0; i<7; i++){      	//BCD处理
		tmp = l_tmpdate[i]/10;
		l_tmpdate[i] = l_tmpdate[i]%10;
		l_tmpdate[i] = l_tmpdate[i]+tmp*16;
	}  
	Write_Ds1302(0x8E, 0X00);

	p = write_rtc_address;		//传地址	
	for(i=0; i<7; i++)			//7次写入 秒分时日月周年
	{
		Write_Ds1302(*p, l_tmpdate[i]);
		p++;  
	}
	Write_Ds1302(0x8E, 0x80);
}

/******************************************************************/
/*                   写一个字节                                   */
/******************************************************************/
void Write_Ds1302_Byte(unsigned char temp) 
{
	unsigned char i;
	for (i=0; i<8; i++)     	// 循环8次 写入数据
	{ 
		SCK = 0;
		SDA = temp&0x01;     	// 每次传输低字节 
		temp >>= 1;  			// 右移一位
		SCK = 1;
	}
}   
/******************************************************************/
/*                  写入DS1302                                    */
/******************************************************************/
void Write_Ds1302( unsigned char address,unsigned char dat )     
{
	RST = 0;
	_nop_();
	SCK = 0;
	_nop_();
	RST = 1;	
	_nop_();                    //启动
	Write_Ds1302_Byte(address);	//发送地址
	Write_Ds1302_Byte(dat);		//发送数据
	RST = 0;  		            //恢复
}

/******************************************************************/
/*                   读出DS1302数据                               */
/******************************************************************/
/*
unsigned char Read_Ds1302 ( unsigned char address )
{
	unsigned char i, temp = 0x00;
	RST = 0;
	_nop_();
	_nop_();
	SCK = 0;
	_nop_();
	_nop_();
	RST = 1;
	_nop_();
	_nop_();
	Write_Ds1302_Byte(address);
	for (i=0; i<8; i++) 		// 循环8次 读取数据
	{		
		if (SDA)
			temp |= 0x80;		// 每次传输低字节
		SCK = 0;
		temp >>= 1;				// 右移一位
		_nop_();
		_nop_();
		_nop_();
		SCK = 1;
	} 
	RST = 0;
	_nop_();	          		// 以下为DS1302复位的稳定时间
	_nop_();
	RST = 0;
	SCK = 0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SCK = 1;
	_nop_();
	_nop_();
	SDA = 0;
	_nop_();
	_nop_();
	SDA = 1;
	_nop_();
	_nop_();
	return (temp);				// 返回
}
*/