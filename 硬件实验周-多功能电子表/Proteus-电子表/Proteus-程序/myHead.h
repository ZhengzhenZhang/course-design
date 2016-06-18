#include <ds1302.h>
#include <string.h>

/********************************变量定义*********************************/
// 控制变量
char mainLoop = 0;					// 主菜单变量
bit isModify = 0;			   		// 是否处于修改状态
uChar mFlag = 0;	  				// 修改位标记

// 闹铃变量
#define ALARMNUM 5					// 闹铃个数
uChar alarmNum = 0;					// 哪个闹铃
uChar isAlarm[ALARMNUM] = 0;  		// 是否响闹铃
uChar alarm[ALARMNUM][3];		// 闹铃

// 秒表变量
#define SWATCHNUM 10				// 秒表总数
bit isWatch = 0;					// 是否秒表
uChar sWatchNum = 0;				// 记录个数
uChar sWatchFlag = 0;				// 哪一个记录
uChar sWatch[SWATCHNUM+2][3];		// 秒表

// 定义位
sbit keyUp = P1^3;
sbit keyDown = P1^7;
sbit keyMain = P1^2;
sbit keyBack = P1^6;
sbit beep = P1^5;
/*************************************************************************/

/********************************函数声明*********************************/
// 函数声明
void KeyScan();				// 键盘扫描
void InitData();			// 初始化数据
bit DelayMs(uInt x);		// 延时
void Key_Main();			// 激活键
void Key_Up();				// 左方向键
void Key_Down();			// 右方向键
void Key_Back();			// 返回键
void display_time();   		// 时间显示
void display_data();		// 日期显示
void display_alarm();		// 闹铃显示
void display_sWatch();		// 秒表显示
void Flicker(uChar i);		// 调整闪烁
void JudgeAlarm();			// 判断闹铃
void JudgeSWatch();			// 判断秒表
void ReadTimeAndJudgeAlarmArrival();		// 读取时间并判断闹铃是否到来
uChar GetWeek(uChar y, uChar m, uChar d);	// 设定时间
/*************************************************************************/



/********************************函数实现*********************************/

void InitData() {
	//初始化定时器0
	InitTIMER0();         		 	

	// 写入时钟值，如果使用备用电池时候，不需要没每次上电写入，此程序应该屏蔽
	// Set_RTC(); 
	// 从芯片得到时间
	Read_RTC();
	// 用时间计算星期
	l_tmpdate[5] = GetWeek(l_tmpdate[6], l_tmpdate[4], l_tmpdate[3]);
	Set_RTC();						
	
	// 闹铃变量初始化
	memset(alarm, 0, sizeof (alarm));

	// 秒表数据初始化
	memset(sWatch, 0, sizeof (sWatch));
}

uChar GetWeek(uChar y, uChar m, uChar d) {
    uChar tm, ty;
    tm = m>=3 ? (m-2) : (m+10);
    ty = m>=3 ? y : y-1;
    return (ty+ty/4-ty/100+ty/400+(uChar)(2.6*tm-0.2)+d)%7;
}

// 读取时间并判断闹铃是否到来
void ReadTimeAndJudgeAlarmArrival() {
	uChar i;		// 循环用
	if(ReadRTC_Flag)
	{
		ReadRTC_Flag = 0;
		// 如果它不处于修改状态或修改状态但不为调节时间和日期
		if (!isModify || (0!=mainLoop && 1!=mainLoop)) {
			Read_RTC();	 					// 如果符合条件就从芯片读取时间
			for (i=0; i<ALARMNUM; i++)	  	// 判断是否有闹铃时间到
				if (!isModify && l_tmpdate[1]==alarm[i][2]  	// 如果处于非修改状态且时间相等
					&& l_tmpdate[2]==alarm[i][1] && !l_tmpdate[0]
					&& alarm[i][0])								// 如果闹铃不为关闭状态
					isAlarm[i] = 1;	
		}
	}
}

// 延时函数
bit DelayMs(uInt x) {
	uChar j;
	while (x--)
		for (j=110; j>0; j--);
	return 1;
}

// 显示时间函数实现
void display_time()
{
	l_tmpdisplay[0] = l_tmpdate[2]/10;	//数据的转换，因我们采用数码管0~9的显示,将数据分开
	l_tmpdisplay[1] = l_tmpdate[2]%10;
	l_tmpdisplay[2] = 20;				//加入"-"
	l_tmpdisplay[3] = l_tmpdate[1]/10;
	l_tmpdisplay[4] = l_tmpdate[1]%10;
	l_tmpdisplay[5] = 20;
	l_tmpdisplay[6] = l_tmpdate[0]/10;
	l_tmpdisplay[7] = l_tmpdate[0]%10;
}

// 显示日期函数实现
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

// 显示闹铃函数实现
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

// 显示秒表函数实现
void display_sWatch()
{
	if (0 == sWatchFlag) {
		l_tmpdisplay[0] = 20;							// 如果为0则用‘-’表示
		l_tmpdisplay[1] = 20;
	}
	else {
 		l_tmpdisplay[0] = sWatchFlag/10;	
		l_tmpdisplay[1] = sWatchFlag%10;
	}
	l_tmpdisplay[2] = sWatch[sWatchFlag][0]/10;			
	l_tmpdisplay[3] = sWatch[sWatchFlag][0]%10 + 10;	// +10表示带点的数字
	l_tmpdisplay[4] = sWatch[sWatchFlag][1]/10;
	l_tmpdisplay[5] = sWatch[sWatchFlag][1]%10 + 10;
	l_tmpdisplay[6] = sWatch[sWatchFlag][2]/10;
	l_tmpdisplay[7] = sWatch[sWatchFlag][2]%10;
}

// 判断四个按键哪个被按下，然后调用相应函数
#define DTIM 200	 		// 方向键循环延时
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