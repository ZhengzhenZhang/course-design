// StoreInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Begin.h"
#include "StoreInfoDlg.h"
#include "UpdateDlg.h"


// CStoreInfoDlg 对话框

IMPLEMENT_DYNAMIC(CStoreInfoDlg, CDialog)

CStoreInfoDlg::CStoreInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStoreInfoDlg::IDD, pParent)
	, m_code(_T("批准文号"))
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


// CStoreInfoDlg 消息处理程序

BOOL CStoreInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list.InsertColumn(0, _T("批准文号"), LVCFMT_CENTER, 83);
	m_list.InsertColumn(1, _T("药品名称"), LVCFMT_CENTER, 83);
	m_list.InsertColumn(2, _T("药品规格"), LVCFMT_CENTER, 143);
	m_list.InsertColumn(3, _T("药品库存"), LVCFMT_CENTER, 83);
	m_list.InsertColumn(4, _T("药品报价"), LVCFMT_CENTER, 83);
	//m_list.SetBkColor(RGB(26, 231, 151));
	//m_list.SetTextBkColor(RGB(26, 231, 151));
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES);

	OnBnClickedStoreAll();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CStoreInfoDlg::ListTheInfo()
{
	if (!set.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
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
	// TODO: 在此添加控件通知处理程序代码
	m_radio = 0;
	set.m_strFilter.Format(_T(""));
	ListTheInfo();
}

void CStoreInfoDlg::OnBnClickedStoreLack()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio = 1;
	set.m_strFilter.Format(_T("counts < 20"));
	set.m_strSort.Format(_T("counts asc")); // 最少的排在上面
	ListTheInfo();
	set.m_strSort.Format(_T("code asc"));
}

void CStoreInfoDlg::OnBnClickedStoreNormal()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio = 2;
	set.m_strFilter.Format(_T("counts >= 20 and counts < 100"));
	ListTheInfo();
}

void CStoreInfoDlg::OnBnClickedStoreEx()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radio = 3;
	set.m_strFilter.Format(_T("counts >= 100"));
	set.m_strSort.Format(_T("counts desc"));	// 最冗余的排在上面
	ListTheInfo();
	set.m_strSort.Format(_T("code asc"));
}


void CStoreInfoDlg::OnBnClickedStoreSearch()
{
	// TODO: 在此添加控件通知处理程序代码

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
	// TODO: 在此添加控件通知处理程序代码

	// 从库存信息中直接更新已有药品信息
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
		MessageBox(_T("无库存信息或单击选中药品批准文号"), 
			_T("提示"), MB_OK);
	}
	
	
	// 更新药品后还保持原先界面并显示更新后的信息
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
