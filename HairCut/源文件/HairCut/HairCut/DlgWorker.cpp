// DlgWorker.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgWorker.h"
#include "afxdialogex.h"


// CDlgWorker �Ի���

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


// CDlgWorker ��Ϣ�������


void CDlgWorker::OnOK()
{
	UpdateData(TRUE);

	if (m_strName.GetLength() <= 0)
	{
		MessageBox(_T("Ա��������Ϊ�գ�"), _T("��ʾ"), MB_ICONINFORMATION);
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

	CDialogEx::OnOK();
}
