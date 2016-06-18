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
	sockServ.Listen();				// 开始监听客户端请求

	PatientInfo drg;				// 要传输数据的缓冲区
	int drgSize = sizeof (PatientInfo);
	// 得到患者信息结构体大小
	CSocket sockRecv;				// 定义一个接收socket

	while (true)
	{
	
		sockServ.Accept(sockRecv);	// 接收客户端请求并和底层套接字进行绑定

		CRecordsetDiag setDiag;
		setDiag.m_strFilter = _T(""); // sql语句条件
		if (!setDiag.Open())
		{
			AfxMessageBox(_T("连接数据库时错误"), MB_OK);
			setDiag.Close();
			continue;
		}

		CString strTmp;
		drg.flag = true;

		for (int i=0; !setDiag.IsEOF(); i++)
		{			
			GetPatientStruct(drg, setDiag);	// 为结构体赋值

			sockRecv.Send(&drg, drgSize);		// 发送该结构体
	

			IfReceived(sockRecv);				// 判断客户端是否收到如果未收到则等待
		

			setDiag.MoveNext();
		}

		setDiag.Close();

		drg.flag = false;					// 标记为结束

		sockRecv.Send(&drg, drgSize);
	
		sockRecv.Close();
	}

	return 0;
}

void GetPatientStruct(PatientInfo &drg, CRecordsetDiag &set)
{
	memset(&drg, 0, sizeof (PatientInfo));	// 对传输结构体清零，可避免字符串结束问题
	drg.flag = true;						// true说明还有数据

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