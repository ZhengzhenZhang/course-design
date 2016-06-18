// DlgProjInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgProjInfo.h"
#include "afxdialogex.h"
#include <math.h>
#include "DlgProject.h"


// CDlgProjInfo 对话框

IMPLEMENT_DYNAMIC(CDlgProjInfo, CDialogEx)

CDlgProjInfo::CDlgProjInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgProjInfo::IDD, pParent)
{

	m_timDate = COleDateTime::GetCurrentTime();
	m_strKWORD = _T("");
	m_strName = _T("");
	m_strDate = _T("");
	m_strCode = _T("");
	m_nTNum = 0;
	m_dbTMoney = 0.0;
	m_nChange = 0;
	m_dbPrice = 0;
	m_dbVipPrice = 0;
	m_dbPrice = 0.0;
	m_dbVipPrice = 0.0;
}

CDlgProjInfo::~CDlgProjInfo()
{
}

void CDlgProjInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATE_PROJ, m_timDate);
	DDX_Text(pDX, IDC_EDIT_KWORD, m_strKWORD);
	DDV_MaxChars(pDX, m_strKWORD, 24);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 4);
	DDX_Text(pDX, IDC_EDIT_NUM, m_nTNum);
	DDV_MinMaxInt(pDX, m_nTNum, 0, 100000000);
	DDX_Text(pDX, IDC_EDIT_TMONEY, m_dbTMoney);
	DDV_MinMaxDouble(pDX, m_dbTMoney, 0, 100000000);
	DDX_Control(pDX, IDC_LIST_WRK, m_listInfo);
	DDX_Radio(pDX, IDC_RADIO_ALL, m_nChange);
	DDV_MinMaxInt(pDX, m_nChange, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_dbPrice);
	DDV_MinMaxDouble(pDX, m_dbPrice, 0, 10000000);
	DDX_Text(pDX, IDC_EDIT_VIPPRICE, m_dbVipPrice);
	DDV_MinMaxDouble(pDX, m_dbVipPrice, 0, 1000000);
}


BEGIN_MESSAGE_MAP(CDlgProjInfo, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_ALL, &CDlgProjInfo::OnBnClickedRadioAll)
	ON_BN_CLICKED(IDC_RADIO_DAY, &CDlgProjInfo::OnBnClickedRadioDay)
	ON_BN_CLICKED(IDC_RADIO_MONTH, &CDlgProjInfo::OnBnClickedRadioMonth)
	ON_BN_CLICKED(IDC_RADIO_YEAR, &CDlgProjInfo::OnBnClickedRadioYear)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CDlgProjInfo::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgProjInfo::OnBnClickedButtonSearch)
END_MESSAGE_MAP()


// CDlgProjInfo 消息处理程序

