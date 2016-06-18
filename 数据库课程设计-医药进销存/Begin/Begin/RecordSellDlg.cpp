// RecordSellDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Begin.h"
#include "RecordSellDlg.h"


// CRecordSellDlg 对话框

IMPLEMENT_DYNAMIC(CRecordSellDlg, CDialog)

CRecordSellDlg::CRecordSellDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecordSellDlg::IDD, pParent)
	, m_radio(0)
	, m_sumMny(0)
	, m_ftime(COleDateTime::GetCurrentTime())
	, m_totime(COleDateTime::GetCurrentTime())
	, m_edit(_T("输入批准文号"))
	, m_sumNum(0)
{
	
}

CRecordSellDlg::~CRecordSellDlg()
{
}

void CRecordSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDL_RECORD_SELL, m_list);
	DDX_Radio(pDX, IDR_SELL_ALL, m_radio);
	DDX_Text(pDX, IDE_SELL_SUMMNY, m_sumMny);
	DDX_DateTimeCtrl(pDX, IDT_TIME_FROM, m_ftime);
	DDX_DateTimeCtrl(pDX, IDT_TIME_TO, m_totime);
	DDX_Text(pDX, IDE_SELL, m_edit);
	DDX_Text(pDX, IDE_SELL_SUMNUM, m_sumNum);
	DDX_Control(pDX, IDE_SELL, m_CSell);
}


