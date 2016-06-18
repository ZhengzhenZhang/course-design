// DlgWrkInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgWrkInfo.h"
#include "afxdialogex.h"
#include "DlgWrkPMoney.h"
#include <math.h>


// CDlgWrkInfo 对话框

IMPLEMENT_DYNAMIC(CDlgWrkInfo, CDialogEx)

CDlgWrkInfo::CDlgWrkInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgWrkInfo::IDD, pParent)
{

	m_timDate = COleDateTime::GetCurrentTime();
	m_strKWORD = _T("");
	m_strName = _T("");
	m_strPhone = _T("");
	m_dbTMoney = 0.0;
	m_nChange = 0;
	m_nTNum = 0;
}

CDlgWrkInfo::~CDlgWrkInfo()
{
}

void CDlgWrkInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATE_WRK, m_timDate);
	DDX_Text(pDX, IDC_EDIT_KWORD, m_strKWORD);
	DDV_MaxChars(pDX, m_strKWORD, 24);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 4);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
	DDV_MaxChars(pDX, m_strPhone, 11);
	DDX_Text(pDX, IDC_EDIT_TMONEY, m_dbTMoney);
	DDV_MinMaxDouble(pDX, m_dbTMoney, 0, 10000000);
	DDX_Control(pDX, IDC_LIST_WRK, m_listInfo);
	DDX_Radio(pDX, IDC_RADIO_ALL, m_nChange);
	DDX_Text(pDX, IDC_EDIT_NUM, m_nTNum);
	DDV_MinMaxInt(pDX, m_nTNum, 0, 10000000);
	DDX_Control(pDX, IDC_LIST_WAGE, m_listWage);
}


BEGIN_MESSAGE_MAP(CDlgWrkInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgWrkInfo::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_RADIO_ALL, &CDlgWrkInfo::OnBnClickedRadioAll)
	ON_BN_CLICKED(IDC_RADIO_DAY, &CDlgWrkInfo::OnBnClickedRadioDay)
	ON_BN_CLICKED(IDC_RADIO_MONTH, &CDlgWrkInfo::OnBnClickedRadioMonth)
	ON_BN_CLICKED(IDC_RADIO_YEAR, &CDlgWrkInfo::OnBnClickedRadioYear)
	ON_BN_CLICKED(IDC_BUTTON_PMONEY, &CDlgWrkInfo::OnBnClickedButtonPmoney)
END_MESSAGE_MAP()


// CDlgWrkInfo 消息处理程序


BOOL CDlgWrkInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_listInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_listInfo.InsertColumn(0, _T("创建时间"), LVCFMT_LEFT, 160);
	m_listInfo.InsertColumn(1, _T("销售信息"), LVCFMT_LEFT, 400);
	m_listInfo.InsertColumn(2, _T("金额"), LVCFMT_LEFT, 100);

	m_listWage.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_listWage.InsertColumn(0, _T("创建时间"), LVCFMT_LEFT, 160);
	m_listWage.InsertColumn(1, _T("工资信息"), LVCFMT_LEFT, 400);
	m_listWage.InsertColumn(2, _T("金额"), LVCFMT_LEFT, 100);

	GetDlgItem(IDC_DATE_WRK)->EnableWindow(FALSE);
	MyListWrkInfo();
	MyListWageInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgWrkInfo::MyRecordsetOpen(CString strSQL)
{
	m_pRecordSet.CreateInstance(__uuidof(Recordset));

	try
	{
		m_pRecordSet->Open(
			_variant_t(strSQL),
			m_pConnection.GetInterfacePtr(),
			adOpenDynamic,
			adLockOptimistic,
			adCmdText
			);
	}
	catch (_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
}


void CDlgWrkInfo::MyConnectionOpen()
{
	m_pConnection.CreateInstance(__uuidof(Connection));

	try
	{
		m_pConnection->Open(_T("Provider=Microsoft.ACE.OLEDB.12.0; Data Source=Sys\\HairCutDataBase.accdb; \
							   Persist Security Info=False; Jet OLEDB:Database Password=HC!123;"), 
							   _T(""), _T(""), adModeUnknown);
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("数据库连接失败，确认数据库“HairCutDataBase.accdb”是否在当前路径！"));
	}
}


void CDlgWrkInfo::MyConnectionExecute(CString strSQL)
{
	try
	{
		m_pConnection->CursorLocation = adUseClient;

		m_pConnection->Execute(_bstr_t(strSQL), NULL, adExecuteNoRecords);
	}
	catch (_com_error *e)
	{
		AfxMessageBox(e->ErrorMessage());
	}
}


