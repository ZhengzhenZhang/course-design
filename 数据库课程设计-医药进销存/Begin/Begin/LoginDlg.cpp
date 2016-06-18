// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Begin.h"
#include "LoginDlg.h"
#include "IDkeySet.h"


// CLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CLoginDlg, CDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
	, m_ID(_T(""))
	, m_key(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_ID);
	DDX_Text(pDX, IDC_EDIT_KEY, m_key);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLoginDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CLoginDlg::OnBnClickedButtonCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������
// �ⲿ����
CString login_ID = _T("");


void CLoginDlg::OnBnClickedButtonLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	/////////////
	// ������
	//login_ID = _T("009");
	//OnOK();
	//return;

	///////////////

	UpdateData(TRUE);
	CIDkeySet setID;
	
	setID.m_strFilter.Format(_T("ID='%s'"), m_ID);
	if (!setID.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	if (!setID.IsEOF())
	{
		setID.m_PASSWORD.TrimRight();
		if (setID.m_PASSWORD == m_key)
		{
			login_ID = m_ID;
			OnOK();
		}
		else
		{
			MessageBox(_T("��������"), _T("��ʾ"), MB_OK);
			GetDlgItem(IDC_EDIT_KEY)->SetFocus();
			SendDlgItemMessage(IDC_EDIT_KEY, EM_SETSEL, 0, -1);
		}
	}
	else
	{
		MessageBox(_T("�˺Ų����ڣ�"), _T("��ʾ"), MB_OK);
		GetDlgItem(IDC_EDIT_ID)->SetFocus();
		SendDlgItemMessage(IDC_EDIT_ID, EM_SETSEL, 0, -1);
	}
	setID.Close();
}

void CLoginDlg::OnBnClickedButtonCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PostQuitMessage(0);
}

void CLoginDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//PostQuitMessage(0);
	exit(0);	
	// ֱ���˳��������postֻ�ǰ��˳���Ϣ�ŵ���Ϣ���У����Ի�����������󲻹�����ȫ
	CDialog::OnClose();
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
