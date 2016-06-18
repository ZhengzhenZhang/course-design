// DlgSell.cpp : 实现文件
//

#include "stdafx.h"
#include "HairCut.h"
#include "DlgSell.h"
#include "afxdialogex.h"


// CDlgSell 对话框

IMPLEMENT_DYNAMIC(CDlgSell, CDialogEx)

CDlgSell::CDlgSell(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSell::IDD, pParent)
{
	m_dbPrice = 0.0;
	m_dbTmpPrice = 0;
	m_dbTmpPriceVip = 0;
	m_bIsVip = FALSE;
	m_strProjCode = _T("");
	m_strProjInfo = _T("");
	m_strVipCode = _T("");
	m_strVipInfo = _T("");
	m_strWrkCode = _T("");
	m_strWrkInfo = _T("");
	m_strWrkPhoneInfo = _T("");
	m_strProjCodeInfo = _T("");
	m_strWrkCodeInfo = _T("");
	m_strVipCodeInfo = _T("");
	m_strVipPhoneInfo = _T("");
	m_dbVipBalance = 0;
}

CDlgSell::~CDlgSell()
{
}

void CDlgSell::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_HANDINPUT, m_bHandInput);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_dbPrice);
	DDV_MinMaxDouble(pDX, m_dbPrice, 0, 100000);
	DDX_Text(pDX, IDC_EDIT_PROJCODE, m_strProjCode);
	DDV_MaxChars(pDX, m_strProjCode, 24);
	DDX_Text(pDX, IDC_EDIT_PROJINFO, m_strProjInfo);
	DDV_MaxChars(pDX, m_strProjInfo, 24);
	DDX_Text(pDX, IDC_EDIT_VIPCODE, m_strVipCode);
	DDV_MaxChars(pDX, m_strVipCode, 4);
	DDX_Text(pDX, IDC_EDIT_VIPINFO, m_strVipInfo);
	DDV_MaxChars(pDX, m_strVipInfo, 4);
	DDX_Text(pDX, IDC_EDIT_WRKCODE, m_strWrkCode);
	DDV_MaxChars(pDX, m_strWrkCode, 4);
	DDX_Text(pDX, IDC_EDIT_WRKINFO, m_strWrkInfo);
	DDV_MaxChars(pDX, m_strWrkInfo, 4);
	DDX_Control(pDX, IDC_LIST_PROJ, m_listProj);
	DDX_Control(pDX, IDC_LIST_VIP, m_listVip);
	DDX_Control(pDX, IDC_LIST_WRK, m_listWrk);
	DDX_Check(pDX, IDC_CHECK_ISVIP, m_bIsVip);
}


