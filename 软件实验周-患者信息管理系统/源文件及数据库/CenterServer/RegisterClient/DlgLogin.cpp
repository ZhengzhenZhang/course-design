// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RegisterClient.h"
#include "DlgLogin.h"

#include "RecordsetWorkerId.h"

// CDlgLogin �Ի���

IMPLEMENT_DYNAMIC(CDlgLogin, CDialog)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
	, m_strRegId(_T(""))
	, m_strRegPas(_T(""))
{
	m_Style = 0;
}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_REGID, m_strRegId);
	DDX_Text(pDX, IDC_EDIT_REGPAS, m_strRegPas);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgLogin::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgLogin::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgLogin ��Ϣ�������

void CDlgLogin::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CRecordsetWorkerId setID;

	setID.m_strFilter.Format(_T("workerID='%s' AND workerStyle='%d'"), 
		m_strRegId, m_Style);
	if (!setID.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	if (!setID.IsEOF())
	{
		setID.m_workerPas.TrimRight();
		if (setID.m_workerPas == m_strRegPas)
		{
			//login_ID = m_ID;
			OnOK();
		}
		else
		{
			MessageBox(_T("��������"), _T("��ʾ"), MB_OK);
			// ����ʵ�ֶ��˺ź�����༭��ؼ����ý����ȫѡ
			GetDlgItem(IDC_EDIT_REGPAS)->SetFocus();
			SendDlgItemMessage(IDC_EDIT_REGPAS, EM_SETSEL, 0, -1);
		}
	}
	else
	{
		MessageBox(_T("�˺Ų����ڣ�"), _T("��ʾ"), MB_OK);
		GetDlgItem(IDC_EDIT_REGID)->SetFocus();
		SendDlgItemMessage(IDC_EDIT_REGID, EM_SETSEL, 0, -1);
	}

	setID.Close();
}

void CDlgLogin::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
