// DlgReg.cpp : 实现文件
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgReg.h"
#include "afxdialogex.h"


// CDlgReg 对话框

IMPLEMENT_DYNAMIC(CDlgReg, CDialogEx)

CDlgReg::CDlgReg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgReg::IDD, pParent)
{

	m_strMachine = _T("");
	m_strReg = _T("");
	m_strRightReg = _T("");
}

CDlgReg::~CDlgReg()
{
}

void CDlgReg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MACHINE, m_strMachine);
	DDX_Text(pDX, IDC_EDIT_REG, m_strReg);
}


BEGIN_MESSAGE_MAP(CDlgReg, CDialogEx)
END_MESSAGE_MAP()


// CDlgReg 消息处理程序


void CDlgReg::OnOK()
{
	UpdateData(TRUE);

	if (_T("") == m_strReg || m_strRightReg != m_strReg)
	{
		AfxMessageBox(_T("注册码不正确，请联系袋鼠集团软件研发中心：18310738133"));
		m_strReg = _T("");
		UpdateData(FALSE);
		return;
	}

	CDialogEx::OnOK();
}
