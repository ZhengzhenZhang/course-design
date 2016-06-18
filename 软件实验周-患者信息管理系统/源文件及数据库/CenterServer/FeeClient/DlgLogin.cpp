// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FeeClient.h"
#include "DlgLogin.h"
#include "RecordsetWorkerId.h"


// CDlgLogin �Ի���

IMPLEMENT_DYNAMIC(CDlgLogin, CDialog)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
	, m_strFeeId(_T(""))
	, m_strFeePas(_T(""))
{
	m_Style = 2;
}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FEEID, m_strFeeId);
	DDX_Text(pDX, IDC_EDIT_FEEPAS, m_strFeePas);
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
		m_strFeeId, m_Style);
	if (!setID.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	if (!setID.IsEOF())
	{
		setID.m_workerPas.TrimRight();
		if (setID.m_workerPas == m_strFeePas)
		{
			//login_ID = m_ID;
			OnOK();
		}
		else
		{
			MessageBox(_T("��������"), _T("��ʾ"), MB_OK);
			// ����ʵ�ֶ��˺ź�����༭��ؼ����ý����ȫѡ
			GetDlgItem(IDC_EDIT_FEEPAS)->SetFocus();
			SendDlgItemMessage(IDC_EDIT_FEEPAS, EM_SETSEL, 0, -1);
		}
	}
	else
	{
		MessageBox(_T("�˺Ų����ڣ�"), _T("��ʾ"), MB_OK);
		GetDlgItem(IDC_EDIT_FEEID)->SetFocus();
		SendDlgItemMessage(IDC_EDIT_FEEID, EM_SETSEL, 0, -1);
	}
	setID.Close();
}

void CDlgLogin::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
	OnCancel();
}
