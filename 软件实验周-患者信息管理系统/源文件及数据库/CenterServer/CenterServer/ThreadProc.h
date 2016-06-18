#pragma once

// 时间不够废弃的线程类，实现远程连接客户端
#include "RecordsetDiag.h"

class CThreadProc
{
public:
	CThreadProc(void);
	~CThreadProc(void);
};

//---------------
//---功能：患者信息结构体
//---完成人：
//---完成时间：
//---修改时间：
//---------------
typedef struct _PatientInfo {
	bool	flag;				// 用来标记是否接收完了数据
	TCHAR	diagTime[20];
	TCHAR	diagDoctorID[20];
	TCHAR	idNumber[20];
	TCHAR	patientName[10];
	TCHAR	patientSex[2];
	int		patientAge;
	TCHAR	patientPhone[20];
	TCHAR	patientAddress[50];
	TCHAR	patientNum[20];
	TCHAR	patientAllergy[100];
	TCHAR	patientRemark[200];
}PatientInfo;


//---------------
//---功能：该函数实现为患者信息结构体赋值
//---完成人：
//---完成时间：
//---修改时间：
//---------------
void GetPatientStruct(PatientInfo &drg, CRecordsetDiag &set);

//---------------
//---功能：该函数实现判断客户端是否收到数据，如果没有收到则一直等待下去
//---完成人：
//---完成时间：
//---修改时间：
//---------------
void IfReceived(CSocket &sockRecv);

UINT ThreadProc1(LPVOID pParam);

UINT ThreadProc2(LPVOID pParam);

