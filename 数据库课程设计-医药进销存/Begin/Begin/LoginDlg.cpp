// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Begin.h"
#include "LoginDlg.h"
#include "IDkeySet.h"


// CLoginDlg 对话框

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


// CLoginDlg 消息处理程序
// 外部变量
CString login_ID = _T("");


void CLoginDlg::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码

	/////////////
	// 测试用
	//login_ID = _T("009");
	//OnOK();
	//return;

	///////////////

	UpdateData(TRUE);
	CIDkeySet setID;
	
	setID.m_strFilter.Format(_T("ID='%s'"), m_ID);
	if (!setID.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

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
			MessageBox(_T("密码有误！"), _T("提示"), MB_OK);
			GetDlgItem(IDC_EDIT_KEY)->SetFocus();
			SendDlgItemMessage(IDC_EDIT_KEY, EM_SETSEL, 0, -1);
		}
	}
	else
	{
		MessageBox(_T("账号不存在！"), _T("提示"), MB_OK);
		GetDlgItem(IDC_EDIT_ID)->SetFocus();
		SendDlgItemMessage(IDC_EDIT_ID, EM_SETSEL, 0, -1);
	}
	setID.Close();
}

void CLoginDlg::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	PostQuitMessage(0);
}

void CLoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//PostQuitMessage(0);
	exit(0);	
	// 直接退出，上面的post只是把退出消息放到消息队列，所以会出现闪屏现象不过更安全
	CDialog::OnClose();
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
