#pragma once

class CThreadProc
{
public:
	CThreadProc(void);
	~CThreadProc(void);
};

//---------------
//---���ܣ�������Ϣ�ṹ��
//---����ˣ�
//---���ʱ�䣺
//---�޸�ʱ�䣺
//---------------
typedef struct _PatientInfo {
	bool	flag;				// ��������Ƿ������������
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
//---���ܣ������˷������յ���Ϣ
//---����ˣ�
//---���ʱ�䣺
//---�޸�ʱ�䣺
//---------------
void HaveReceived(CSocket &sockClient);

UINT ThreadProc1(LPVOID pParam);