#include <reg52.h> 
#include <intrins.h>
#include <myHead.h>

int main()    
{
	// ��ʼ�����ݺ���
	InitData();	 					
	
	while(1) {
		// ��ȡʱ�䲢�ж������Ƿ���
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

		/********************������ӹ���***********************/
		} 

		KeyScan();
	}

	return 0;
}

void Key_Main() {
	// ����ս����޸�״̬
	if (!isModify) {			
		isModify = 1;
		if (0 == mainLoop)	 		// ���Ϊʱ��
			mFlag = 2;
		else if (1 == mainLoop)	  	// ���Ϊ����
			mFlag = 6;
		else if (2 == mainLoop)	   	// ���Ϊ����
			mFlag = 3;
		else if (3 == mainLoop) {	// ������
			sWatchFlag = 0;
		}
		/********************������ӹ���***********************/
		return;
	}
	// ������˵���ʱ��
	if (0 == mainLoop) {  			
		mFlag--;			 		// ѭ��ʱ��
		if (mFlag <= 0)
			mFlag = 2;
		return;
	}
	// ������˵�������
	if (1 == mainLoop) {
		if (6 == mFlag)	mFlag--;
		mFlag--;
		if (mFlag <= 2)
			mFlag = 6;
		return;
	}
	// ������˵�������
	if (2 == mainLoop) {
		mFlag++;
		if (mFlag >= 4)
			mFlag = 0;
		return;
	}
	// ������˵������
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

	/********************������ӹ���***********************/
}

void Key_Up() {
	if (!isModify) {			   	// ��������޸�״̬
		mainLoop++;
		return;
	}
	// ���ϵ���ʱ��
	if (0 == mainLoop) {		  	
		l_tmpdate[mFlag]++;
		if (2==mFlag && l_tmpdate[2]>=24)
			l_tmpdate[2] = 0;
		else if (1==mFlag && l_tmpdate[1]>=60)
			l_tmpdate[1] = 0;
		return;
	}
	// ���ϵ�������
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

	// ���ϵ�������
	if (2 == mainLoop) {
		if (3 == mFlag)		 	// �������ѡ����
			alarmNum++;	
		else	   				// ������ڵ�������
			alarm[alarmNum][mFlag]++;

		if (3==mFlag && alarmNum>=ALARMNUM)
			alarmNum = 0;
		if (1==mFlag && alarm[alarmNum][1]>=24)
			alarm[alarmNum][1] = 0;
		else if (2==mFlag && alarm[alarmNum][2]>=60)
			alarm[alarmNum][2] = 0;
		else if (0==mFlag && alarm[alarmNum][0]>=3)	 // ����״̬����
			alarm[alarmNum][0] = 0;
		return;	
	}
	// ���ϵ������
	if (3 == mainLoop) {
		sWatchFlag++;
		if (sWatchFlag > sWatchNum)
			sWatchFlag = 0;
		return;	
	}
	/********************������ӹ���***********************/
}

