#include <ds1302.h>
#include <string.h>

/********************************��������*********************************/
// ���Ʊ���
char mainLoop = 0;					// ���˵�����
bit isModify = 0;			   		// �Ƿ����޸�״̬
uChar mFlag = 0;	  				// �޸�λ���

// �������
#define ALARMNUM 5					// �������
uChar alarmNum = 0;					// �ĸ�����
uChar isAlarm[ALARMNUM] = 0;  		// �Ƿ�������
uChar alarm[ALARMNUM][3];		// ����

// ������
#define SWATCHNUM 10				// �������
bit isWatch = 0;					// �Ƿ����
uChar sWatchNum = 0;				// ��¼����
uChar sWatchFlag = 0;				// ��һ����¼
uChar sWatch[SWATCHNUM+2][3];		// ���

// ����λ
sbit keyUp = P1^3;
sbit keyDown = P1^7;
sbit keyMain = P1^2;
sbit keyBack = P1^6;
sbit beep = P1^5;
/*************************************************************************/

/********************************��������*********************************/
// ��������
void KeyScan();				// ����ɨ��
void InitData();			// ��ʼ������
bit DelayMs(uInt x);		// ��ʱ
void Key_Main();			// �����
void Key_Up();				// �����
void Key_Down();			// �ҷ����
void Key_Back();			// ���ؼ�
void display_time();   		// ʱ����ʾ
void display_data();		// ������ʾ
void display_alarm();		// ������ʾ
void display_sWatch();		// �����ʾ
void Flicker(uChar i);		// ������˸
void JudgeAlarm();			// �ж�����
void JudgeSWatch();			// �ж����
void ReadTimeAndJudgeAlarmArrival();		// ��ȡʱ�䲢�ж������Ƿ���
uChar GetWeek(uChar y, uChar m, uChar d);	// �趨ʱ��
/*************************************************************************/



/********************************����ʵ��*********************************/

void InitData() {
	//��ʼ����ʱ��0
	InitTIMER0();         		 	

	// д��ʱ��ֵ�����ʹ�ñ��õ��ʱ�򣬲���Ҫûÿ���ϵ�д�룬�˳���Ӧ������
	// Set_RTC(); 
	// ��оƬ�õ�ʱ��
	Read_RTC();
	// ��ʱ���������
	l_tmpdate[5] = GetWeek(l_tmpdate[6], l_tmpdate[4], l_tmpdate[3]);
	Set_RTC();						
	
	// ���������ʼ��
	memset(alarm, 0, sizeof (alarm));

	// ������ݳ�ʼ��
	memset(sWatch, 0, sizeof (sWatch));
}

uChar GetWeek(uChar y, uChar m, uChar d) {
    uChar tm, ty;
    tm = m>=3 ? (m-2) : (m+10);
    ty = m>=3 ? y : y-1;
    return (ty+ty/4-ty/100+ty/400+(uChar)(2.6*tm-0.2)+d)%7;
}

// ��ȡʱ�䲢�ж������Ƿ���
void ReadTimeAndJudgeAlarmArrival() {
	uChar i;		// ѭ����
	if(ReadRTC_Flag)
	{
		ReadRTC_Flag = 0;
		// ������������޸�״̬���޸�״̬����Ϊ����ʱ�������
		if (!isModify || (0!=mainLoop && 1!=mainLoop)) {
			Read_RTC();	 					// ������������ʹ�оƬ��ȡʱ��
			for (i=0; i<ALARMNUM; i++)	  	// �ж��Ƿ�������ʱ�䵽
				if (!isModify && l_tmpdate[1]==alarm[i][2]  	// ������ڷ��޸�״̬��ʱ�����
					&& l_tmpdate[2]==alarm[i][1] && !l_tmpdate[0]
					&& alarm[i][0])								// ������岻Ϊ�ر�״̬
					isAlarm[i] = 1;	
		}
	}
}

// ��ʱ����
bit DelayMs(uInt x) {
	uChar j;
	while (x--)
		for (j=110; j>0; j--);
	return 1;
}

