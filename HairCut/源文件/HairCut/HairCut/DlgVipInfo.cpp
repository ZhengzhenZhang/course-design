// DlgVipInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgVipInfo.h"
#include "afxdialogex.h"
#include "DlgVipPMoney.h"
#include <math.h>


// CDlgVipInfo 对话框

IMPLEMENT_DYNAMIC(CDlgVipInfo, CDialogEx)

CDlgVipInfo::CDlgVipInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgVipInfo::IDD, pParent)
{
	m_timDate = COleDateTime::GetCurrentTime();
	m_dbBalance = 0.0;
	m_strKWORD = _T("");
	m_strName = _T("");
	m_strPhone = _T("");
	m_dbTMoney = 0.0;
	m_nChange = 0;
	m_strCode = _T("");
}

CDlgVipInfo::~CDlgVipInfo()
{
}

void CDlgVipInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATE_VIP, m_timDate);
	DDX_Text(pDX, IDC_EDIT_BALANCE, m_dbBalance);
	DDV_MinMaxDouble(pDX, m_dbBalance, 0, 10000000);
	DDX_Text(pDX, IDC_EDIT_KWORD, m_strKWORD);
	DDV_MaxChars(pDX, m_strKWORD, 24);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 4);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
	DDV_MaxChars(pDX, m_strPhone, 11);
	DDX_Text(pDX, IDC_EDIT_TMONEY, m_dbTMoney);
	DDV_MinMaxDouble(pDX, m_dbTMoney, 0, 100000000);
	DDX_Control(pDX, IDC_LIST_VIP, m_listInfo);
	DDX_Radio(pDX, IDC_RADIO_ALL, m_nChange);
}


BEGIN_MESSAGE_MAP(CDlgVipInfo, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgVipInfo::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_PMONEY, &CDlgVipInfo::OnBnClickedButtonPmoney)
	ON_BN_CLICKED(IDC_RADIO_ALL, &CDlgVipInfo::OnBnClickedRadioAll)
	ON_BN_CLICKED(IDC_RADIO_YEAR, &CDlgVipInfo::OnBnClickedRadioYear)
	ON_BN_CLICKED(IDC_RADIO_MONTH, &CDlgVipInfo::OnBnClickedRadioMonth)
	ON_BN_CLICKED(IDC_BUTTON_DMONEY, &CDlgVipInfo::OnBnClickedButtonDmoney)
END_MESSAGE_MAP()


// CDlgVipInfo 消息处理程序


BOOL CDlgVipInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_listInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_listInfo.InsertColumn(0, _T("创建时间"), LVCFMT_LEFT, 160);
	m_listInfo.InsertColumn(1, _T("信息"), LVCFMT_LEFT, 400);
	m_listInfo.InsertColumn(2, _T("金额"), LVCFMT_LEFT, 100);

	GetDlgItem(IDC_DATE_VIP)->EnableWindow(FALSE);
	MyListVipCardInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgVipInfo::MyRecordsetOpen(CString strSQL)
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


void CDlgVipInfo::MyConnectionOpen()
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


void CDlgVipInfo::MyConnectionExecute(CString strSQL)
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


void CDlgVipInfo::MyConnectionClose()
{
	if (m_pConnection->State)
		m_pConnection->Close();
	m_pConnection = NULL;
}


