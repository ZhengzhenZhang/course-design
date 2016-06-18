// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ClassRoom.h"
#include "DlgLogin.h"
#include "RecordsetAdminId.h"


// CDlgLogin �Ի���

IMPLEMENT_DYNAMIC(CDlgLogin, CDialog)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
	, m_strAdminId(_T(""))
	, m_strAdminPas(_T(""))
{

}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ADMIN, m_strAdminId);
	DDX_Text(pDX, IDC_EDIT_ADMINPAS, m_strAdminPas);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgLogin::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgLogin::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgLogin ��Ϣ�������

//---------------
//---���ܣ���½����ʵ��---
//---����ˣ���ϡ��---
//---���ʱ�䣺2012-12-25---
//---�޸�ʱ�䣺---
//---------------
void CDlgLogin::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CRecordsetAdminId setID;

	setID.m_strFilter.Format(_T("adminID='%s'"), m_strAdminId);
	if (!setID.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	if (!setID.IsEOF())
	{
		setID.m_adminPassword.TrimRight();
		if (setID.m_adminPassword == m_strAdminPas)
		{

			OnOK();
		}
		else
		{
			MessageBox(_T("��������"), _T("��ʾ"), MB_OK);
			// ����ʵ�ֶ��˺ź�����༭��ؼ����ý����ȫѡ
			GetDlgItem(IDC_EDIT_ADMINPAS)->SetFocus();
			SendDlgItemMessage(IDC_EDIT_ADMINPAS, EM_SETSEL, 0, -1);
		}
	}
	else
	{
		MessageBox(_T("�˺Ų����ڣ�"), _T("��ʾ"), MB_OK);
		GetDlgItem(IDC_EDIT_ADMIN)->SetFocus();
		SendDlgItemMessage(IDC_EDIT_ADMIN, EM_SETSEL, 0, -1);
	}
	setID.Close();
}
void CDlgLogin::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);	// ����û�����ȡ����ť���˳�����
	OnCancel();
}
