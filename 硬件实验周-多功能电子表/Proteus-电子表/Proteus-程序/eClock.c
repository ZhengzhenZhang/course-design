#include <reg52.h> 
#include <intrins.h>
#include <myHead.h>

int main()    
{	
	InitData();	 					
	
	while(1) {

		ReadTimeAndJudgeAlarmArrival();

		switch (mainLoop) {
		case 0:
			display_time();
			break;
		case 1:
			display_data();
			break;
		case 2:
			display_alarm();
			break;
		case 3:
			display_sWatch();
			break;
		}
		KeyScan();
	}

	return 0;
}

void Key_Main() {
	// 如果刚进入修改状态
	if (!isModify) {			
		isModify = 1;
		if (0 == mainLoop)	 		// 如果为时间
			mFlag = 2;
		else if (1 == mainLoop)	  	// 如果为日期
			mFlag = 6;
		else if (2 == mainLoop)	   	// 如果为闹铃
			mFlag = 3;
		else if (3 == mainLoop) {	// 如果秒表
			sWatchFlag = 0;
		}
		/********************继续添加功能***********************/
		return;
	}
	// 如果主菜单是时间
	if (0 == mainLoop) {  			
		mFlag--;			 		// 循环时分
		if (mFlag <= 0)
			mFlag = 2;
		return;
	}
	// 如果主菜单是日期
	if (1 == mainLoop) {
		if (6 == mFlag)	mFlag--;
		mFlag--;
		if (mFlag <= 2)
			mFlag = 6;
		return;
	}
	// 如果主菜单是闹铃
	if (2 == mainLoop) {
		mFlag++;
		if (mFlag >= 4)
			mFlag = 0;
		return;
	}
	// 如果主菜单是秒表
	if (3 == mainLoop) {
		if (!isWatch) {
			if (sWatchFlag != 0)
				return;
			sWatchNum = 0;
		}
		isWatch = 1;
		sWatchNum++;
		if (sWatchNum > SWATCHNUM) {
			isWatch = 0;
			sWatchFlag = 1;
			sWatchNum--;
			return;
		}
		sWatchFlag = sWatchNum;
		sWatch[sWatchNum][0] = sWatch[sWatchNum-1][0];
		sWatch[sWatchNum][1] = sWatch[sWatchNum-1][1];
		sWatch[sWatchNum][2] = sWatch[sWatchNum-1][2];
		return;
	}

	/********************继续添加功能***********************/
}

void Key_Up() {
	if (!isModify) {			   	// 如果不是修改状态
		mainLoop++;
		return;
	}
	// 向上调节时间
	if (0 == mainLoop) {		  	
		l_tmpdate[mFlag]++;
		if (2==mFlag && l_tmpdate[2]>=24)
			l_tmpdate[2] = 0;
		else if (1==mFlag && l_tmpdate[1]>=60)
			l_tmpdate[1] = 0;
		return;
	}
	// 向上调节日期
	if (1 == mainLoop) {		   	
		l_tmpdate[mFlag]++;
		if (6==mFlag && l_tmpdate[6]>=100)
			l_tmpdate[6] = 0;
		else if (4==mFlag && l_tmpdate[4]>=13)
			l_tmpdate[4] = 1;
		else if (3==mFlag && l_tmpdate[3]>=32)
			l_tmpdate[3] = 1;
		return;	
	}

	// 向上调节闹铃
	if (2 == mainLoop) {
		if (3 == mFlag)		 	// 如果处于选闹铃
			alarmNum++;	
		else	   				// 如果处于调节闹铃
			alarm[alarmNum][mFlag]++;

		if (3==mFlag && alarmNum>=ALARMNUM)
			alarmNum = 0;
		if (1==mFlag && alarm[alarmNum][1]>=24)
			alarm[alarmNum][1] = 0;
		else if (2==mFlag && alarm[alarmNum][2]>=60)
			alarm[alarmNum][2] = 0;
		else if (0==mFlag && alarm[alarmNum][0]>=3)	 // 闹铃状态调节
			alarm[alarmNum][0] = 0;
		return;	
	}
	// 向上调节秒表
	if (3 == mainLoop) {
		sWatchFlag++;
		if (sWatchFlag > sWatchNum)
			sWatchFlag = 0;
		return;	
	}
	/********************继续添加功能***********************/
}

