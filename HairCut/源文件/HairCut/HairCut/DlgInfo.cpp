// DlgInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgInfo.h"
#include "afxdialogex.h"
#include <math.h>


// CDlgInfo 对话框

IMPLEMENT_DYNAMIC(CDlgInfo, CDialogEx)

CDlgInfo::CDlgInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgInfo::IDD, pParent)
{

	m_timDate = COleDateTime::GetCurrentTime();
	m_strKWORD = _T("");
	m_dbGMoney = 0.0;
	m_dbPMoney = 0.0;
	m_dbSMoney = 0.0;
	m_dbVMoney = 0.0;
	m_nChange = 0;
}

CDlgInfo::~CDlgInfo()
{
}

void CDlgInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATE_INFO, m_timDate);
	DDX_Text(pDX, IDC_EDIT_KWORD, m_strKWORD);
	DDV_MaxChars(pDX, m_strKWORD, 24);
	DDX_Text(pDX, IDC_EDIT_GTMONEY, m_dbGMoney);
	DDX_Text(pDX, IDC_EDIT_PTMONEY, m_dbPMoney);
	DDX_Text(pDX, IDC_EDIT_STMONEY, m_dbSMoney);
	DDX_Text(pDX, IDC_EDIT_VTMONEY, m_dbVMoney);
	DDX_Control(pDX, IDC_LIST_PINFO, m_listPInfo);
	DDX_Control(pDX, IDC_LIST_SINFO, m_listSInfo);
	DDX_Radio(pDX, IDC_RADIO_ALL, m_nChange);
}


BEGIN_MESSAGE_MAP(CDlgInfo, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_ALL, &CDlgInfo::OnBnClickedRadioAll)
	ON_BN_CLICKED(IDC_RADIO_DAY, &CDlgInfo::OnBnClickedRadioDay)
	ON_BN_CLICKED(IDC_RADIO_MONTH, &CDlgInfo::OnBnClickedRadioMonth)
	ON_BN_CLICKED(IDC_RADIO_YEAR, &CDlgInfo::OnBnClickedRadioYear)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgInfo::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CDlgInfo::OnBnClickedButtonExport)
END_MESSAGE_MAP()


// CDlgInfo 消息处理程序

void CDlgInfo::MyRecordsetOpen(CString strSQL)
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


void CDlgInfo::MyConnectionOpen()
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


void CDlgInfo::MyConnectionExecute(CString strSQL)
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


void CDlgInfo::MyConnectionClose()
{
	if (m_pConnection->State)
		m_pConnection->Close();
	m_pConnection = NULL;
}


BOOL CDlgInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_listSInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_listSInfo.InsertColumn(0, _T("创建时间"), LVCFMT_LEFT, 160);
	m_listSInfo.InsertColumn(1, _T("销售信息"), LVCFMT_LEFT, 400);
	m_listSInfo.InsertColumn(2, _T("金额"), LVCFMT_LEFT, 100);

	m_listPInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_listPInfo.InsertColumn(0, _T("创建时间"), LVCFMT_LEFT, 160);
	m_listPInfo.InsertColumn(1, _T("支出信息"), LVCFMT_LEFT, 400);
	m_listPInfo.InsertColumn(2, _T("金额"), LVCFMT_LEFT, 100);

	GetDlgItem(IDC_DATE_INFO)->EnableWindow(FALSE);
	MyListSellInfo();
	MyListPayInfo();

	m_dbGMoney = m_dbSMoney - m_dbPMoney;

	MyConnectionOpen();
	_variant_t var;
	CString strSQLSum;
	CString strTmp;
	strSQLSum.Format(_T("select sum(VipBalance) from 会员信息表"));

	MyRecordsetOpen(strSQLSum);
	var = m_pRecordSet->GetCollect(_variant_t((long)0));

	strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
	m_dbVMoney = fabs(_ttof(strTmp));

	m_pRecordSet->Close();
	m_pRecordSet.Release();
	MyConnectionClose();

	UpdateData(FALSE);

	return TRUE;
}


