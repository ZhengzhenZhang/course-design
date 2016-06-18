// DlgWorker.cpp : 实现文件
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgWorker.h"
#include "afxdialogex.h"


// CDlgWorker 对话框

IMPLEMENT_DYNAMIC(CDlgWorker, CDialogEx)

CDlgWorker::CDlgWorker(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgWorker::IDD, pParent)
{
	m_strPhone = _T("");
	m_strName = _T("");
	m_strCode = _T("");
}

CDlgWorker::~CDlgWorker()
{
}

void CDlgWorker::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
	DDV_MaxChars(pDX, m_strPhone, 11);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 4);
	DDX_Text(pDX, IDC_EDIT_CODE, m_strCode);
	DDV_MaxChars(pDX, m_strCode, 4);
}


BEGIN_MESSAGE_MAP(CDlgWorker, CDialogEx)
END_MESSAGE_MAP()


// CDlgWorker 消息处理程序


void CDlgWorker::OnOK()
{
	UpdateData(TRUE);

	if (m_strName.GetLength() <= 0)
	{
		MessageBox(_T("员工名不能为空！"), _T("提示"), MB_ICONINFORMATION);
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

	CDialogEx::OnOK();
}
