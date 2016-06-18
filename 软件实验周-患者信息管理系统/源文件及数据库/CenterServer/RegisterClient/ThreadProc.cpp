#include "StdAfx.h"
#include "ThreadProc.h"

#include "RegisterClientDoc.h"
#include "RegisterClientView.h"


CThreadProc::CThreadProc(void)
{
}

CThreadProc::~CThreadProc(void)
{
}
extern PatientInfo drg[];
extern int tNum;
UINT ThreadProc1(LPVOID pParam)
{
	CRegisterClientView* rcview = (CRegisterClientView*)pParam;

	AfxSocketInit();
	CSocket sockClient;
	sockClient.Create();
	while (!sockClient.Connect(_T("192.168.137.3"), 5000))
	{
		Sleep(10);		// ÿ��10ms����һ��
	}

	
	drg[0].flag = false;
	int drgSize = sizeof (PatientInfo);  // �õ�������Ϣ�ṹ���С

	sockClient.Receive(&drg[0], drgSize);

	HaveReceived(sockClient);			// ���߷�������յ�������Ϣ

	CListCtrl& listCtrl = rcview->GetListCtrl();
	listCtrl.DeleteAllItems();
	CString strTmp;
	int i = 0;
	while (drg[i].flag)					// �ж��Ƿ����������
	{
		strTmp.Format(_T("%d"), i + 1);
		listCtrl.InsertItem(i, strTmp);
		
		strTmp = drg[i].diagTime;
		listCtrl.SetItemText(i, 1, strTmp);

		strTmp = drg[i].patientName;
		listCtrl.SetItemText(i, 2, strTmp);

		strTmp = drg[i].patientSex;
		listCtrl.SetItemText(i, 3, strTmp);

		strTmp.Format(_T("%d"), drg[i].patientAge);
		listCtrl.SetItemText(i, 4, strTmp);
		
		strTmp = drg[i].idNumber;
		listCtrl.SetItemText(i, 5, strTmp);
	
		strTmp = drg[i].patientPhone;
		listCtrl.SetItemText(i, 6, strTmp);

		strTmp = drg[i].diagDoctorID;
		listCtrl.SetItemText(i, 7, strTmp);

		i++;
		drg[i].flag = false;	// ������һֱ����ȥ
		sockClient.Receive(&drg[i], drgSize);
		HaveReceived(sockClient);
	}
	
	tNum = i;

	sockClient.Close();
	return 0;
}

void HaveReceived(CSocket &sockClient)
{
	bool flag = 0;
	sockClient.Send(&flag, sizeof (bool));
}