// ��ʾʱ�亯��ʵ��
void display_time()
{
	l_tmpdisplay[0] = l_tmpdate[2]/10;	//���ݵ�ת���������ǲ��������0~9����ʾ,�����ݷֿ�
	l_tmpdisplay[1] = l_tmpdate[2]%10;
	l_tmpdisplay[2] = 20;				//����"-"
	l_tmpdisplay[3] = l_tmpdate[1]/10;
	l_tmpdisplay[4] = l_tmpdate[1]%10;
	l_tmpdisplay[5] = 20;
	l_tmpdisplay[6] = l_tmpdate[0]/10;
	l_tmpdisplay[7] = l_tmpdate[0]%10;
}

// ��ʾ���ں���ʵ��
void display_data()
{
	l_tmpdisplay[0] = l_tmpdate[6]/10;;	
	l_tmpdisplay[1] = l_tmpdate[6]%10 + 10;
	l_tmpdisplay[2] = l_tmpdate[4]/10;			
	l_tmpdisplay[3] = l_tmpdate[4]%10 + 10;
	l_tmpdisplay[4] = l_tmpdate[3]/10;
	l_tmpdisplay[5] = l_tmpdate[3]%10;
	l_tmpdisplay[6] = 20;
	l_tmpdisplay[7] = l_tmpdate[5];
}

// ��ʾ���庯��ʵ��
void display_alarm()
{
	l_tmpdisplay[0] = alarm[alarmNum][0]+20;	
	l_tmpdisplay[1] = alarmNum + 1;
	l_tmpdisplay[2] = 20;			
	l_tmpdisplay[3] = alarm[alarmNum][1]/10;
	l_tmpdisplay[4] = alarm[alarmNum][1]%10;
	l_tmpdisplay[5] = 20;
	l_tmpdisplay[6] = alarm[alarmNum][2]/10;
	l_tmpdisplay[7] = alarm[alarmNum][2]%10;
}

// ��ʾ�����ʵ��
void display_sWatch()
{
	if (0 == sWatchFlag) {
		l_tmpdisplay[0] = 20;							// ���Ϊ0���á�-����ʾ
		l_tmpdisplay[1] = 20;
	}
	else {
 		l_tmpdisplay[0] = sWatchFlag/10;	
		l_tmpdisplay[1] = sWatchFlag%10;
	}
	l_tmpdisplay[2] = sWatch[sWatchFlag][0]/10;			
	l_tmpdisplay[3] = sWatch[sWatchFlag][0]%10 + 10;	// +10��ʾ���������
	l_tmpdisplay[4] = sWatch[sWatchFlag][1]/10;
	l_tmpdisplay[5] = sWatch[sWatchFlag][1]%10 + 10;
	l_tmpdisplay[6] = sWatch[sWatchFlag][2]/10;
	l_tmpdisplay[7] = sWatch[sWatchFlag][2]%10;
}

// �ж��ĸ������ĸ������£�Ȼ�������Ӧ����
#define DTIM 200	 		// �����ѭ����ʱ
#define KDT 10
void KeyScan() {
	if (0 == keyMain) {
		DelayMs(KDT);
		if (0 == keyMain) {
			 Key_Main();
		}
		while (!keyMain);
		DelayMs(KDT);
		while (!keyMain);
	}
	else if (0 == keyUp) {
		DelayMs(KDT);
		if (0 == keyUp) {
			Key_Up();			
		}
		while (!keyUp && !DelayMs(DTIM));
		DelayMs(KDT);
		while (!keyUp && !DelayMs(DTIM));
	}
	else if (0 == keyDown) {
		DelayMs(KDT);
		if (0 == keyDown) {
			Key_Down();				
		}
		while (!keyDown && !DelayMs(DTIM));
		DelayMs(KDT);
		while (!keyDown && !DelayMs(DTIM));
	}
	else if (0 == keyBack) {
		DelayMs(KDT);
		if (0 == keyBack) {
			Key_Back();	
		}
		while (!keyBack);
		DelayMs(KDT);
		while (!keyBack);
	}
	
	if (4 <= mainLoop)
		mainLoop = 0;
	else if (-1 >= mainLoop)
		mainLoop = 3;
}
/*************************************************************************/