BEGIN_MESSAGE_MAP(CDlgSell, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_PROJCODE, &CDlgSell::OnEnChangeEditProjcode)
	ON_EN_CHANGE(IDC_EDIT_VIPCODE, &CDlgSell::OnEnChangeEditVipcode)
	ON_EN_CHANGE(IDC_EDIT_WRKCODE, &CDlgSell::OnEnChangeEditWrkcode)
	ON_BN_CLICKED(IDC_CHECK_ISVIP, &CDlgSell::OnBnClickedCheckIsvip)
	ON_BN_CLICKED(IDC_CHECK_HANDINPUT, &CDlgSell::OnBnClickedCheckHandinput)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PROJ, &CDlgSell::OnNMDblclkListProj)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_VIP, &CDlgSell::OnNMDblclkListVip)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_WRK, &CDlgSell::OnNMDblclkListWrk)
	ON_BN_CLICKED(IDOK, &CDlgSell::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgSell::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgSell 消息处理程序


BOOL CDlgSell::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_listProj.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listProj.InsertColumn(0, _T("创建日期"), LVCFMT_LEFT, 0);	// **
	m_listProj.InsertColumn(1, _T("助记码"), LVCFMT_LEFT, 0);
	m_listProj.InsertColumn(2, _T("项目名称"), LVCFMT_LEFT, 175);
	m_listProj.InsertColumn(3, _T("价格"), LVCFMT_LEFT, 80);
	m_listProj.InsertColumn(4, _T("会员价"), LVCFMT_LEFT, 80);

	m_listVip.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listVip.InsertColumn(0, _T("助记码"), LVCFMT_LEFT, 0);
	m_listVip.InsertColumn(1, _T("会员名"), LVCFMT_LEFT, 100);
	m_listVip.InsertColumn(2, _T("联系方式"), LVCFMT_LEFT, 100); // **
	m_listVip.InsertColumn(3, _T("卡内金额"), LVCFMT_LEFT, 75);

	m_listWrk.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listWrk.InsertColumn(0, _T("助记码"), LVCFMT_LEFT, 0);
	m_listWrk.InsertColumn(1, _T("员工名"), LVCFMT_LEFT, 100);
	m_listWrk.InsertColumn(2, _T("联系方式"), LVCFMT_LEFT, 160); // **

	MyListProjInfo();
	MyListVipInfo();
	MyListWrkInfo();

	MyUpdateWndStatus();

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgSell::MyListProjInfo()
{
	m_listProj.DeleteAllItems();
	MyConnectionOpen();

	_variant_t var;
	CString strTmp;

	CString strSQL = _T("select * from 项目信息表 where ProjectCode like ");
	strTmp.Format(_T("'%s%c' order by ProjectName"), m_strProjCode, _T('%'));
	strSQL += strTmp;
	MyRecordsetOpen(strSQL);

	for (int i = 0; !m_pRecordSet->adoEOF && i < 100; i++)
	{
		var = m_pRecordSet->GetCollect(_T("ProjectDate"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listProj.InsertItem(i, strTmp);

		var = m_pRecordSet->GetCollect(_T("ProjectCode"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listProj.SetItemText(i, 1, strTmp);

		var = m_pRecordSet->GetCollect(_T("ProjectName"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listProj.SetItemText(i, 2, strTmp);

		var = m_pRecordSet->GetCollect(_T("ProjectPrice"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listProj.SetItemText(i, 3, strTmp);

		var = m_pRecordSet->GetCollect(_T("ProjectVipPrice"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listProj.SetItemText(i, 4, strTmp);

		m_pRecordSet->MoveNext();
	}


	m_pRecordSet->Close();
	m_pRecordSet.Release();
	MyConnectionClose();
}

void CDlgSell::MyListVipInfo()
{
	m_listVip.DeleteAllItems();
	MyConnectionOpen();

	_variant_t var;
	CString strTmp;

	CString strSQL = _T("select * from 会员信息表 where VipCode like ");
	if (m_strVipCode.GetLength() <= 0)
		strTmp.Format(_T("'%s%c' and VipBalance > 0 order by VipName"), m_strVipCode, _T('%'));
	else
		strTmp.Format(_T("'%s%c' order by VipName"), m_strVipCode, _T('%'));
	strSQL += strTmp;
	MyRecordsetOpen(strSQL);

	for (int i = 0; !m_pRecordSet->adoEOF && i < 100; i++)
	{
		var = m_pRecordSet->GetCollect(_T("VipCode"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listVip.InsertItem(i, strTmp);

		var = m_pRecordSet->GetCollect(_T("VipName"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listVip.SetItemText(i, 1, strTmp);

		var = m_pRecordSet->GetCollect(_T("VipPhone"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listVip.SetItemText(i, 2, strTmp);

		var = m_pRecordSet->GetCollect(_T("VipBalance"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listVip.SetItemText(i, 3, strTmp);

		m_pRecordSet->MoveNext();
	}


	m_pRecordSet->Close();
	m_pRecordSet.Release();
	MyConnectionClose();
}


void CDlgSell::MyListWrkInfo()
{
	m_listWrk.DeleteAllItems();
	MyConnectionOpen();

	_variant_t var;
	CString strTmp;

	CString strSQL = _T("select * from 员工信息表 where WorkerCode like ");
	strTmp = _T("'");
	strTmp += m_strWrkCode;
	strTmp += _T("%'");
	strSQL += strTmp;
	MyRecordsetOpen(strSQL);

	for (int i = 0; !m_pRecordSet->adoEOF && i < 100; i++)
	{
		var = m_pRecordSet->GetCollect(_T("WorkerCode"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listWrk.InsertItem(i, strTmp);

		var = m_pRecordSet->GetCollect(_T("WorkerName"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listWrk.SetItemText(i, 1, strTmp);

		var = m_pRecordSet->GetCollect(_T("WorkerPhone"));
		strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
		m_listWrk.SetItemText(i, 2, strTmp);

		m_pRecordSet->MoveNext();
	}

	m_pRecordSet->Close();
	m_pRecordSet.Release();
	MyConnectionClose();
}


void CDlgSell::MyRecordsetOpen(CString strSQL)
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


void CDlgSell::MyConnectionOpen()
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


void CDlgSell::MyConnectionExecute(CString strSQL)
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


void CDlgSell::MyConnectionClose()
{
	if (m_pConnection->State)
		m_pConnection->Close();
	m_pConnection = NULL;
}


void CDlgSell::OnEnChangeEditProjcode()
{
	UpdateData(TRUE);
	MyListProjInfo();
}


void CDlgSell::OnEnChangeEditVipcode()
{
	UpdateData(TRUE);
	MyListVipInfo();
}


void CDlgSell::OnEnChangeEditWrkcode()
{
	UpdateData(TRUE);
	MyListWrkInfo();
}


void CDlgSell::OnBnClickedCheckIsvip()
{
	UpdateData(TRUE);

	if (m_bIsVip)
	{
		m_dbPrice = m_dbTmpPriceVip;
	}
	else
	{
		m_dbPrice = m_dbTmpPrice;
		m_strVipInfo = _T("");
		m_strVipCodeInfo = _T("");
		m_strVipPhoneInfo = _T("");
		UpdateData(FALSE);
	}
	MyUpdateWndStatus();
}


void CDlgSell::MyUpdateWndStatus()
{
	if (m_bHandInput)
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PROJINFO))->SetReadOnly(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT_PRICE))->SetReadOnly(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT_VIPINFO))->SetReadOnly(TRUE);
		((CEdit*)GetDlgItem(IDC_EDIT_WRKINFO))->SetReadOnly(TRUE);
		GetDlgItem(IDC_LIST_PROJ)->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT_PROJCODE))->SetReadOnly(TRUE);
	}
	else
	{
		((CEdit*)GetDlgItem(IDC_EDIT_PRICE))->SetReadOnly(TRUE);
		((CEdit*)GetDlgItem(IDC_EDIT_VIPINFO))->SetReadOnly(TRUE);
		((CEdit*)GetDlgItem(IDC_EDIT_PROJINFO))->SetReadOnly(TRUE);
		((CEdit*)GetDlgItem(IDC_EDIT_WRKINFO))->SetReadOnly(TRUE);
		GetDlgItem(IDC_CHECK_ISVIP)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIST_VIP)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIST_PROJ)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIST_WRK)->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_EDIT_VIPCODE))->SetReadOnly(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT_PROJCODE))->SetReadOnly(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT_WRKCODE))->SetReadOnly(FALSE);
	}

	if (m_bIsVip)
	{
		GetDlgItem(IDC_LIST_VIP)->EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_EDIT_VIPCODE))->SetReadOnly(FALSE);
	}
	else
	{
		GetDlgItem(IDC_LIST_VIP)->EnableWindow(FALSE);
		((CEdit*)GetDlgItem(IDC_EDIT_VIPCODE))->SetReadOnly(TRUE);
	}

	UpdateData(FALSE);
}

void CDlgSell::OnBnClickedCheckHandinput()
{
	UpdateData(TRUE);

	m_strProjCodeInfo = _T("");
	m_strProjDateInfo = _T("");

	MyUpdateWndStatus();
}


void CDlgSell::OnNMDblclkListProj(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	UpdateData(TRUE);

	int nIndex = m_listProj.GetSelectionMark();

	if (nIndex >= 0)
	{
		m_strProjDateInfo = m_listProj.GetItemText(nIndex, 0);
		m_strProjCodeInfo = m_listProj.GetItemText(nIndex, 1);
		m_strProjInfo = m_listProj.GetItemText(nIndex, 2);

		CString strTmp;
		strTmp = m_listProj.GetItemText(nIndex, 3);
		m_dbTmpPrice = _ttof(strTmp.GetBuffer(strTmp.GetLength()));
		strTmp = m_listProj.GetItemText(nIndex, 4);
		m_dbTmpPriceVip = _ttof(strTmp.GetBuffer(strTmp.GetLength()));

		if (m_bIsVip)
			m_dbPrice = m_dbTmpPriceVip;
		else
			m_dbPrice = m_dbTmpPrice;

		UpdateData(FALSE);
	}
}


void CDlgSell::OnNMDblclkListVip(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	UpdateData(TRUE);

	int index = m_listVip.GetSelectionMark();

	if (index >= 0)
	{
		m_strVipCodeInfo = m_listVip.GetItemText(index, 0);
		m_strVipInfo = m_listVip.GetItemText(index, 1);
		m_strVipPhoneInfo = m_listVip.GetItemText(index, 2);
		m_dbVipBalance = _ttof(m_listVip.GetItemText(index, 3));

		UpdateData(FALSE);
	}
}


void CDlgSell::OnNMDblclkListWrk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	UpdateData(TRUE);

	int index = m_listWrk.GetSelectionMark();

	if (index >= 0)
	{
		m_strWrkCodeInfo = m_listWrk.GetItemText(index, 0);
		m_strWrkInfo = m_listWrk.GetItemText(index, 1);
		m_strWrkPhoneInfo = m_listWrk.GetItemText(index, 2);
		UpdateData(FALSE);
	}
}


void CDlgSell::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (m_strProjInfo.GetLength() <= 0)
	{
		MessageBox(_T("项目信息不能为空！"), _T("提示"), MB_ICONINFORMATION);
		return;
	}

	if (m_strWrkInfo.GetLength() <= 0)
	{
		MessageBox(_T("员工信息不能为空！"), _T("提示"), MB_ICONINFORMATION);
		return;
	}

	CString strTmp;
	if (m_bIsVip)
	{
		if (m_strVipInfo.GetLength() <= 0)
		{
			MessageBox(_T("会员信息不能为空！"), _T("提示"), MB_ICONINFORMATION);
			return;
		}
		if (m_dbVipBalance < m_dbPrice)
		{
			MessageBox(_T("余额不足，请充值！"), _T("提示"), MB_ICONINFORMATION);
			m_strVipInfo = _T("");
			UpdateData(FALSE);
			return;
		}

		strTmp.Format(_T("请再次确认该条销售记录！\n\n项目信息： %s\n\n员工信息： %s\n\n价格信息： %.2lf\n\n会员信息： %s  卡内余额： %.2lf"),
			m_strProjInfo, m_strWrkInfo, m_dbPrice, m_strVipInfo, m_dbVipBalance - m_dbPrice);
	}
	else
	{
		strTmp.Format(_T("请再次确认该条销售记录！\n\n项目信息： %s\n\n员工信息： %s\n\n价格信息： %.2lf"),
			m_strProjInfo, m_strWrkInfo, m_dbPrice);
	}

	if (m_dbPrice < 1e-9)
	{
		MessageBox(_T("金额不能为0！"), _T("提示"), MB_ICONINFORMATION);
		return;
	}

	if (IDCANCEL == MessageBox(strTmp, _T("提示"), MB_ICONINFORMATION | MB_OKCANCEL))
	{
		return;
	}

	MyConnectionOpen();
	
	CTime tim;
	tim = CTime::GetCurrentTime();

	CString strTim;
	strTim.Format(_T("%4d-%02d-%02d %02d:%02d:%02d"), tim.GetYear(), tim.GetMonth(), 
		tim.GetDay(), tim.GetHour(), tim.GetMinute(), tim.GetSecond());

	CString strSQL;
	strSQL.Format(_T("insert into 销售信息表(\
					 SellDate,\
					 SellProjectDate, SellProjectCode, SellProjectName,\
					 SellWorkerPhone, SellWorkerCode, SellWorkerName,\
					 SellIsVIP,\
					 SellVipPhone, SellVipCode, SellVipName,\
					 SellPrice) \
					 values('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', %.2lf)"),
					 strTim,
					 m_strProjDateInfo, m_strProjCodeInfo, m_strProjInfo, 
					 m_strWrkPhoneInfo, m_strWrkCodeInfo, m_strWrkInfo,
					 m_bIsVip ? _T("是") : _T("否"),
					 m_strVipPhoneInfo, m_strVipCodeInfo, m_strVipInfo,
					 m_dbPrice
					 );
	
 	MyConnectionExecute(strSQL);
	
	if (m_bIsVip)
	{
		strSQL.Format(_T("update 会员信息表 set VipBalance = %.2lf where VipPhone = '%s'"), 
			m_dbVipBalance - m_dbPrice, m_strVipPhoneInfo);

		MyConnectionExecute(strSQL);

		strSQL.Format(_T("insert into 会员卡信息表(\
						 CardDate, CardInfo, CardMoney, CardVipCode, CardVipName, CardVipPhone) \
						 values('%s', '%s', %.2lf, '%s', '%s', '%s')"),
						 strTim, m_strProjInfo, -m_dbPrice, 
						 m_strVipCodeInfo, m_strVipInfo, m_strVipPhoneInfo);

		MyConnectionExecute(strSQL);
	}

	MyConnectionClose();
	
	CDialogEx::OnOK();
}




void CDlgSell::OnBnClickedCancel()
{
	if (IDCANCEL == MessageBox(_T("确定要取消操作？"), _T("提示"), MB_ICONQUESTION | MB_OKCANCEL))
	{
		return;
	}

	CDialogEx::OnCancel();
}
