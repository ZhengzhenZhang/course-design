#pragma once

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
//---功能：向服务端返回已收到信息
//---完成人：
//---完成时间：
//---修改时间：
//---------------
void HaveReceived(CSocket &sockClient);

UINT ThreadProc1(LPVOID pParam);