void Key_Down() {
	if (!isModify) {
		mainLoop--;
		return;
	}
	// 向下调节时间
	if (0 == mainLoop) {
		if (l_tmpdate[mFlag] > 0) {
			l_tmpdate[mFlag]--;
			return;
		}
		if (2==mFlag && l_tmpdate[2]<=0)
			l_tmpdate[2] = 23;
		else if (1==mFlag && l_tmpdate[1]<=0)
			l_tmpdate[1] = 59;
		return;
	}
	// 向下调节日期
	if (1 == mainLoop) {
		if (l_tmpdate[mFlag] > 1 && mFlag!=6) {
			l_tmpdate[mFlag]--;
			return;
		}
		if (l_tmpdate[mFlag] > 0 && mFlag == 6) {
			l_tmpdate[mFlag]--;
			return;
		}
		if (6==mFlag && l_tmpdate[6]<=0)
			l_tmpdate[6] = 99;
		else if (4==mFlag && l_tmpdate[4]<=1)
			l_tmpdate[4] = 12;
		else if (3==mFlag && l_tmpdate[3]<=1)
			l_tmpdate[3] = 31;
		return;
	}
	// 向下调节闹铃
	if (2 == mainLoop) {
		if (3==mFlag && alarmNum>0) {		 		// 如果处于选闹铃状态
			alarmNum--;	
			return;
		}
		else if (alarm[alarmNum][mFlag]>0) {	// 如果处于调节闹铃状态
			alarm[alarmNum][mFlag]--;
			return;
		}
		if (3==mFlag && alarmNum<=0)
			alarmNum = ALARMNUM-1;
		else if (1==mFlag && alarm[alarmNum][1]<=0)
			alarm[alarmNum][1] = 23;
		else if (2==mFlag && alarm[alarmNum][2]<=0)
			alarm[alarmNum][2] = 59;
		else if (0==mFlag && alarm[alarmNum][0]<=0)
			alarm[alarmNum][0] = 2;
		return;
	}
	// 向下调节秒表
	if (3 == mainLoop) {
		if (sWatchFlag > 0) {
		 	sWatchFlag--;
			return;
		}
		if (sWatchFlag <= 0)
			sWatchFlag = sWatchNum;
		return;	
	}
	/********************继续添加功能***********************/
}

void Key_Back() {
	uChar i;
	if (!isModify) {
		mainLoop = 0;
		for (i=0; i<ALARMNUM; i++) {
			if (isAlarm[i]) {			// 如果闹铃正在响则关闭
				isAlarm[i] = 0;
				if (1 == alarm[i][0])	// 如果闹铃为单一状态则设为关闭状态
					alarm[i][0] = 0;
			}
		}
		alarmNum = 0;
		beep = 1; 	// 按返回键关闭闹铃
		return;
	}
	if (0 == mainLoop) {	// 如果为设定时间
		isModify = 0;
		Set_RTC();
		return; 
	}
	if (1 == mainLoop) {	// 如果为设定日期
		isModify = 0;
		l_tmpdate[5] = GetWeek(l_tmpdate[6], l_tmpdate[4], l_tmpdate[3]);
							// 得到星期
		Set_RTC();
		return; 
	}	
	if (2 == mainLoop) {
		isModify = 0;
		return;
	}
	if (3 == mainLoop) {  // 如果为秒表
		if (isWatch) {
			sWatchFlag = 1;
			isWatch = 0;
			return;
		}
		isModify = 0;
		sWatchFlag = 0;
		return;
	}

	/********************继续添加功能***********************/
}

// 调整闪烁函数
#define XTIM 180
 uInt fx = 0; // 用于闪烁记数