void CDlgInfo::MyListSellInfo()
{
	m_listSInfo.DeleteAllItems();
	MyConnectionOpen();

	_variant_t var;
	CString strTmp;

	CString strSQL;
	CString strSQLSum;
	
	switch (m_nChange)
	{
	case 0:
		strSQL.Format(_T("select * from 销售信息表 \
						 where SellProjectCode like '%c%s%c' or SellProjectName like '%c%s%c'order by SellDate DESC"), 
						 _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'));
		strSQLSum.Format(_T("select sum(SellPrice) from 销售信息表 \
							where SellProjectCode like '%c%s%c' or SellProjectName like '%c%s%c'"), 
							_T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'));
		break;

	case 1:
		strSQL.Format(_T("select * from 销售信息表 \
						 where (SellProjectCode like '%c%s%c' or SellProjectName like '%c%s%c') \
						 and SellDate like '%4d-%c'order by SellDate DESC"), 
						 _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), _T('%'));
		strSQLSum.Format(_T("select sum(SellPrice) from 销售信息表 \
							where (SellProjectCode like '%c%s%c' or SellProjectName like '%c%s%c') \
							and SellDate like '%4d-%c'"), 
							_T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), _T('%'));
		break;

	case 2:
		strSQL.Format(_T("select * from 销售信息表 \
						 where (SellProjectCode like '%c%s%c' or SellProjectName like '%c%s%c') \
						 and SellDate like '%4d-%02d-%c'order by SellDate DESC"), 
						 _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), 
						 m_timDate.GetMonth(), _T('%'));
		strSQLSum.Format(_T("select sum(SellPrice) from 销售信息表 \
							where (SellProjectCode like '%c%s%c' or SellProjectName like '%c%s%c') \
							and SellDate like '%4d-%02d-%c'"), 
							_T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), 
							m_timDate.GetMonth(), _T('%'));
		break;

	case 3:
		strSQL.Format(_T("select * from 销售信息表 \
						 where (SellProjectCode like '%c%s%c' or SellProjectName like '%c%s%c') \
						 and SellDate like '%4d-%02d-%02d%c'order by SellDate DESC"), 
						 _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), 
						 m_timDate.GetMonth(), m_timDate.GetDay(), _T('%'));
		strSQLSum.Format(_T("select sum(SellPrice) from 销售信息表 \
							where (SellProjectCode like '%c%s%c' or SellProjectName like '%c%s%c') \
							and SellDate like '%4d-%02d-%02d%c'"), 
							_T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), 
							m_timDate.GetMonth(), m_timDate.GetDay(), _T('%'));
		break;
	}

	MyRecordsetOpen(strSQL);

	m_dbSMoney = 0;
	
	for (int i = 0; !m_pRecordSet->adoEOF && i < 100; i++)
	{
		var = m_pRecordSet->GetCollect(_T("SellDate"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listSInfo.InsertItem(i, strTmp);

		var = m_pRecordSet->GetCollect(_T("SellProjectName"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listSInfo.SetItemText(i, 1, strTmp);

		var = m_pRecordSet->GetCollect(_T("SellPrice"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listSInfo.SetItemText(i, 2, strTmp);

		m_pRecordSet->MoveNext();
	}

	MyRecordsetOpen(strSQLSum);
	var = m_pRecordSet->GetCollect(_variant_t((long)0));


	strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
	m_dbSMoney = fabs(_ttof(strTmp));

	m_pRecordSet->Close();
	m_pRecordSet.Release();
	MyConnectionClose();

	UpdateData(FALSE);
}


void CDlgInfo::MyListPayInfo()
{
	m_listPInfo.DeleteAllItems();
	MyConnectionOpen();

	_variant_t var;
	CString strTmp;

	CString strSQL;
	CString strSQLSum;

	switch (m_nChange)
	{
	case 0:
		strSQL.Format(_T("select * from 支出信息表 order by PayDate DESC"));
		strSQLSum.Format(_T("select sum(PayMoney) from 支出信息表"));
		break;

	case 1:
		strSQL.Format(_T("select * from 支出信息表 where PayDate like '%4d-%c'order by PayDate DESC"), 
						 m_timDate.GetYear(), _T('%'));
		strSQLSum.Format(_T("select sum(PayMoney) from 支出信息表	where PayDate like '%4d-%c'"), 
							m_timDate.GetYear(), _T('%'));
		break;

	case 2:
		strSQL.Format(_T("select * from 支出信息表 where PayDate like '%4d-%02d-%c'order by PayDate DESC"), 
						 m_timDate.GetYear(), m_timDate.GetMonth(), _T('%'));
		strSQLSum.Format(_T("select sum(PayMoney) from 支出信息表 where PayDate like '%4d-%02d-%c'"), 
							m_timDate.GetYear(), m_timDate.GetMonth(), _T('%'));
		break;

	case 3:
		strSQL.Format(_T("select * from 支出信息表 where PayDate like '%4d-%02d-%02d%c'order by PayDate DESC"), 
						 m_timDate.GetYear(), m_timDate.GetMonth(), m_timDate.GetDay(), _T('%'));
		strSQLSum.Format(_T("select sum(PayMoney) from 支出信息表 where PayDate like '%4d-%02d-%02d%c'"), 
							m_timDate.GetYear(), m_timDate.GetMonth(), m_timDate.GetDay(), _T('%'));
		break;
	}

	MyRecordsetOpen(strSQL);
	
	for (int i = 0; !m_pRecordSet->adoEOF && i < 100; i++)
	{
		var = m_pRecordSet->GetCollect(_T("PayDate"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listPInfo.InsertItem(i, strTmp);

		var = m_pRecordSet->GetCollect(_T("PayInfo"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listPInfo.SetItemText(i, 1, strTmp);

		var = m_pRecordSet->GetCollect(_T("PayMoney"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listPInfo.SetItemText(i, 2, strTmp);

		m_pRecordSet->MoveNext();
	}

	MyRecordsetOpen(strSQLSum);
	var = m_pRecordSet->GetCollect(_variant_t((long)0));
	
	strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
	m_dbPMoney = fabs(_ttof(strTmp));

	m_pRecordSet->Close();
	m_pRecordSet.Release();
	MyConnectionClose();

	UpdateData(FALSE);
}


void CDlgInfo::OnBnClickedRadioAll()
{
	GetDlgItem(IDC_DATE_INFO)->EnableWindow(FALSE);
}


void CDlgInfo::OnBnClickedRadioDay()
{
	GetDlgItem(IDC_DATE_INFO)->EnableWindow(TRUE);
}


void CDlgInfo::OnBnClickedRadioMonth()
{
	GetDlgItem(IDC_DATE_INFO)->EnableWindow(TRUE);
}


void CDlgInfo::OnBnClickedRadioYear()
{
	GetDlgItem(IDC_DATE_INFO)->EnableWindow(TRUE);
}


void CDlgInfo::OnBnClickedButtonSearch()
{
	UpdateData(TRUE);
	MyListSellInfo();
	MyListPayInfo();

	m_dbGMoney = m_dbSMoney - m_dbPMoney;

	UpdateData(FALSE);
}


void CDlgInfo::OnBnClickedButtonExport()
{
	MessageBox(_T("该功能暂未实现！"), _T("提示"));
}