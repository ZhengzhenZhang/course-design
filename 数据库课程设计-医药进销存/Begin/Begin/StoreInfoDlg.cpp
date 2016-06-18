// StoreInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Begin.h"
#include "StoreInfoDlg.h"
#include "UpdateDlg.h"


// CStoreInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CStoreInfoDlg, CDialog)

CStoreInfoDlg::CStoreInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStoreInfoDlg::IDD, pParent)
	, m_code(_T("��׼�ĺ�"))
	, m_radio(0)
	, m_tNum(0)
{

}

CStoreInfoDlg::~CStoreInfoDlg()
{
}

void CStoreInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDE_STORE_SEARCH, m_code);
	DDX_Control(pDX, IDL_STORE_INFO, m_list);
	DDX_Radio(pDX, IDR_STORE_ALL, m_radio);
	DDX_Text(pDX, IDE_STORE_TNUM, m_tNum);
}


BEGIN_MESSAGE_MAP(CStoreInfoDlg, CDialog)
	ON_BN_CLICKED(IDR_STORE_ALL, &CStoreInfoDlg::OnBnClickedStoreAll)
	ON_BN_CLICKED(IDB_STORE_SEARCH, &CStoreInfoDlg::OnBnClickedStoreSearch)
	ON_BN_CLICKED(IDR_STORE_LACK, &CStoreInfoDlg::OnBnClickedStoreLack)
	ON_BN_CLICKED(IDR_STORE_NORMAL, &CStoreInfoDlg::OnBnClickedStoreNormal)
	ON_BN_CLICKED(IDR_STORE_EX, &CStoreInfoDlg::OnBnClickedStoreEx)
	ON_NOTIFY(NM_DBLCLK, IDL_STORE_INFO, &CStoreInfoDlg::OnNMDblclkStoreInfo)
END_MESSAGE_MAP()


// CStoreInfoDlg ��Ϣ�������

BOOL CStoreInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list.InsertColumn(0, _T("��׼�ĺ�"), LVCFMT_CENTER, 83);
	m_list.InsertColumn(1, _T("ҩƷ����"), LVCFMT_CENTER, 83);
	m_list.InsertColumn(2, _T("ҩƷ���"), LVCFMT_CENTER, 143);
	m_list.InsertColumn(3, _T("ҩƷ���"), LVCFMT_CENTER, 83);
	m_list.InsertColumn(4, _T("ҩƷ����"), LVCFMT_CENTER, 83);
	//m_list.SetBkColor(RGB(26, 231, 151));
	//m_list.SetTextBkColor(RGB(26, 231, 151));
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES);

	OnBnClickedStoreAll();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CStoreInfoDlg::ListTheInfo()
{
	if (!set.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
	m_list.DeleteAllItems();

	m_tNum = 0;
	for(int i=0; !set.IsEOF(); i++,set.MoveNext())
	{
		set.m_code.TrimRight();
		m_list.InsertItem(i, set.m_code);
		set.m_name.TrimRight();
		m_list.SetItemText(i, 1, set.m_name);
		set.m_specification.TrimRight();
		m_list.SetItemText(i, 2, set.m_specification);
		CString cs;
		cs.Format(_T("%d"), set.m_counts);
		cs.TrimRight();
		m_list.SetItemText(i, 3, cs);

		cs.Format(_T("%.2f"), set.m_selPrice);
		cs.TrimRight();
		m_list.SetItemText(i, 4, cs);
		
		m_tNum++;
	}
	
	set.Close();
	UpdateData(FALSE);
}

void CStoreInfoDlg::OnBnClickedStoreAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_radio = 0;
	set.m_strFilter.Format(_T(""));
	ListTheInfo();
}

void CStoreInfoDlg::OnBnClickedStoreLack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_radio = 1;
	set.m_strFilter.Format(_T("counts < 20"));
	set.m_strSort.Format(_T("counts asc")); // ���ٵ���������
	ListTheInfo();
	set.m_strSort.Format(_T("code asc"));
}

void CStoreInfoDlg::OnBnClickedStoreNormal()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_radio = 2;
	set.m_strFilter.Format(_T("counts >= 20 and counts < 100"));
	ListTheInfo();
}

void CStoreInfoDlg::OnBnClickedStoreEx()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_radio = 3;
	set.m_strFilter.Format(_T("counts >= 100"));
	set.m_strSort.Format(_T("counts desc"));	// ���������������
	ListTheInfo();
	set.m_strSort.Format(_T("code asc"));
}


void CStoreInfoDlg::OnBnClickedStoreSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	set.m_strFilter = _T("code like '%");

	set.m_strFilter += m_code;
	set.m_strFilter += "%'";  

	ListTheInfo();
	GetDlgItem(IDE_STORE_SEARCH)->SetFocus();
	SendDlgItemMessage(IDE_STORE_SEARCH, EM_SETSEL, 0, -1);
}


void CStoreInfoDlg::OnNMDblclkStoreInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// �ӿ����Ϣ��ֱ�Ӹ�������ҩƷ��Ϣ
	int n = m_list.GetSelectionMark();
	if (n >= 0)
	{
		CUpdateDlg dlg;
		dlg.m_ifStore = TRUE;

		dlg.m_search = m_list.GetItemText(n,0);
		dlg.DoModal();
	}
	else
	{
		MessageBox(_T("�޿����Ϣ�򵥻�ѡ��ҩƷ��׼�ĺ�"), 
			_T("��ʾ"), MB_OK);
	}
	
	
	// ����ҩƷ�󻹱���ԭ�Ƚ��沢��ʾ���º����Ϣ
	switch (m_radio)
	{
	case 0:
		OnBnClickedStoreAll();
		break;
	case 1:
		OnBnClickedStoreLack();
		break;
	case 2:
		OnBnClickedStoreNormal();
		break;
	case 3:
		OnBnClickedStoreEx();
		break;
	default:
		break;
	}
	*pResult = 0;
}
