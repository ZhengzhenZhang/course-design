// DlgProject.cpp : 实现文件
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgProject.h"
#include "afxdialogex.h"


// CDlgProject 对话框

IMPLEMENT_DYNAMIC(CDlgProject, CDialogEx)

CDlgProject::CDlgProject(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgProject::IDD, pParent)
{

	m_strCode = _T("");
	m_strInfo = _T("");
	m_dbPrice = 0.0;
	m_dbVipPrice = 0.0;
	m_bIsModify = false;
}

CDlgProject::~CDlgProject()
{
}

void CDlgProject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CODE, m_strCode);
	DDV_MaxChars(pDX, m_strCode, 4);
	DDX_Text(pDX, IDC_EDIT_INFO, m_strInfo);
	DDV_MaxChars(pDX, m_strInfo, 24);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_dbPrice);
	DDV_MinMaxDouble(pDX, m_dbPrice, 0, 100000);
	DDX_Text(pDX, IDC_EDIT_VIPPRICE, m_dbVipPrice);
	DDV_MinMaxDouble(pDX, m_dbVipPrice, 0, 100000);
}


BEGIN_MESSAGE_MAP(CDlgProject, CDialogEx)
END_MESSAGE_MAP()


// CDlgProject 消息处理程序


void CDlgProject::OnOK()
{
	UpdateData(TRUE);

	if (m_strInfo.GetLength() <= 0)
	{
		MessageBox(_T("项目信息不能为空！"), _T("提示"), MB_ICONINFORMATION);
		return;
	}
	if (m_strCode.GetLength() <= 0)
	{
		MessageBox(_T("请为信息添加助记码！\n\n为信息添加助记码可以进行首字母查询，助记码通常用信息首字母组成！\n例如：“剪发”的助记码为“JF”"), _T("提示"), MB_ICONINFORMATION);
		return;
	}
	if (m_dbPrice < 1e-9)
	{
		if (IDCANCEL == MessageBox(_T("确定价格为0？"), _T("提示"), MB_ICONQUESTION | MB_OKCANCEL))
			return;
	}
	if (m_dbVipPrice < 1e-9)
	{
		if (IDCANCEL == MessageBox(_T("确定会员价格为0？"), _T("提示"), MB_ICONQUESTION | MB_OKCANCEL))
			return;
	}

	if (m_bIsModify)
	{
		if (IDCANCEL == MessageBox(_T("确定要修改该项目信息？"), _T("提示"), MB_OKCANCEL | MB_ICONQUESTION))
			return;
	}

	CDialogEx::OnOK();
}
