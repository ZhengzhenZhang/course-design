// DlgVipPMoney.cpp : 实现文件
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgVipPMoney.h"
#include "afxdialogex.h"


// CDlgVipPMoney 对话框

IMPLEMENT_DYNAMIC(CDlgVipPMoney, CDialogEx)

CDlgVipPMoney::CDlgVipPMoney(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgVipPMoney::IDD, pParent)
{
	m_strName = _T("");
	m_dbBalance = 0.0;
	m_strPhone = _T("");
	m_dbPMoney = 0.0;
	m_bDMoney = FALSE;
}

CDlgVipPMoney::~CDlgVipPMoney()
{
}

void CDlgVipPMoney::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_BALANCE, m_dbBalance);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
	DDX_Text(pDX, IDC_EDIT_PMONEY, m_dbPMoney);
	DDV_MinMaxDouble(pDX, m_dbPMoney, 0, 10000000);
}


BEGIN_MESSAGE_MAP(CDlgVipPMoney, CDialogEx)
END_MESSAGE_MAP()


// CDlgVipPMoney 消息处理程序


BOOL CDlgVipPMoney::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	if (m_bDMoney)
	{
		SetWindowText(_T("会员提现"));
		GetDlgItem(IDC_STATIC_PDMONEY)->SetWindowText(_T("提现金额"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgVipPMoney::OnOK()
{
	UpdateData(TRUE);

	if (m_dbPMoney < 1e-9)
	{
		MessageBox(_T("金额不能为0！"), _T("提示"), MB_ICONINFORMATION);
		return;
	}

	CString strTmp;
	if (m_bDMoney)
		strTmp.Format(_T("请确认提现信息！\n\n提现金额：%.2lf  提现后余额：%.2lf"), m_dbPMoney, m_dbBalance - m_dbPMoney);
	else		
		strTmp.Format(_T("请确认充值信息！\n\n充值金额：%.2lf  充值后余额：%.2lf"), m_dbPMoney, m_dbBalance + m_dbPMoney);
	
	if (IDCANCEL == MessageBox(strTmp, _T("提示"), MB_ICONINFORMATION))
		return;

	CDialogEx::OnOK();
}
