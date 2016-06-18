// DlgPay.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgPay.h"
#include "afxdialogex.h"


// CDlgPay �Ի���

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


// CDlgPay ��Ϣ�������


void CDlgPay::OnOK()
{
	UpdateData(TRUE);
	
	if (m_strInfo.GetLength() <= 0)
	{
		MessageBox(_T("֧����Ϣ����Ϊ�գ�"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}

	if (m_dbMoney < 1e-9)
	{
		MessageBox(_T("����Ϊ0��"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}

	CString strTmp;
	strTmp.Format(_T("���ٴ�ȷ�ϸ�֧����Ϣ��\n\n֧���� %.2lf\n\n֧����Ϣ�� %s"),
		m_dbMoney, m_strInfo);

	if (IDCANCEL == MessageBox(strTmp, _T("��ʾ"), MB_ICONINFORMATION | MB_OKCANCEL))
	{
		return;
	}
	
	CDialogEx::OnOK();
}
