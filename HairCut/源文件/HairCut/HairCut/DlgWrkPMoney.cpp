// DlgWrkPMoney.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgWrkPMoney.h"
#include "afxdialogex.h"


// CDlgWrkPMoney �Ի���

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


// CDlgWrkPMoney ��Ϣ�������


void CDlgWrkPMoney::OnOK()
{
	UpdateData(TRUE);

	if (m_dbPMoney < 1e-9)
	{
		MessageBox(_T("����Ϊ0��"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}

	CString strTmp;
		
	strTmp.Format(_T("���ٴ�ȷ�Ϲ��ʽ�\n\n���ʽ�%.2lf"), m_dbPMoney);

	if (IDCANCEL == MessageBox(strTmp, _T("��ʾ"), MB_ICONINFORMATION))
		return;
	CDialogEx::OnOK();
}
