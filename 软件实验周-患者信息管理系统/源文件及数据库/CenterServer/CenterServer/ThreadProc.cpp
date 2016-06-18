#include "StdAfx.h"
#include "ThreadProc.h"

CThreadProc::CThreadProc(void)
{
}

CThreadProc::~CThreadProc(void)
{
}

UINT ThreadProc2(LPVOID pParam)
{

	while (1);
	return 0;
}

UINT ThreadProc1(LPVOID pParam)
{
	AfxSocketInit();
	CSocket sockServ;
	sockServ.Create(5000);
	sockServ.Listen();				// ��ʼ�����ͻ�������

	PatientInfo drg;				// Ҫ�������ݵĻ�����
	int drgSize = sizeof (PatientInfo);
	// �õ�������Ϣ�ṹ���С
	CSocket sockRecv;				// ����һ������socket

	while (true)
	{
	
		sockServ.Accept(sockRecv);	// ���տͻ������󲢺͵ײ��׽��ֽ��а�

		CRecordsetDiag setDiag;
		setDiag.m_strFilter = _T(""); // sql�������
		if (!setDiag.Open())
		{
			AfxMessageBox(_T("�������ݿ�ʱ����"), MB_OK);
			setDiag.Close();
			continue;
		}

		CString strTmp;
		drg.flag = true;

		for (int i=0; !setDiag.IsEOF(); i++)
		{			
			GetPatientStruct(drg, setDiag);	// Ϊ�ṹ�帳ֵ

			sockRecv.Send(&drg, drgSize);		// ���͸ýṹ��
	

			IfReceived(sockRecv);				// �жϿͻ����Ƿ��յ����δ�յ���ȴ�
		

			setDiag.MoveNext();
		}

		setDiag.Close();

		drg.flag = false;					// ���Ϊ����

		sockRecv.Send(&drg, drgSize);
	
		sockRecv.Close();
	}

	return 0;
}

void GetPatientStruct(PatientInfo &drg, CRecordsetDiag &set)
{
	memset(&drg, 0, sizeof (PatientInfo));	// �Դ���ṹ�����㣬�ɱ����ַ�����������
	drg.flag = true;						// true˵����������

	CString strTmp;
	strTmp.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
		set.m_diagNum.GetYear(), set.m_diagNum.GetMonth(), set.m_diagNum.GetDay(),
		set.m_diagNum.GetHour(), set.m_diagNum.GetMinute(), set.m_diagNum.GetSecond());
	memcpy(drg.diagTime, strTmp.GetBuffer(), strTmp.GetLength()*2);
	
	strTmp = set.m_diagDoctorID.TrimRight();
	memcpy(drg.diagDoctorID, strTmp.GetBuffer(), strTmp.GetLength()*2);

	strTmp = set.m_patientName.TrimRight();
	memcpy(drg.patientName, strTmp.GetBuffer(), strTmp.GetLength()*2);

	strTmp = set.m_patientSex.TrimRight();
	memcpy(drg.patientSex, strTmp.GetBuffer(), strTmp.GetLength()*2);

	drg.patientAge = set.m_patientAge;

	strTmp = set.m_idNumber.TrimRight();
	memcpy(drg.idNumber, strTmp.GetBuffer(), strTmp.GetLength()*2);

	strTmp = set.m_patientPhone.TrimRight();
	memcpy(drg.patientPhone, strTmp.GetBuffer(), strTmp.GetLength()*2);

	strTmp = set.m_patientAddress.TrimRight();
	memcpy(drg.patientAddress, strTmp.GetBuffer(), strTmp.GetLength()*2);

	strTmp = set.m_patientNum.TrimRight();
	memcpy(drg.patientNum, strTmp.GetBuffer(), strTmp.GetLength()*2);

	strTmp = set.m_patientAllergy.TrimRight();
	memcpy(drg.patientAllergy, strTmp.GetBuffer(), strTmp.GetLength()*2);

	strTmp = set.m_patientRemark.TrimRight();
	memcpy(drg.patientRemark, strTmp.GetBuffer(), strTmp.GetLength()*2);
}

void IfReceived(CSocket &sockRecv)
{
	bool flag = 1;
	while (flag)
	{
		sockRecv.Receive(&flag, sizeof (bool));
	}
}