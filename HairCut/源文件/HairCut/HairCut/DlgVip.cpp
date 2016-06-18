// DlgVip.cpp : 实现文件
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgVip.h"
#include "afxdialogex.h"


// CDlgVip 对话框

IMPLEMENT_DYNAMIC(CDlgVip, CDialogEx)

CDlgVip::CDlgVip(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgVip::IDD, pParent)
{

	//  m_strCode = _T("");
	m_strName = _T("");
	m_dbMoney = 0.0;
	m_strPhone = _T("");
	m_strCode = _T("");
}

CDlgVip::~CDlgVip()
{
}

void CDlgVip::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 4);
	DDX_Text(pDX, IDC_EDIT_MONEY, m_dbMoney);
	DDV_MinMaxDouble(pDX, m_dbMoney, 0, 10000000);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
	DDV_MaxChars(pDX, m_strPhone, 11);
	DDX_Text(pDX, IDC_EDIT_CODE, m_strCode);
	DDV_MaxChars(pDX, m_strCode, 4);
}


BEGIN_MESSAGE_MAP(CDlgVip, CDialogEx)
END_MESSAGE_MAP()


// CDlgVip 消息处理程序


void CDlgVip::OnOK()
{
	UpdateData(TRUE);

	if (m_strName.GetLength() <= 0)
	{
		MessageBox(_T("会员名不能为空！"), _T("提示"), MB_ICONINFORMATION);
		return;
	}
	if (m_strCode.GetLength() <= 0)
	{
		MessageBox(_T("请为信息添加助记码！\n\n为信息添加助记码可以进行首字母查询，助记码通常用信息首字母组成！\n例如：“张三”的助记码为“ZS”"), _T("提示"), MB_ICONINFORMATION);
		return;
	}
	if (m_strPhone.GetLength() <= 0)
	{
		MessageBox(_T("联系方式不能为空！"), _T("提示"), MB_ICONINFORMATION);
		return;
	}
	if (m_dbMoney < 1e-9)
	{
		MessageBox(_T("充值金额不能为0！"), _T("提示"), MB_ICONINFORMATION);
		return;
	}
	
	CString strTmp;
	strTmp.Format(_T("请再次确认新会员信息！\n\n新会员名： %s\n联系方式： %s\n充值金额： %.2lf"),
		m_strName, m_strPhone, m_dbMoney);
	if (IDCANCEL == MessageBox(strTmp, _T("提示"), MB_ICONINFORMATION | MB_OKCANCEL))
	{
		return;
	}

	CDialogEx::OnOK();
}
