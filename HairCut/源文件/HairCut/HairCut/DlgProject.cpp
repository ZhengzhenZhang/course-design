// DlgProject.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgProject.h"
#include "afxdialogex.h"


// CDlgProject �Ի���

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


// CDlgProject ��Ϣ�������


void CDlgProject::OnOK()
{
	UpdateData(TRUE);

	if (m_strInfo.GetLength() <= 0)
	{
		MessageBox(_T("��Ŀ��Ϣ����Ϊ�գ�"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	if (m_strCode.GetLength() <= 0)
	{
		MessageBox(_T("��Ϊ��Ϣ��������룡\n\nΪ��Ϣ�����������Խ�������ĸ��ѯ��������ͨ������Ϣ����ĸ��ɣ�\n���磺����������������Ϊ��JF��"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	if (m_dbPrice < 1e-9)
	{
		if (IDCANCEL == MessageBox(_T("ȷ���۸�Ϊ0��"), _T("��ʾ"), MB_ICONQUESTION | MB_OKCANCEL))
			return;
	}
	if (m_dbVipPrice < 1e-9)
	{
		if (IDCANCEL == MessageBox(_T("ȷ����Ա�۸�Ϊ0��"), _T("��ʾ"), MB_ICONQUESTION | MB_OKCANCEL))
			return;
	}

	if (m_bIsModify)
	{
		if (IDCANCEL == MessageBox(_T("ȷ��Ҫ�޸ĸ���Ŀ��Ϣ��"), _T("��ʾ"), MB_OKCANCEL | MB_ICONQUESTION))
			return;
	}

	CDialogEx::OnOK();
}
