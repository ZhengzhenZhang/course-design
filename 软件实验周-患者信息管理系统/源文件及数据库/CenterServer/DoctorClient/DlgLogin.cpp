// DlgLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DoctorClient.h"
#include "DlgLogin.h"
#include "RecordsetWorkerId.h"


// CDlgLogin �Ի���

IMPLEMENT_DYNAMIC(CDlgLogin, CDialog)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
	, m_strDocId(_T(""))
	, m_strDocPas(_T(""))
{
	m_Style = 1;
}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DOCTORID, m_strDocId);

	DDX_Text(pDX, IDC_EDIT_DOCTORPAS, m_strDocPas);
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
		m_strDocId, m_Style);;
	if (!setID.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	if (!setID.IsEOF())
	{
		setID.m_workerPas.TrimRight();
		if (setID.m_workerPas == m_strDocPas)
		{
			//login_ID = m_ID;
			OnOK();
		}
		else
		{
			MessageBox(_T("��������"), _T("��ʾ"), MB_OK);
			// ����ʵ�ֶ��˺ź�����༭��ؼ����ý����ȫѡ
			GetDlgItem(IDC_EDIT_DOCTORPAS)->SetFocus();
			SendDlgItemMessage(IDC_EDIT_DOCTORPAS, EM_SETSEL, 0, -1);
		}
	}
	else
	{
		MessageBox(_T("�˺Ų����ڣ�"), _T("��ʾ"), MB_OK);
		GetDlgItem(IDC_EDIT_DOCTORID)->SetFocus();
		SendDlgItemMessage(IDC_EDIT_DOCTORID, EM_SETSEL, 0, -1);
	}
	setID.Close();
}

void CDlgLogin::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
	OnCancel();
}