void Key_Down() {
	if (!isModify) {
		mainLoop--;
		return;
	}
	// ���µ���ʱ��
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
	// ���µ�������
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
	// ���µ�������
	if (2 == mainLoop) {
		if (3==mFlag && alarmNum>0) {		 		// �������ѡ����״̬
			alarmNum--;	
			return;
		}
		else if (alarm[alarmNum][mFlag]>0) {	// ������ڵ�������״̬
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
	// ���µ������
	if (3 == mainLoop) {
		if (sWatchFlag > 0) {
		 	sWatchFlag--;
			return;
		}
		if (sWatchFlag <= 0)
			sWatchFlag = sWatchNum;
		return;	
	}

	/********************������ӹ���***********************/
}

void Key_Back() {
	uChar i;
	if (!isModify) {
		mainLoop = 0;
		for (i=0; i<ALARMNUM; i++) {
			if (isAlarm[i]) {			// ���������������ر�
				isAlarm[i] = 0;
				if (1 == alarm[i][0])	// �������Ϊ��һ״̬����Ϊ�ر�״̬
					alarm[i][0] = 0;
			}
		}
		alarmNum = 0;
		beep = 1; 	// �����ؼ��ر�����
		return;
	}
	if (0 == mainLoop) {	// ���Ϊ�趨ʱ��
		isModify = 0;
		Set_RTC();
		return; 
	}
	if (1 == mainLoop) {	// ���Ϊ�趨����
		isModify = 0;
		l_tmpdate[5] = GetWeek(l_tmpdate[6], l_tmpdate[4], l_tmpdate[3]);
							// �õ�����
		Set_RTC();
		return; 
	}	
	if (2 == mainLoop) {
		isModify = 0;
		return;
	}
	if (3 == mainLoop) {  // ���Ϊ���
		if (isWatch) {
			sWatchFlag = 1;
			isWatch = 0;
			return;
		}
		isModify = 0;
		sWatchFlag = 0;
		return;
	}

	/********************������ӹ���***********************/
}

// ������˸����
#define XTIM 180
xdata uInt fx = 0; // ������˸����
void Flicker(uChar i) {
	fx++;
	if (!isModify) {
		P0 = table[l_tmpdisplay[i]]; 			//����õ�Ҫ��ʾ���ֵ������
		return;
	}
	// ʱ����˸
	if (0 == mainLoop) {						
		if (fx < XTIM)	
		{
			if (2==mFlag && (0==i||1==i))	 	// ���ΪСʱ
	   			P0 = 0;
			else if (1==mFlag && (3==i||4==i))	// ���Ϊ����
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
	// ������˸
	if (1 == mainLoop) {						
		if (fx < XTIM)	
		{
			if (6==mFlag && (0==i||1==i))	// ���Ϊ��
	   			P0 = 0;
			else if (4==mFlag && (2==i||3==i))			// ���Ϊ��
				P0 = 0;
			else if (3==mFlag && (4==i||5==i))			// ���Ϊ��
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

	// ������˸
	if (2 == mainLoop) {						
		if (fx < XTIM)	
		{
			if (3==mFlag && 1==i)			   	// ���ѡ����
				P0 = 0;
			else if (1==mFlag && (3==i||4==i))	// ���ΪСʱ
				P0 = 0;
			else if (2==mFlag && (6==i||7==i))	// ���Ϊ����
				P0 = 0;
			else if (0==mFlag && 0==i)	 		// ���Ϊ״̬
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
	// ���
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
	/********************������ӹ���***********************/
}

// �ж�����
#define ATIM 100
xdata uChar ax = 0;
xdata uChar aNum = 0;
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
		P0  = 0;				// ����������Ļ��˸
	}
	else  {
		ax = 0;
		aNum++;
	}

	if (aNum > 20)	{			// ����칻20���Զ��ر�
		aNum = 0;
		for (i=0; i<ALARMNUM; i++)
			if (isAlarm[i]) {			// ���������������ر�
				isAlarm[i] = 0;
				if (1 == alarm[i][0])	// �������Ϊ��һ״̬����Ϊ�ر�״̬
					alarm[i][0] = 0;
			}
		beep = 1;
	}
}

// �ж����
xdata uChar sNum = 0;
void JudgeSWatch() {			// �ж��Ƿ����
	if (!isWatch)				// ������ǿ�ʼ�����ͷ���
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

// ��ʾ����
xdata uChar iCount = 0, iNum = 0;
void Display() interrupt 1 using 1
// �жϣ����������ɨ��
{	
	// 2.5ms
	TH0 = 0xf7;		
	TL0 = 0x00;

	// ������Ӱ	
	P0 = 0;	 

	// ʵ�������λѡ
	LS138A = (iCount) & 0x01;
	LS138B = (iCount>>1) & 0x01;
	LS138C = (iCount>>2) & 0x01;
   
	Flicker(iCount);
	JudgeAlarm();			 	// �ж��Ƿ�����
	JudgeSWatch();				// �ж��Ƿ����

	iCount++;
	if(iCount >= 8)
	{
		iCount = 0;
		iNum++;
		if(iNum>=10)       		// ����ʱ���ȡ1302�����ݡ�ʱ�������Ե���
		{
			ReadRTC_Flag = 1; 	// ʹ�ñ�־λ�ж�
			iNum = 0;
		}
	}
}