void Flicker(uChar i) {
	fx++;
	if (!isModify) {
		P0 = table[l_tmpdisplay[i]]; 			//查表法得到要显示数字的数码段
		return;
	}
	// 时间闪烁
	if (0 == mainLoop) {						
		if (fx < XTIM)	
		{
			if (2==mFlag && (0==i||1==i))	 	// 如果为小时
	   			P0 = 0;
			else if (1==mFlag && (3==i||4==i))	// 如果为分钟
				P0 = 0;
			else
				P0 = table[l_tmpdisplay[i]];
		}
		else if (fx < XTIM*2)
			P0 = table[l_tmpdisplay[i]];
		else {
			P0 = table[l_tmpdisplay[i]];
			fx = 0;
		}
		return;
	}
	// 日期闪烁
	if (1 == mainLoop) {						
		if (fx < XTIM)	
		{
			if (6==mFlag && (0==i||1==i))	// 如果为年
	   			P0 = 0;
			else if (4==mFlag && (2==i||3==i))			// 如果为月
				P0 = 0;
			else if (3==mFlag && (4==i||5==i))			// 如果为日
				P0 = 0;
			else
				P0 = table[l_tmpdisplay[i]];
		}
		else if (fx < XTIM*2)
			P0 = table[l_tmpdisplay[i]];
		else {
			P0 = table[l_tmpdisplay[i]];
			fx = 0;
		}
		return;
	}

	// 闹铃闪烁
	if (2 == mainLoop) {						
		if (fx < XTIM)	
		{
			if (3==mFlag && 1==i)			   	// 如果选闹铃
				P0 = 0;
			else if (1==mFlag && (3==i||4==i))	// 如果为小时
				P0 = 0;
			else if (2==mFlag && (6==i||7==i))	// 如果为分钟
				P0 = 0;
			else if (0==mFlag && 0==i)	 		// 如果为状态
	   			P0 = 0;
			else
				P0 = table[l_tmpdisplay[i]];
		}
		else if (fx < XTIM*2)
			P0 = table[l_tmpdisplay[i]];
		else {
			P0 = table[l_tmpdisplay[i]];
			fx = 0;
		}
		return;
	}
	// 秒表
	if (3 == mainLoop) {
		if (fx < XTIM && (0==i||1==i))	
		{
			P0 = 0;
		}
		else if (fx < XTIM*2)
			P0 = table[l_tmpdisplay[i]];
		else {
			P0 = table[l_tmpdisplay[i]];
			fx = 0;
		}
   		return;
	}
	/********************继续添加功能***********************/
}

// 判断闹铃
#define ATIM 100
 uChar ax = 0;
 uChar aNum = 0;
void JudgeAlarm() {
	uChar i;
	for (i=0; i<ALARMNUM; i++)
		if (isAlarm[i])
			break;
	if (i == ALARMNUM)
		return;

	ax++;
	if (ax < ATIM)
		beep = 0;
	else if (ax < 2*ATIM) {
		beep = 1;
		P0  = 0;				// 随着闹铃屏幕闪烁
	}
	else  {
		ax = 0;
		aNum++;
	}

	if (aNum > 20)	{			// 如果响够20次自动关闭
		aNum = 0;
		for (i=0; i<ALARMNUM; i++)
			if (isAlarm[i]) {			// 如果闹铃正在响则关闭
				isAlarm[i] = 0;
				if (1 == alarm[i][0])	// 如果闹铃为单一状态则设为关闭状态
					alarm[i][0] = 0;
			}
		beep = 1;
	}
}

// 判断秒表
 uChar sNum = 0;
void JudgeSWatch() {			// 判断是否秒表
	if (!isWatch)				// 如果不是开始计数就返回
		return;

	sNum++;
	if (sNum >= 4) {
		sNum = 0;
		sWatch[sWatchNum][2]++;
		sWatch[sWatchNum][1] += sWatch[sWatchNum][2]/100;
		sWatch[sWatchNum][2] %= 100;
		sWatch[sWatchNum][0] += sWatch[sWatchNum][1]/60;
		sWatch[sWatchNum][1] %= 60;
		sWatch[sWatchNum][0] %= 60;
	}	
}

// 显示函数
 uChar iCount = 0, iNum = 0;
void Display(void) interrupt 1 using 1
// 中断，用于数码管扫描
{	
	// 2.5ms
	TH0 = 0xf7;		
	TL0 = 0x00;

	// 消除重影	
	P0 = 0;	 

	// 实现数码管位选
	LS138A = (iCount) & 0x01;
	LS138B = (iCount>>1) & 0x01;
	LS138C = (iCount>>2) & 0x01;
   
	Flicker(iCount);
	JudgeAlarm();			 	// 判断是否闹铃
	JudgeSWatch();				// 判断是否秒表

	iCount++;
	if(iCount >= 8)
	{
		iCount = 0;
		iNum++;
		if(iNum>=10)       		// 隔段时间读取1302的数据。时间间隔可以调整
		{
			ReadRTC_Flag = 1; 	// 使用标志位判断
			iNum = 0;
		}
	}
}