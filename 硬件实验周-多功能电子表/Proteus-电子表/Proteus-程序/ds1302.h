#include <DS1302_EX.h>
typedef unsigned char uChar;
typedef unsigned int uInt;

sbit SCK = P3^6;					//ʱ��	
sbit SDA = P3^4;					//����	
sbit RST = P3^5;					// DS1302��λ

sbit LS138A = P2^2;  
sbit LS138B = P2^3;
sbit LS138C = P2^4; 

uChar ReadRTC_Flag;						//�����DS1302��־

uChar l_tmpdate[7]={8,0,1,12,1,6,13};	// ���ʱ��������13-01-12 12:00:00
uChar l_tmpdisplay[8];

uChar code write_rtc_address[7]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c}; 
										//���ʱ�������� ���λ��дλ
uChar code read_rtc_address[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};  

uChar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
							0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,
							0x40,0x01,0x1f}; // �����־ֹͣ����һ��ѭ��
//��������� 0-9  10-19�����㣩 '-' 'Ϩ��'��

/******************************************************************/
/*                    ��������                                    */
/******************************************************************/												
void Write_Ds1302_byte(unsigned char temp); 
void Write_Ds1302(unsigned char address, unsigned char dat);
unsigned char Read_Ds1302 (unsigned char address);
void Read_RTC(void);		//read RTC 
void Set_RTC(void); 		//set RTC 
void InitTIMER0(void);		//inital timer0


/******************************************************************/
/*                   ��ʱ��0��ʼ��                                */
/******************************************************************/
void InitTIMER0(void)
{
	TMOD |= 0x01;			// ��ʱ�����÷�ʽһ 16λ��ʱ����
	// 2.5ms
	TH0 = 0xf7;		
	TL0 = 0x00;
	
	TR0 = 1;				// ��ʱ��0���п���λ
	ET0 = 1;				// ��T0�ж�
	EA = 1;					// ȫ���ж�����λ
}

/******************************************************************/
/*                   ��ʱ������                                   */
/******************************************************************/
void Read_RTC(void)	        	// ��ȡ ����
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
	p = read_rtc_address; 	    // ��ַ����
	for(i=0; i<7; i++)		    // ��7�ζ�ȡ ���ʱ��������
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
/*                  �趨ʱ������                                  */
/******************************************************************/
void Set_RTC(void)		    	//�趨 ����
{
	unsigned char i, *p, tmp;
	for(i=0; i<7; i++){      	//BCD����
		tmp = l_tmpdate[i]/10;
		l_tmpdate[i] = l_tmpdate[i]%10;
		l_tmpdate[i] = l_tmpdate[i]+tmp*16;
	}  
	Write_Ds1302(0x8E, 0X00);

	p = write_rtc_address;		//����ַ	
	for(i=0; i<7; i++)			//7��д�� ���ʱ��������
	{
		Write_Ds1302(*p, l_tmpdate[i]);
		p++;  
	}
	Write_Ds1302(0x8E, 0x80);
}

/******************************************************************/
/*                   дһ���ֽ�                                   */
/******************************************************************/
void Write_Ds1302_Byte(unsigned char temp) 
{
	unsigned char i;
	for (i=0; i<8; i++)     	// ѭ��8�� д������
	{ 
		SCK = 0;
		SDA = temp&0x01;     	// ÿ�δ�����ֽ� 
		temp >>= 1;  			// ����һλ
		SCK = 1;
	}
}   
/******************************************************************/
/*                  д��DS1302                                    */
/******************************************************************/
void Write_Ds1302( unsigned char address,unsigned char dat )     
{
	RST = 0;
	_nop_();
	SCK = 0;
	_nop_();
	RST = 1;	
	_nop_();                    //����
	Write_Ds1302_Byte(address);	//���͵�ַ
	Write_Ds1302_Byte(dat);		//��������
	RST = 0;  		            //�ָ�
}

/******************************************************************/
/*                   ����DS1302����                               */
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
	for (i=0; i<8; i++) 		// ѭ��8�� ��ȡ����
	{		
		if (SDA)
			temp |= 0x80;		// ÿ�δ�����ֽ�
		SCK = 0;
		temp >>= 1;				// ����һλ
		_nop_();
		_nop_();
		_nop_();
		SCK = 1;
	} 
	RST = 0;
	_nop_();	          		// ����ΪDS1302��λ���ȶ�ʱ��
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
	return (temp);				// ����
}
*/