void CDlgWrkInfo::MyConnectionClose()
{
	if (m_pConnection->State)
		m_pConnection->Close();
	m_pConnection = NULL;
}


void CDlgWrkInfo::MyListWrkInfo()
{
	m_listInfo.DeleteAllItems();
	MyConnectionOpen();

	_variant_t var;
	CString strTmp;

	CString strSQL;
	CString strSQLSum;
	CString strSQLCounts;
	

	switch (m_nChange)
	{
	case 0:
		strSQL.Format(_T("select * from 销售信息表 \
						 where SellWorkerPhone = '%s' and SellProjectName like '%c%s%c'order by SellDate DESC"), 
						 m_strPhone, _T('%'), m_strKWORD, _T('%'));
		strSQLSum.Format(_T("select sum(SellPrice) from 销售信息表 \
						 where SellWorkerPhone = '%s' and SellProjectName like '%c%s%c'"), 
						 m_strPhone, _T('%'), m_strKWORD, _T('%'));
		strSQLCounts.Format(_T("select count(*) from 销售信息表 \
							where SellWorkerPhone = '%s' and SellProjectName like '%c%s%c'"), 
							m_strPhone, _T('%'), m_strKWORD, _T('%'));
		break;

	case 1:
		strSQL.Format(_T("select * from 销售信息表 \
						 where SellWorkerPhone = '%s' and SellProjectName like '%c%s%c' \
						 and SellDate like '%4d-%c'order by SellDate DESC"), 
						 m_strPhone, _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), _T('%'));
		strSQLSum.Format(_T("select sum(SellPrice) from 销售信息表 \
							where SellWorkerPhone = '%s' and SellProjectName like '%c%s%c' \
							and SellDate like '%4d-%c'"), 
							m_strPhone, _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), _T('%'));
		strSQLCounts.Format(_T("select count(*) from 销售信息表 \
							   where SellWorkerPhone = '%s' and SellProjectName like '%c%s%c' \
							   and SellDate like '%4d-%c'"), 
							   m_strPhone, _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), _T('%'));
		break;

	case 2:
		strSQL.Format(_T("select * from 销售信息表 \
						 where SellWorkerPhone = '%s' and SellProjectName like '%c%s%c' \
						 and SellDate like '%4d-%02d-%c'order by SellDate DESC"), 
						 m_strPhone, _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), 
						 m_timDate.GetMonth(), _T('%'));
		strSQLSum.Format(_T("select sum(SellPrice) from 销售信息表 \
							where SellWorkerPhone = '%s' and SellProjectName like '%c%s%c' \
							and SellDate like '%4d-%02d-%c'"), 
							m_strPhone, _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), 
							m_timDate.GetMonth(), _T('%'));
		strSQLCounts.Format(_T("select count(*) from 销售信息表 \
							   where SellWorkerPhone = '%s' and SellProjectName like '%c%s%c' \
							   and SellDate like '%4d-%02d-%c'"), 
							   m_strPhone, _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), 
							   m_timDate.GetMonth(), _T('%'));
		break;

	case 3:
		strSQL.Format(_T("select * from 销售信息表 \
						 where SellWorkerPhone = '%s' and SellProjectName like '%c%s%c' \
						 and SellDate like '%4d-%02d-%02d%c'order by SellDate DESC"), 
						 m_strPhone, _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), 
						 m_timDate.GetMonth(), m_timDate.GetDay(), _T('%'));
		strSQLSum.Format(_T("select sum(SellPrice) from 销售信息表 \
							where SellWorkerPhone = '%s' and SellProjectName like '%c%s%c' \
							and SellDate like '%4d-%02d-%02d%c'"), 
							m_strPhone, _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), 
							m_timDate.GetMonth(), m_timDate.GetDay(), _T('%'));
		strSQLCounts.Format(_T("select count(*) from 销售信息表 \
							   where SellWorkerPhone = '%s' and SellProjectName like '%c%s%c' \
							   and SellDate like '%4d-%02d-%02d%c'"), 
							   m_strPhone, _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), 
							   m_timDate.GetMonth(), m_timDate.GetDay(), _T('%'));
		break;
	}

	MyRecordsetOpen(strSQL);

	m_dbTMoney = 0;
	m_nTNum = 0;
	for (int i = 0; !m_pRecordSet->adoEOF && i < 100; i++)
	{
		var = m_pRecordSet->GetCollect(_T("SellDate"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listInfo.InsertItem(i, strTmp);

		var = m_pRecordSet->GetCollect(_T("SellProjectName"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listInfo.SetItemText(i, 1, strTmp);

		var = m_pRecordSet->GetCollect(_T("SellPrice"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listInfo.SetItemText(i, 2, strTmp);

		m_pRecordSet->MoveNext();
	}

	MyRecordsetOpen(strSQLSum);
	var = m_pRecordSet->GetCollect(_variant_t((long)0));

	
	strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
	m_dbTMoney = fabs(_ttof(strTmp));

	MyRecordsetOpen(strSQLCounts);
	var = m_pRecordSet->GetCollect(_variant_t((long)0));

	strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
	m_nTNum = _ttoi(strTmp);
	
	m_pRecordSet->Close();
	m_pRecordSet.Release();
	MyConnectionClose();

	UpdateData(FALSE);
}


void CDlgWrkInfo::MyListWageInfo()
{
	m_listWage.DeleteAllItems();
	MyConnectionOpen();

	_variant_t var;
	CString strTmp;

	CString strSQL;

	switch (m_nChange)
	{
	case 0:
		strSQL.Format(_T("select * from 支出信息表 \
						 where PayWrkPhone = '%s' and PayInfo = '%s'order by PayDate DESC"), 
						 m_strPhone, _T("发放工资"));
		break;

	case 1:
		strSQL.Format(_T("select * from 支出信息表 \
						 where PayWrkPhone = '%s' and PayInfo = '%s' \
						 and PayDate like '%4d-%c'order by PayDate DESC"), 
						 m_strPhone, _T("发放工资"), m_timDate.GetYear(), _T('%'));
		break;

	case 2:
		strSQL.Format(_T("select * from 支出信息表 \
						 where PayWrkPhone = '%s' and PayInfo = '%s' \
						 and PayDate like '%4d-%02d-%c'order by PayDate DESC"), 
						 m_strPhone, _T("发放工资"), m_timDate.GetYear(), 
						 m_timDate.GetMonth(), _T('%'));
		break;

	case 3:
		strSQL.Format(_T("select * from 支出信息表 \
						 where PayWrkPhone = '%s' and PayInfo = '%s' \
						 and PayDate like '%4d-%02d-%c'order by PayDate DESC"), 
						 m_strPhone, _T("发放工资"), m_timDate.GetYear(), 
						 m_timDate.GetMonth(), _T('%'));
		break;
	}

	MyRecordsetOpen(strSQL);


	for (int i = 0; !m_pRecordSet->adoEOF && i < 100; i++)
	{
		var = m_pRecordSet->GetCollect(_T("PayDate"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listWage.InsertItem(i, strTmp);

		var = m_pRecordSet->GetCollect(_T("PayInfo"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listWage.SetItemText(i, 1, strTmp);

		var = m_pRecordSet->GetCollect(_T("PayMoney"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listWage.SetItemText(i, 2, strTmp);

		m_pRecordSet->MoveNext();
	}

	m_pRecordSet->Close();
	m_pRecordSet.Release();
	MyConnectionClose();

	UpdateData(FALSE);
}


void CDlgWrkInfo::OnBnClickedButtonSearch()
{
	UpdateData(TRUE);
	MyListWrkInfo();
	MyListWageInfo();
}


void CDlgWrkInfo::OnBnClickedRadioAll()
{
	GetDlgItem(IDC_DATE_WRK)->EnableWindow(FALSE);
}


void CDlgWrkInfo::OnBnClickedRadioDay()
{
	GetDlgItem(IDC_DATE_WRK)->EnableWindow(TRUE);
}


void CDlgWrkInfo::OnBnClickedRadioMonth()
{
	GetDlgItem(IDC_DATE_WRK)->EnableWindow(TRUE);
}


void CDlgWrkInfo::OnBnClickedRadioYear()
{
	GetDlgItem(IDC_DATE_WRK)->EnableWindow(TRUE);
}


void CDlgWrkInfo::OnBnClickedButtonPmoney()
{
	CDlgWrkPMoney dlg;
	dlg.m_strName = m_strName;
	dlg.m_strPhone = m_strPhone;

	if (IDCANCEL == dlg.DoModal())
		return;

	// 添加信息
	CTime tim;
	tim = CTime::GetCurrentTime();

	CString strTim;
	strTim.Format(_T("%4d-%02d-%02d %02d:%02d:%02d"), tim.GetYear(), tim.GetMonth(), 
		tim.GetDay(), tim.GetHour(), tim.GetMinute(), tim.GetSecond());

	MyConnectionOpen();

	CString strSQL;
	strSQL.Format(_T("insert into 支出信息表(PayDate, PayMoney, PayInfo, PayWrkName, PayWrkPhone) \
					 values('%s', %.2lf, '%s', '%s', '%s')"),
					 strTim, dlg.m_dbPMoney, _T("发放工资"), m_strName, m_strPhone);
	MyConnectionExecute(strSQL);

	MyConnectionClose();

	MyListWageInfo();
}
