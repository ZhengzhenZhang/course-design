// DlgVipPMoney.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgVipPMoney.h"
#include "afxdialogex.h"


// CDlgVipPMoney �Ի���

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


// CDlgVipPMoney ��Ϣ�������


BOOL CDlgVipPMoney::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	if (m_bDMoney)
	{
		SetWindowText(_T("��Ա����"));
		GetDlgItem(IDC_STATIC_PDMONEY)->SetWindowText(_T("���ֽ��"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgVipPMoney::OnOK()
{
	UpdateData(TRUE);

	if (m_dbPMoney < 1e-9)
	{
		MessageBox(_T("����Ϊ0��"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}

	CString strTmp;
	if (m_bDMoney)
		strTmp.Format(_T("��ȷ��������Ϣ��\n\n���ֽ�%.2lf  ���ֺ���%.2lf"), m_dbPMoney, m_dbBalance - m_dbPMoney);
	else		
		strTmp.Format(_T("��ȷ�ϳ�ֵ��Ϣ��\n\n��ֵ��%.2lf  ��ֵ����%.2lf"), m_dbPMoney, m_dbBalance + m_dbPMoney);
	
	if (IDCANCEL == MessageBox(strTmp, _T("��ʾ"), MB_ICONINFORMATION))
		return;

	CDialogEx::OnOK();
}