BEGIN_MESSAGE_MAP(CRecordSellDlg, CDialog)
	ON_BN_CLICKED(IDR_SELL_ALL, &CRecordSellDlg::OnBnClickedSellAll)
	ON_BN_CLICKED(IDR_SELL_LMON, &CRecordSellDlg::OnBnClickedSellLmon)
	ON_BN_CLICKED(IDR_SELL_LWEEK, &CRecordSellDlg::OnBnClickedSellLweek)
	ON_BN_CLICKED(IDR_SELL_LYEST, &CRecordSellDlg::OnBnClickedSellLyest)
	ON_BN_CLICKED(IDB_SELL_SEARCH, &CRecordSellDlg::OnBnClickedSellSearch)
	ON_BN_CLICKED(IDC_RADIO1, &CRecordSellDlg::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CRecordSellDlg 消息处理程序

BOOL CRecordSellDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list.InsertColumn(0, _T("销售时间"), LVCFMT_CENTER, 105);
	m_list.InsertColumn(1, _T("批准文号"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(2, _T("药品名称"), LVCFMT_CENTER, 110);
	m_list.InsertColumn(3, _T("药品规格"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(4, _T("销售数量"), LVCFMT_CENTER, 65);
	m_list.InsertColumn(5, _T("销售金额"), LVCFMT_CENTER, 65);
	m_list.InsertColumn(6, _T("销售员ID"), LVCFMT_CENTER, 65);
	//m_list.SetBkColor(RGB(26, 231, 151));
	//m_list.SetTextBkColor(RGB(26, 231, 151));
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES);

	OnBnClickedSellAll();
	
	GetDlgItem(IDE_SELL)->SetFocus();
	SendDlgItemMessage(IDE_SELL, EM_SETSEL, 0, -1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CRecordSellDlg::ListTheInfo()
{
	// 采用时间降序排列，更贴心
	set.m_strSort.Format(_T("sellTime desc"));
	if (!set.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
	m_list.DeleteAllItems();
	if(set.IsEOF())
	{
		m_sumMny = 0;
		m_sumNum = 0;
		//MessageBox(_T("无销售记录"));
	}
	else
	{
		m_sumMny = 0;
		m_sumNum = 0;
		for(int i=0; !set.IsEOF(); i++,set.MoveNext())
		{
			CString cs;
			cs.Format(_T("%d-%d-%d %d:%d:%d"),
				set.m_sellTime.GetYear(), set.m_sellTime.GetMonth(), set.m_sellTime.GetDay(),
				set.m_sellTime.GetHour(), set.m_sellTime.GetMinute(), set.m_sellTime.GetSecond());
			m_list.InsertItem(i, cs);

			set.m_code.TrimRight();
			m_list.SetItemText(i, 1, set.m_code);

			set.m_name.TrimRight();
			m_list.SetItemText(i, 2, set.m_name);

			set.m_specification.TrimRight();
			m_list.SetItemText(i, 3, set.m_specification);
		
			cs.Format(_T("%d"), set.m_sellNum);
			cs.TrimRight();
			m_list.SetItemText(i, 4, cs);

			cs.Format(_T("%.2f"), set.m_sellSumMny);
			cs.TrimRight();
			m_list.SetItemText(i, 5, cs);

			set.m_ID.TrimRight();
			m_list.SetItemText(i, 6, set.m_ID);

			m_sumMny += set.m_sellSumMny;
			m_sumNum ++;
		}	
	}
	UpdateData(FALSE);
	set.Close();
}

void CRecordSellDlg::OnBnClickedSellAll()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_radio = 0;
	set.m_strFilter.Format(_T(""));
	ListTheInfo();
}

void CRecordSellDlg::OnBnClickedSellLmon()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_radio = 1;
	
	CTime ct = CTime::GetCurrentTime();
	// 调时间         日  小时 分钟 秒
	//ct -= CTimeSpan(ct.GetDay(), 0, 0, 0);
	int m_ny = ct.GetYear();
	int m_nm = ct.GetMonth();
	int m_nd = 1;
	
	int m_fy, m_fm, m_fd;
	m_fy = m_ny;
	m_fm = m_nm;
	m_fd = 1;
	if (m_fm == 1)
	{
		m_fm = 12;
		m_fy--;
	}
	else
	{
		m_fm--;
	}


	CString ft, nt, cs;
	ft.Format(_T("'%d-%d-%d'"), m_fy, m_fm, m_fd);
	nt.Format(_T("'%d-%d-%d'"), m_ny, m_nm, m_nd);
	
	cs = _T("sellTime between ");
	cs += ft;
	cs += _T(" and ");
	cs += nt;
	
	//MessageBox(cs);

	set.m_strFilter = cs;
	ListTheInfo();
}

void CRecordSellDlg::OnBnClickedSellLweek()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_radio = 2;

	CTime ct = CTime::GetCurrentTime();
	// 调时间         日  小时 分钟 秒
	ct -= CTimeSpan(ct.GetDayOfWeek()-1, 0, 0, 0);
	int m_ny = ct.GetYear();
	int m_nm = ct.GetMonth();
	int m_nd = ct.GetDay();
	ct -= CTimeSpan(7, 0, 0, 0);
	int m_fy = ct.GetYear();
	int m_fm = ct.GetMonth();
	int m_fd = ct.GetDay();

	CString ft, nt, cs;
	ft.Format(_T("'%d-%d-%d'"), m_fy, m_fm, m_fd);
	nt.Format(_T("'%d-%d-%d'"), m_ny, m_nm, m_nd);

	cs = _T("sellTime between ");
	cs += ft;
	cs += _T(" and ");
	cs += nt;
	//MessageBox(cs);
	set.m_strFilter = cs;
	ListTheInfo();

}

void CRecordSellDlg::OnBnClickedSellLyest()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	m_radio = 3;

	CTime ct = CTime::GetCurrentTime();
	// 调时间         日  小时 分钟 秒
	//ct -= CTimeSpan(ct.GetDayOfWeek()-1, 0, 0, 0);
	int m_ny = ct.GetYear();
	int m_nm = ct.GetMonth();
	int m_nd = ct.GetDay();
	ct -= CTimeSpan(1, 0, 0, 0);
	int m_fy = ct.GetYear();
	int m_fm = ct.GetMonth();
	int m_fd = ct.GetDay();

	CString ft, nt, cs;
	ft.Format(_T("'%d-%d-%d'"), m_fy, m_fm, m_fd);
	nt.Format(_T("'%d-%d-%d'"), m_ny, m_nm, m_nd);

	cs = _T("sellTime between ");
	cs += ft;
	cs += _T(" and ");
	cs += nt;
	//MessageBox(cs);
	set.m_strFilter = cs;
	ListTheInfo();
}

void CRecordSellDlg::OnBnClickedSellSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int m_ny = m_totime.GetYear();
	int m_nm = m_totime.GetMonth();
	int m_nd = m_totime.GetDay()+1;
	
	int m_fy = m_ftime.GetYear();
	int m_fm = m_ftime.GetMonth();
	int m_fd = m_ftime.GetDay();
	CString ft, nt, cs;
	ft.Format(_T("'%d-%d-%d'"), m_fy, m_fm, m_fd);
	nt.Format(_T("'%d-%d-%d'"), m_ny, m_nm, m_nd);

	cs = _T("sellTime between ");
	cs += ft;
	cs += _T(" and ");
	cs += nt;
	cs += _T(" and code like '%");
	cs += m_edit;
	cs += _T("%'");

	set.m_strFilter = cs;
	ListTheInfo();

	GetDlgItem(IDE_SELL)->SetFocus();
	SendDlgItemMessage(IDE_SELL, EM_SETSEL, 0, -1);
}	

BOOL CRecordSellDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message==WM_LBUTTONDOWN)
	{
		if(pMsg->hwnd == m_CSell.m_hWnd)
		{
			GetDlgItem(IDE_SELL)->PostMessage(EM_SETSEL, 0, -1);
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CRecordSellDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
}