BOOL CDlgProjInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_listInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_listInfo.InsertColumn(0, _T("销售时间"), LVCFMT_LEFT, 160);
	m_listInfo.InsertColumn(1, _T("员工名"), LVCFMT_LEFT, 100);
	m_listInfo.InsertColumn(2, _T("是否会员"), LVCFMT_LEFT, 100);
	m_listInfo.InsertColumn(3, _T("会员名"), LVCFMT_LEFT, 100);
	m_listInfo.InsertColumn(4, _T("联系方式"), LVCFMT_LEFT, 120);
	m_listInfo.InsertColumn(5, _T("金额"), LVCFMT_LEFT, 100);


	GetDlgItem(IDC_DATE_PROJ)->EnableWindow(FALSE);
	MyListProjInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgProjInfo::MyListProjInfo()
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
						 where SellProjectDate = '%s' and (SellWorkerName like '%c%s%c' \
						 or SellVipName like '%c%s%c') order by SellDate DESC"), 
						 m_strDate, _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'));
		strSQLSum.Format(_T("select sum(SellPrice) from 销售信息表 \
							where SellProjectDate = '%s' and (SellWorkerName like '%c%s%c' \
							or SellVipName like '%c%s%c')"), 
							m_strDate, _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'));
		strSQLCounts.Format(_T("select count(*) from 销售信息表 \
							   where SellProjectDate = '%s' and (SellWorkerName like '%c%s%c' \
							   or SellVipName like '%c%s%c')"), 
							   m_strDate, _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'));
		break;

	case 1:
		strSQL.Format(_T("select * from 销售信息表 \
						 where SellProjectDate = '%s' and (SellWorkerName like '%c%s%c' \
						 or SellVipName like '%c%s%c') \
						 and SellDate like '%4d-%c'order by SellDate DESC"), 
						 m_strDate, _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'), 
						 m_timDate.GetYear(), _T('%'));
		strSQLSum.Format(_T("select sum(SellPrice) from 销售信息表 \
							where SellProjectDate = '%s' and (SellWorkerName like '%c%s%c' \
							or SellVipName like '%c%s%c') \
							and SellDate like '%4d-%c'"), 
							m_strDate, _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'), 
							m_timDate.GetYear(), _T('%'));
		strSQLCounts.Format(_T("select count(*) from 销售信息表 \
							   where SellProjectDate = '%s' and (SellWorkerName like '%c%s%c' \
							   or SellVipName like '%c%s%c') \
							   and SellDate like '%4d-%c'"), 
							   m_strDate, _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'), 
							   m_timDate.GetYear(), _T('%'));
		break;

	case 2:
		strSQL.Format(_T("select * from 销售信息表 \
						 where SellProjectDate = '%s' and (SellWorkerName like '%c%s%c' \
						 or SellVipName like '%c%s%c') \
						 and SellDate like '%4d-%02d-%c'order by SellDate DESC"), 
						 m_strDate, _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'), 
						 m_timDate.GetYear(),  m_timDate.GetMonth(), _T('%'));
		strSQLSum.Format(_T("select sum(SellPrice) from 销售信息表 \
							where SellProjectDate = '%s' and (SellWorkerName like '%c%s%c' \
							or SellVipName like '%c%s%c') \
							and SellDate like '%4d-%02d-%c'"), 
							m_strDate, _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'), 
							m_timDate.GetYear(), m_timDate.GetMonth(), _T('%'));
		strSQLCounts.Format(_T("select count(*) from 销售信息表 \
							   where SellProjectDate = '%s' and (SellWorkerName like '%c%s%c' \
							   or SellVipName like '%c%s%c') \
							   and SellDate like '%4d-%02d-%c'"), 
							   m_strDate, _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'), 
							   m_timDate.GetYear(), m_timDate.GetMonth(), _T('%'));
		break;

	case 3:
		strSQL.Format(_T("select * from 销售信息表 \
						 where SellProjectDate = '%s' and (SellWorkerName like '%c%s%c' \
						 or SellVipName like '%c%s%c') \
						 and SellDate like '%4d-%02d-%02d%c'order by SellDate DESC"), 
						 m_strDate, _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'), 
						 m_timDate.GetYear(), m_timDate.GetMonth(), m_timDate.GetDay(), _T('%'));
		strSQLSum.Format(_T("select sum(SellPrice) from 销售信息表 \
							where SellProjectDate = '%s' and (SellWorkerName like '%c%s%c' \
							or SellVipName like '%c%s%c') \
							and SellDate like '%4d-%02d-%02d%c'"), 
							m_strDate, _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'), 
							m_timDate.GetYear(), m_timDate.GetMonth(), m_timDate.GetDay(), _T('%'));
		strSQLCounts.Format(_T("select count(*) from 销售信息表 \
							   where SellProjectDate = '%s' and (SellWorkerName like '%c%s%c' \
							   or SellVipName like '%c%s%c') \
							   and SellDate like '%4d-%02d-%02d%c'"), 
							   m_strDate, _T('%'), m_strKWORD, _T('%'), _T('%'), m_strKWORD, _T('%'), 
							   m_timDate.GetYear(), m_timDate.GetMonth(), m_timDate.GetDay(), _T('%'));
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

		var = m_pRecordSet->GetCollect(_T("SellWorkerName"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listInfo.SetItemText(i, 1, strTmp);

		var = m_pRecordSet->GetCollect(_T("SellIsVIP"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listInfo.SetItemText(i, 2, strTmp);

		var = m_pRecordSet->GetCollect(_T("SellVipName"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listInfo.SetItemText(i, 3, strTmp);

		var = m_pRecordSet->GetCollect(_T("SellVipPhone"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listInfo.SetItemText(i, 4, strTmp);

		var = m_pRecordSet->GetCollect(_T("SellPrice"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listInfo.SetItemText(i, 5, strTmp);

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


void CDlgProjInfo::MyRecordsetOpen(CString strSQL)
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


void CDlgProjInfo::MyConnectionOpen()
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


void CDlgProjInfo::MyConnectionExecute(CString strSQL)
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


void CDlgProjInfo::MyConnectionClose()
{
	if (m_pConnection->State)
		m_pConnection->Close();
	m_pConnection = NULL;
}


void CDlgProjInfo::OnBnClickedRadioAll()
{
	GetDlgItem(IDC_DATE_PROJ)->EnableWindow(FALSE);
}


void CDlgProjInfo::OnBnClickedRadioDay()
{
	GetDlgItem(IDC_DATE_PROJ)->EnableWindow(TRUE);
}


void CDlgProjInfo::OnBnClickedRadioMonth()
{
	GetDlgItem(IDC_DATE_PROJ)->EnableWindow(TRUE);
}


void CDlgProjInfo::OnBnClickedRadioYear()
{
	GetDlgItem(IDC_DATE_PROJ)->EnableWindow(TRUE);
}


void CDlgProjInfo::OnBnClickedButtonModify()
{
	CDlgProject dlg;
	dlg.m_bIsModify = true;
	dlg.m_strCode = m_strCode;
	dlg.m_strInfo = m_strName;
	dlg.m_dbPrice = m_dbPrice;
	dlg.m_dbVipPrice = m_dbVipPrice;

	if (IDCANCEL == dlg.DoModal())
		return;

	MyConnectionOpen();
	CString strSQL;
	strSQL.Format(_T("update 项目信息表 set ProjectCode = '%s', \
					 ProjectName = '%s', \
					 ProjectPrice = %.2f, \
					 ProjectVipPrice = %.2f \
					 where ProjectDate = '%s'"), 
					 dlg.m_strCode, dlg.m_strInfo, 
					 dlg.m_dbPrice, dlg.m_dbVipPrice, m_strDate);

	MyConnectionExecute(strSQL);
	MyConnectionClose();
	
	m_strName = dlg.m_strInfo;
	m_dbPrice = dlg.m_dbPrice;
	m_dbVipPrice = dlg.m_dbVipPrice;
	UpdateData(FALSE);
}


void CDlgProjInfo::OnBnClickedButtonSearch()
{
	UpdateData(TRUE);
	MyListProjInfo();
}