void CDlgVipInfo::MyListVipCardInfo()
{
	m_listInfo.DeleteAllItems();
	MyConnectionOpen();

	CString strSQL;
	CString strSQLSum;

	switch (m_nChange)
	{
	case 0:
		strSQL.Format(_T("select * from 会员卡信息表 \
						 where CardVipPhone = '%s' and CardInfo like '%c%s%c'order by CardDate DESC"), 
						 m_strPhone, _T('%'), m_strKWORD, _T('%'));
		strSQLSum.Format(_T("select sum(CardMoney) from 会员卡信息表 \
						 where CardVipPhone = '%s' and CardInfo like '%c%s%c' \
						 and CardInfo <> '会员卡充值' and CardInfo <> '会员卡提现' \
						 and CardInfo <> '创建新会员'"), 
						 m_strPhone, _T('%'), m_strKWORD, _T('%'));
		break;

	case 1:
		strSQL.Format(_T("select * from 会员卡信息表 \
						 where CardVipPhone = '%s' and CardInfo like '%c%s%c' \
						 and CardDate like '%4d-%c'order by CardDate DESC"), 
						 m_strPhone, _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), _T('%'));
		strSQLSum.Format(_T("select sum(CardMoney) from 会员卡信息表 \
						 where CardVipPhone = '%s' and CardInfo like '%c%s%c' \
						 and CardDate like '%4d-%c' \
						 and CardInfo <> '会员卡充值' and CardInfo <> '会员卡提现' \
						 and CardInfo <> '创建新会员'"), 
						 m_strPhone, _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), _T('%'));
		break;

	case 2:
		strSQL.Format(_T("select * from 会员卡信息表 \
						 where CardVipPhone = '%s' and CardInfo like '%c%s%c' \
						 and CardDate like '%4d-%02d-%c'order by CardDate DESC"), 
						 m_strPhone, _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), 
						 m_timDate.GetMonth(), _T('%'));
		strSQLSum.Format(_T("select sum(CardMoney) from 会员卡信息表 \
						 where CardVipPhone = '%s' and CardInfo like '%c%s%c' \
						 and CardDate like '%4d-%02d-%c' \
						 and CardInfo <> '会员卡充值' and CardInfo <> '会员卡提现' \
						 and CardInfo <> '创建新会员'"), 
						 m_strPhone, _T('%'), m_strKWORD, _T('%'), m_timDate.GetYear(), 
						 m_timDate.GetMonth(), _T('%'));
		break;
	}
	
	MyRecordsetOpen(strSQL);

	_variant_t var;
	CString strTmp;
	m_dbTMoney = 0;
	for (int i = 0; !m_pRecordSet->adoEOF && i < 100; i++)
	{
		var = m_pRecordSet->GetCollect(_T("CardDate"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listInfo.InsertItem(i, strTmp);
		
		var = m_pRecordSet->GetCollect(_T("CardInfo"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listInfo.SetItemText(i, 1, strTmp);

		var = m_pRecordSet->GetCollect(_T("CardMoney"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listInfo.SetItemText(i, 2, strTmp);
		
		m_pRecordSet->MoveNext();
	}
	
	MyRecordsetOpen(strSQLSum);
	var = m_pRecordSet->GetCollect(_variant_t((long)0));

	strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
	m_dbTMoney = fabs(_ttof(strTmp));

	m_pRecordSet->Close();
	m_pRecordSet.Release();
	MyConnectionClose();

	UpdateData(FALSE);
}


void CDlgVipInfo::OnBnClickedButtonSearch()
{
	UpdateData(TRUE);
	MyListVipCardInfo();
}


void CDlgVipInfo::OnBnClickedButtonPmoney()
{
	CDlgVipPMoney dlg;
	dlg.m_bDMoney = FALSE;
	dlg.m_dbBalance = m_dbBalance;
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
	strSQL.Format(_T("insert into 会员卡信息表(\
					 CardDate, CardInfo, CardMoney, CardVipCode, CardVipName, CardVipPhone) \
					 values('%s', '%s', %.2lf, '%s', '%s', '%s')"),
					 strTim, _T("会员卡充值"), dlg.m_dbPMoney, m_strCode, m_strName, m_strPhone);
	MyConnectionExecute(strSQL);

	m_dbBalance += dlg.m_dbPMoney;
	strSQL.Format(_T("update 会员信息表 set VipBalance = %.2lf where VipPhone = '%s'"), m_dbBalance, m_strPhone);
	MyConnectionExecute(strSQL);

	MyConnectionClose();

	MyListVipCardInfo();
}


void CDlgVipInfo::OnBnClickedButtonDmoney()
{
	CDlgVipPMoney dlg;
	dlg.m_bDMoney = TRUE;
	dlg.m_dbBalance = m_dbBalance;
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
	strSQL.Format(_T("insert into 会员卡信息表(\
					 CardDate, CardInfo, CardMoney, CardVipCode, CardVipName, CardVipPhone) \
					 values('%s', '%s', %.2lf, '%s', '%s', '%s')"),
					 strTim, _T("会员卡提现"), -dlg.m_dbPMoney, m_strCode, m_strName, m_strPhone);
	MyConnectionExecute(strSQL);

	m_dbBalance -= dlg.m_dbPMoney;
	strSQL.Format(_T("update 会员信息表 set VipBalance = %.2lf where VipPhone = '%s'"), m_dbBalance, m_strPhone);
	MyConnectionExecute(strSQL);

	MyConnectionClose();

	MyListVipCardInfo();
}


void CDlgVipInfo::OnBnClickedRadioAll()
{
	GetDlgItem(IDC_DATE_VIP)->EnableWindow(FALSE);
}


void CDlgVipInfo::OnBnClickedRadioYear()
{
	GetDlgItem(IDC_DATE_VIP)->EnableWindow(TRUE);
}


void CDlgVipInfo::OnBnClickedRadioMonth()
{
	GetDlgItem(IDC_DATE_VIP)->EnableWindow(TRUE);
}



