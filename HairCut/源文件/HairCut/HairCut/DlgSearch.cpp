// DlgSearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgSearch.h"
#include "afxdialogex.h"


// CDlgSearch �Ի���

IMPLEMENT_DYNAMIC(CDlgSearch, CDialogEx)

CDlgSearch::CDlgSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSearch::IDD, pParent)
{

	m_strSearch = _T("");
}

CDlgSearch::~CDlgSearch()
{
}

void CDlgSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_SEARCH, m_strSearch);
	DDV_MaxChars(pDX, m_strSearch, 24);
}


BEGIN_MESSAGE_MAP(CDlgSearch, CDialogEx)
END_MESSAGE_MAP()


// CDlgSearch ��Ϣ�������


void CDlgSearch::OnOK()
{
	UpdateData(TRUE);

	SEARCHINFO sInfo;
	sInfo.strSearchInfo = m_strSearch;
	AfxGetMainWnd()->SendMessage(WM_USER_SEARCH, 0, (LPARAM)&sInfo);
}


void CDlgSearch::OnCancel()
{
	DestroyWindow();
}


void CDlgSearch::PostNcDestroy()
{
	CDialogEx::PostNcDestroy();

	AfxGetMainWnd()->SendMessage(WM_USER_DIALOG_DESTROYED, 0, 0);
	delete this;
}
