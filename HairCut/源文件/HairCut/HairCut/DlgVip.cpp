// DlgVip.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgVip.h"
#include "afxdialogex.h"


// CDlgVip �Ի���

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


// CDlgVip ��Ϣ�������


void CDlgVip::OnOK()
{
	UpdateData(TRUE);

	if (m_strName.GetLength() <= 0)
	{
		MessageBox(_T("��Ա������Ϊ�գ�"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	if (m_strCode.GetLength() <= 0)
	{
		MessageBox(_T("��Ϊ��Ϣ��������룡\n\nΪ��Ϣ�����������Խ�������ĸ��ѯ��������ͨ������Ϣ����ĸ��ɣ�\n���磺����������������Ϊ��ZS��"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	if (m_strPhone.GetLength() <= 0)
	{
		MessageBox(_T("��ϵ��ʽ����Ϊ�գ�"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	if (m_dbMoney < 1e-9)
	{
		MessageBox(_T("��ֵ����Ϊ0��"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	
	CString strTmp;
	strTmp.Format(_T("���ٴ�ȷ���»�Ա��Ϣ��\n\n�»�Ա���� %s\n��ϵ��ʽ�� %s\n��ֵ�� %.2lf"),
		m_strName, m_strPhone, m_dbMoney);
	if (IDCANCEL == MessageBox(strTmp, _T("��ʾ"), MB_ICONINFORMATION | MB_OKCANCEL))
	{
		return;
	}

	CDialogEx::OnOK();
}
