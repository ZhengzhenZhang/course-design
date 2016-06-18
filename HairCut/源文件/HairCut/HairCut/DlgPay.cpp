// DlgPay.cpp : 实现文件
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgPay.h"
#include "afxdialogex.h"


// CDlgPay 对话框

IMPLEMENT_DYNAMIC(CDlgPay, CDialogEx)

CDlgPay::CDlgPay(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPay::IDD, pParent)
{

	//  m_dbMoney = 0.0;
	m_strInfo = _T("");
	m_dbMoney = 0.0;
}

CDlgPay::~CDlgPay()
{
}

void CDlgPay::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INFO, m_strInfo);
	DDV_MaxChars(pDX, m_strInfo, 24);
	DDX_Text(pDX, IDC_EDIT_MONEY, m_dbMoney);
	DDV_MinMaxDouble(pDX, m_dbMoney, 0, 10000000);
}


BEGIN_MESSAGE_MAP(CDlgPay, CDialogEx)

END_MESSAGE_MAP()


// CDlgPay 消息处理程序


void CDlgPay::OnOK()
{
	UpdateData(TRUE);
	
	if (m_strInfo.GetLength() <= 0)
	{
		MessageBox(_T("支出信息不能为空！"), _T("提示"), MB_ICONINFORMATION);
		return;
	}

	if (m_dbMoney < 1e-9)
	{
		MessageBox(_T("金额不能为0！"), _T("提示"), MB_ICONINFORMATION);
		return;
	}

	CString strTmp;
	strTmp.Format(_T("请再次确认该支出信息！\n\n支出金额： %.2lf\n\n支出信息： %s"),
		m_dbMoney, m_strInfo);

	if (IDCANCEL == MessageBox(strTmp, _T("提示"), MB_ICONINFORMATION | MB_OKCANCEL))
	{
		return;
	}
	
	CDialogEx::OnOK();
}
