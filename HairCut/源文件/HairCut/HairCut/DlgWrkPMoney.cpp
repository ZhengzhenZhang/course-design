// DlgWrkPMoney.cpp : 实现文件
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgWrkPMoney.h"
#include "afxdialogex.h"


// CDlgWrkPMoney 对话框

IMPLEMENT_DYNAMIC(CDlgWrkPMoney, CDialogEx)

CDlgWrkPMoney::CDlgWrkPMoney(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgWrkPMoney::IDD, pParent)
{

	m_strName = _T("");
	m_strPhone = _T("");
	m_dbPMoney = 0.0;
}

CDlgWrkPMoney::~CDlgWrkPMoney()
{
}

void CDlgWrkPMoney::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 4);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
	DDV_MaxChars(pDX, m_strPhone, 11);
	DDX_Text(pDX, IDC_EDIT_PMONEY, m_dbPMoney);
	DDV_MinMaxDouble(pDX, m_dbPMoney, 0, 100000000);
}


BEGIN_MESSAGE_MAP(CDlgWrkPMoney, CDialogEx)
END_MESSAGE_MAP()


// CDlgWrkPMoney 消息处理程序


void CDlgWrkPMoney::OnOK()
{
	UpdateData(TRUE);

	if (m_dbPMoney < 1e-9)
	{
		MessageBox(_T("金额不能为0！"), _T("提示"), MB_ICONINFORMATION);
		return;
	}

	CString strTmp;
		
	strTmp.Format(_T("请再次确认工资金额！\n\n工资金额：%.2lf"), m_dbPMoney);

	if (IDCANCEL == MessageBox(strTmp, _T("提示"), MB_ICONINFORMATION))
		return;
	CDialogEx::OnOK();
}
