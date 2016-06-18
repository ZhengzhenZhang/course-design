// DlgLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "ClassRoom.h"
#include "DlgLogin.h"
#include "RecordsetAdminId.h"


// CDlgLogin 对话框

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


// CDlgLogin 消息处理程序

//---------------
//---功能：登陆界面实现---
//---完成人：吴稀钰---
//---完成时间：2012-12-25---
//---修改时间：---
//---------------
void CDlgLogin::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CRecordsetAdminId setID;

	setID.m_strFilter.Format(_T("adminID='%s'"), m_strAdminId);
	if (!setID.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

	if (!setID.IsEOF())
	{
		setID.m_adminPassword.TrimRight();
		if (setID.m_adminPassword == m_strAdminPas)
		{

			OnOK();
		}
		else
		{
			MessageBox(_T("密码有误！"), _T("提示"), MB_OK);
			// 下面实现对账号和密码编辑框控件设置焦点和全选
			GetDlgItem(IDC_EDIT_ADMINPAS)->SetFocus();
			SendDlgItemMessage(IDC_EDIT_ADMINPAS, EM_SETSEL, 0, -1);
		}
	}
	else
	{
		MessageBox(_T("账号不存在！"), _T("提示"), MB_OK);
		GetDlgItem(IDC_EDIT_ADMIN)->SetFocus();
		SendDlgItemMessage(IDC_EDIT_ADMIN, EM_SETSEL, 0, -1);
	}
	setID.Close();
}
void CDlgLogin::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);	// 如果用户单击取消按钮则退出程序
	OnCancel();
}
