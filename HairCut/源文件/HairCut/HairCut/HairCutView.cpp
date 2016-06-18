
// HairCutView.cpp : CHairCutView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "HairCut.h"
#endif

#include "HairCutDoc.h"
#include "HairCutView.h"

#include "DlgSell.h"
#include "DlgPay.h"
#include "DlgProject.h"
#include "DlgVip.h"
#include "DlgWorker.h"
#include "DlgVipInfo.h"
#include "DlgVipPMoney.h"
#include "DlgWrkInfo.h"
#include "DlgWrkPMoney.h"
#include "DlgProjInfo.h"
#include "DlgInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHairCutView

IMPLEMENT_DYNCREATE(CHairCutView, CListView)

BEGIN_MESSAGE_MAP(CHairCutView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_INFO_PAY, &CHairCutView::OnInfoPay)
	ON_COMMAND(ID_INFO_PROJECT, &CHairCutView::OnInfoProject)
	ON_UPDATE_COMMAND_UI(ID_INFO_PROJECT, &CHairCutView::OnUpdateInfoProject)
	ON_UPDATE_COMMAND_UI(ID_INFO_PAY, &CHairCutView::OnUpdateInfoPay)
	ON_COMMAND(ID_INFO_SELL, &CHairCutView::OnInfoSell)
	ON_UPDATE_COMMAND_UI(ID_INFO_SELL, &CHairCutView::OnUpdateInfoSell)
	ON_COMMAND(ID_INFO_VIP, &CHairCutView::OnInfoVip)
	ON_UPDATE_COMMAND_UI(ID_INFO_VIP, &CHairCutView::OnUpdateInfoVip)
	ON_COMMAND(ID_INFO_WORKER, &CHairCutView::OnInfoWorker)
	ON_UPDATE_COMMAND_UI(ID_INFO_WORKER, &CHairCutView::OnUpdateInfoWorker)
	ON_COMMAND(ID_OPERATE_INCOME, &CHairCutView::OnOperateIncome)
	ON_COMMAND(ID_OPERATE_SEARCH, &CHairCutView::OnOperateSearch)
	ON_WM_DESTROY()
	
	ON_COMMAND(ID_INFO_CARD, &CHairCutView::OnInfoCard)
	ON_UPDATE_COMMAND_UI(ID_INFO_CARD, &CHairCutView::OnUpdateInfoCard)
	ON_UPDATE_COMMAND_UI(ID_OPERATE_INCOME, &CHairCutView::OnUpdateOperateIncome)
	ON_COMMAND(ID_OPERATE_INFO, &CHairCutView::OnOperateInfo)
	ON_COMMAND(ID_VIP_DMONEY, &CHairCutView::OnVipDmoney)
	ON_COMMAND(ID_VIP_PMONEY, &CHairCutView::OnVipPmoney)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CHairCutView::OnNMDblclk)

	ON_MESSAGE(WM_USER_SEARCH, OnSearch)
	ON_MESSAGE(WM_USER_DIALOG_DESTROYED, OnDialogDestroyed)
	ON_COMMAND(ID_WRK_PMONEY, &CHairCutView::OnWrkPmoney)
	ON_COMMAND(ID_PROJ_DELETE, &CHairCutView::OnProjDelete)
	ON_COMMAND(ID_PROJ_MODIFY, &CHairCutView::OnProjModify)
	ON_COMMAND(ID_WRK_DELETE, &CHairCutView::OnWrkDelete)
	ON_COMMAND(ID_INFO_TOTAL, &CHairCutView::OnInfoTotal)
END_MESSAGE_MAP()

// CHairCutView 构造/析构

CHairCutView::CHairCutView()
{
	// TODO: 在此处添加构造代码
	m_nInfo = 0;
	m_pDlgSearch = NULL;
}

CHairCutView::~CHairCutView()
{
}

BOOL CHairCutView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CListView::PreCreateWindow(cs);
}

void CHairCutView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	m_font.CreatePointFont(110, _T("微软雅黑"));
	GetListCtrl().SetFont(&m_font, TRUE);

	GetDocument()->SetTitle(_T("销售信息"));
	m_nInfo = 0;
	MyCreateListLayout();
	MyListAllDataInfo();
}

void CHairCutView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHairCutView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_MENU_CONTEXT);
	
	CMenu* pContextMenu = NULL;
	if (3 == m_nInfo)
	{
		pContextMenu = menu.GetSubMenu(0);
		pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, 
			point.x, point.y, AfxGetMainWnd());
	}
	else if (4 == m_nInfo)
	{
		pContextMenu = menu.GetSubMenu(1);
		pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, 
			point.x, point.y, AfxGetMainWnd());
	}
	else if (2 == m_nInfo)
	{
		pContextMenu = menu.GetSubMenu(2);
		pContextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, 
			point.x, point.y, AfxGetMainWnd());
	}
}


// CHairCutView 诊断

#ifdef _DEBUG
void CHairCutView::AssertValid() const
{
	CListView::AssertValid();
}


void CHairCutView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}


CHairCutDoc* CHairCutView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHairCutDoc)));
	return (CHairCutDoc*)m_pDocument;
}
#endif //_DEBUG


// CHairCutView 消息处理程序

void CHairCutView::MyListDataInfo(CString strSQL)
{
	MyConnectionOpen();
	MyRecordsetOpen(strSQL);

	CListCtrl& listCtrl = GetListCtrl();
	_variant_t var;
	CString strTmp;
	switch (m_nInfo)
	{
	case 0:
		for (int i = 0; !m_pRecordSet->adoEOF && i < 200; i++)
		{
			var = m_pRecordSet->GetCollect(_T("SellDate"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.InsertItem(i, strTmp);
			
			var = m_pRecordSet->GetCollect(_T("SellProjectName"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 1, strTmp);

			var = m_pRecordSet->GetCollect(_T("SellWorkerName"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 2, strTmp);

			var = m_pRecordSet->GetCollect(_T("SellIsVIP"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 3, strTmp);

			var = m_pRecordSet->GetCollect(_T("SellVipName"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 4, strTmp);

			var = m_pRecordSet->GetCollect(_T("SellPrice"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 5, strTmp);

			m_pRecordSet->MoveNext();
		}
		break;

	case 1:
		for (int i = 0; !m_pRecordSet->adoEOF && i < 200; i++)
		{
			var = m_pRecordSet->GetCollect(_T("PayDate"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.InsertItem(i, strTmp);

			var = m_pRecordSet->GetCollect(_T("PayMoney"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 1, strTmp);

			var = m_pRecordSet->GetCollect(_T("PayInfo"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 2, strTmp);

			var = m_pRecordSet->GetCollect(_T("PayWrkName"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 3, strTmp);

			var = m_pRecordSet->GetCollect(_T("PayWrkPhone"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 4, strTmp);

			m_pRecordSet->MoveNext();
		}
		break;

	case 2:
		for (int i = 0; !m_pRecordSet->adoEOF && i < 200; i++)
		{
			var = m_pRecordSet->GetCollect(_T("ProjectCode"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.InsertItem(i, strTmp);

			var = m_pRecordSet->GetCollect(_T("ProjectName"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 1, strTmp);

			var = m_pRecordSet->GetCollect(_T("ProjectPrice"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 2, strTmp);

			var = m_pRecordSet->GetCollect(_T("ProjectVipPrice"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 3, strTmp);

			var = m_pRecordSet->GetCollect(_T("ProjectDate"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 4, strTmp);

			m_pRecordSet->MoveNext();
		}
		break;

	case 3:
		for (int i = 0; !m_pRecordSet->adoEOF && i < 200; i++)
		{
			var = m_pRecordSet->GetCollect(_T("VipCode"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.InsertItem(i, strTmp);

			var = m_pRecordSet->GetCollect(_T("VipName"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 1, strTmp);

			var = m_pRecordSet->GetCollect(_T("VipPhone"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 2, strTmp);

			var = m_pRecordSet->GetCollect(_T("VipBalance"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 3, strTmp);

			var = m_pRecordSet->GetCollect(_T("VipDate"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 4, strTmp);

			m_pRecordSet->MoveNext();
		}
		break;

	case 4:
		for (int i = 0; !m_pRecordSet->adoEOF && i < 200; i++)
		{
			var = m_pRecordSet->GetCollect(_T("WorkerCode"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.InsertItem(i, strTmp);

			var = m_pRecordSet->GetCollect(_T("WorkerName"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 1, strTmp);

			var = m_pRecordSet->GetCollect(_T("WorkerPhone"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 2, strTmp);

			var = m_pRecordSet->GetCollect(_T("WorkerDate"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 3, strTmp);

			m_pRecordSet->MoveNext();
		}
		break;

	case 5:
		for (int i = 0; !m_pRecordSet->adoEOF && i < 200; i++)
		{
			var = m_pRecordSet->GetCollect(_T("CardDate"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.InsertItem(i, strTmp);

			var = m_pRecordSet->GetCollect(_T("CardInfo"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 1, strTmp);

			var = m_pRecordSet->GetCollect(_T("CardMoney"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 2, strTmp);

			var = m_pRecordSet->GetCollect(_T("CardVipName"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 3, strTmp);

			var = m_pRecordSet->GetCollect(_T("CardVipPhone"));
			strTmp = (var.vt != VT_NULL) ? (CString)var : _T("");
			listCtrl.SetItemText(i, 4, strTmp);

			m_pRecordSet->MoveNext();
		}
		break;
	}

	m_pRecordSet->Close();
	m_pRecordSet.Release();
	MyConnectionClose();
}


void CHairCutView::MyListAllDataInfo()
{
	MyClearListCtrl();
	MyCreateListLayout();

	switch (m_nInfo)
	{
	case 0:
		MyListDataInfo(_T("select * from 销售信息表 order by SellDate DESC"));
		break;

	case 1:
		MyListDataInfo(_T("select * from 支出信息表 order by PayDate DESC"));
		break;

	case 2:
		MyListDataInfo(_T("select * from 项目信息表 order by ProjectName"));
		break;

	case 3:
		MyListDataInfo(_T("select * from 会员信息表 where VipBalance > 0 order by VipName"));
		break;

	case 4:
		MyListDataInfo(_T("select * from 员工信息表 order by WorkerName"));
		break;

	case 5:
		MyListDataInfo(_T("select * from 会员卡信息表 order by CardDate DESC"));
		break;
	}
}


void CHairCutView::MyCreateListLayout()
{
	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.ModifyStyle(0, LVS_REPORT);
	listCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	switch (m_nInfo)
	{
	case 0:
		listCtrl.InsertColumn(0, _T("创建时间"), LVCFMT_LEFT, 170);
		listCtrl.InsertColumn(1, _T("项目信息"), LVCFMT_LEFT, 400);
		listCtrl.InsertColumn(2, _T("员工名"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(3, _T("是否会员"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(4, _T("会员名"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(5, _T("金额"), LVCFMT_LEFT, 100);							
		break;

	case 1:
		listCtrl.InsertColumn(0, _T("创建时间"), LVCFMT_LEFT, 170);
		listCtrl.InsertColumn(1, _T("支出金额"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(2, _T("支出信息"), LVCFMT_LEFT, 400);
		listCtrl.InsertColumn(3, _T("会员名"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(4, _T("联系方式"), LVCFMT_LEFT, 160);
		break;

	case 2:
		listCtrl.InsertColumn(0, _T("助记码"), LVCFMT_LEFT, 0);
		listCtrl.InsertColumn(1, _T("项目名称"), LVCFMT_LEFT, 400);
		listCtrl.InsertColumn(2, _T("价格"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(3, _T("会员价"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(4, _T("创建时间"), LVCFMT_LEFT, 170);
		break;

	case 3:
		listCtrl.InsertColumn(0, _T("助记码"), LVCFMT_LEFT, 0);
		listCtrl.InsertColumn(1, _T("会员名"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(2, _T("联系方式"), LVCFMT_LEFT, 160);
		listCtrl.InsertColumn(3, _T("卡内金额"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(4, _T("创建时间"), LVCFMT_LEFT, 170);
		break;

	case 4:
		listCtrl.InsertColumn(0, _T("助记码"), LVCFMT_LEFT, 0);
		listCtrl.InsertColumn(1, _T("员工名"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(2, _T("联系方式"), LVCFMT_LEFT, 160);
		listCtrl.InsertColumn(3, _T("创建时间"), LVCFMT_LEFT, 170);
		break;

	case 5:
		listCtrl.InsertColumn(0, _T("创建时间"), LVCFMT_LEFT, 170);
		listCtrl.InsertColumn(1, _T("会员卡信息"), LVCFMT_LEFT, 400);
		listCtrl.InsertColumn(2, _T("金额"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(3, _T("会员名"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(4, _T("联系方式"), LVCFMT_LEFT, 160);
		break;
	}
	
}


void CHairCutView::MyClearListCtrl()
{
	CListCtrl& m_myListCtrl = GetListCtrl();

	m_myListCtrl.DeleteAllItems();
	// Delete all of the columns.
	while (m_myListCtrl.DeleteColumn(0));	// 清空标题栏
}


void CHairCutView::OnInfoPay()
{
	GetDocument()->SetTitle(_T("支出信息"));
	m_nInfo = 1;
	MyClearListCtrl();
	MyCreateListLayout();
	MyListAllDataInfo();
}


void CHairCutView::OnUpdateInfoPay(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(1 == m_nInfo);
}


void CHairCutView::OnInfoProject()
{
	GetDocument()->SetTitle(_T("项目信息"));
	m_nInfo = 2;
	MyListAllDataInfo();
}


void CHairCutView::OnUpdateInfoProject(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(2 == m_nInfo);
}


void CHairCutView::OnInfoSell()
{
	GetDocument()->SetTitle(_T("销售信息"));
	m_nInfo = 0;
	MyListAllDataInfo();
}


void CHairCutView::OnUpdateInfoSell(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(0 == m_nInfo);
}


void CHairCutView::OnInfoVip()
{
	GetDocument()->SetTitle(_T("会员信息"));
	m_nInfo = 3;
	MyListAllDataInfo();
}


void CHairCutView::OnUpdateInfoVip(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(3 == m_nInfo);
}


void CHairCutView::OnInfoWorker()
{
	GetDocument()->SetTitle(_T("员工信息"));
	m_nInfo = 4;
	MyListAllDataInfo();
}


void CHairCutView::OnInfoCard()
{
	GetDocument()->SetTitle(_T("会员卡信息"));
	m_nInfo = 5;
	MyListAllDataInfo();
}


void CHairCutView::OnUpdateInfoCard(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(5 == m_nInfo);
}


void CHairCutView::OnUpdateInfoWorker(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(4 == m_nInfo);
}


void CHairCutView::OnProjDelete()
{
	int nIndex = GetListCtrl().GetSelectionMark();
	CString strDate = GetListCtrl().GetItemText(nIndex, 4);	
	CString strInfo = GetListCtrl().GetItemText(nIndex, 1);

	CString strMB;
	strMB.Format(_T("项目名：%s\n\n确定要删除该条目？"), strInfo);
	if (IDCANCEL == MessageBox(strMB, _T("提示"), MB_OKCANCEL | MB_ICONQUESTION))
		return;

	MyConnectionOpen();
	CString strSQL;
	strSQL.Format(_T("delete from 项目信息表 where ProjectDate = '%s'"), strDate);

	MyConnectionExecute(strSQL);
	MyConnectionClose();

	MyListAllDataInfo();
}


void CHairCutView::OnProjModify()
{
	int nIndex = GetListCtrl().GetSelectionMark();
	CString strDate = GetListCtrl().GetItemText(nIndex, 4);	

	CDlgProject dlg;
	dlg.m_bIsModify = true;
	dlg.m_strCode = GetListCtrl().GetItemText(nIndex, 0);
	dlg.m_strInfo = GetListCtrl().GetItemText(nIndex, 1);
	dlg.m_dbPrice = _ttof(GetListCtrl().GetItemText(nIndex, 2));
	dlg.m_dbVipPrice = _ttof(GetListCtrl().GetItemText(nIndex, 3));

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
					 dlg.m_dbPrice, dlg.m_dbVipPrice, strDate);

	MyConnectionExecute(strSQL);
	MyConnectionClose();
	MyListAllDataInfo();
}


void CHairCutView::OnOperateIncome()
{	
	if (0 == m_nInfo)
	{
		
		CDlgSell dlg;
		if (IDCANCEL == dlg.DoModal())
			return;
	}
	else if (1 == m_nInfo)
	{
		CDlgPay dlg;
		if (IDCANCEL == dlg.DoModal())
			return;
		
		MyConnectionOpen();

		CTime tim;
		tim = CTime::GetCurrentTime();

		CString strTim;
		strTim.Format(_T("%4d-%02d-%02d %02d:%02d:%02d"), tim.GetYear(), tim.GetMonth(), 
			tim.GetDay(), tim.GetHour(), tim.GetMinute(), tim.GetSecond());

		CString strSQL;
		strSQL.Format(_T("insert into 支出信息表(PayDate, PayMoney, PayInfo, PayWrkName, PayWrkPhone) \
						 values('%s', %.2lf, '%s', '%s', '%s')"),
				strTim, dlg.m_dbMoney, dlg.m_strInfo, _T(""), _T(""));

		MyConnectionExecute(strSQL);

		MyConnectionClose();
	}
	else if (2 == m_nInfo)
	{
		CDlgProject dlg;
		if (IDCANCEL == dlg.DoModal())
			return;

		MyConnectionOpen();

		CTime tim;
		tim = CTime::GetCurrentTime();

		CString strTim;
		strTim.Format(_T("%4d-%02d-%02d %02d:%02d:%02d"), tim.GetYear(), tim.GetMonth(), 
			tim.GetDay(), tim.GetHour(), tim.GetMinute(), tim.GetSecond());

		CString strSQL;
		strSQL.Format(_T("insert into 项目信息表\
						 (ProjectDate, ProjectCode, ProjectName, ProjectVipPrice, ProjectPrice) \
						 values('%s', '%s', '%s', %.2lf, %.2lf)"),
						 strTim, dlg.m_strCode, dlg.m_strInfo, dlg.m_dbVipPrice, dlg.m_dbPrice);

		MyConnectionExecute(strSQL);

		MyConnectionClose();
	}
	else if (3 == m_nInfo)
	{
		CDlgVip dlg;
		if (IDCANCEL == dlg.DoModal())
			return;

		MyConnectionOpen();

		CTime tim;
		tim = CTime::GetCurrentTime();

		CString strTim;
		strTim.Format(_T("%4d-%02d-%02d %02d:%02d:%02d"), tim.GetYear(), tim.GetMonth(), 
			tim.GetDay(), tim.GetHour(), tim.GetMinute(), tim.GetSecond());

		CString strSQL;
		strSQL.Format(_T("insert into 会员信息表\
						 (VipDate, VipCode, VipName, VipPhone, VipBalance) \
						 values('%s', '%s', '%s', '%s', %.2lf)"),
						 strTim, dlg.m_strCode, dlg.m_strName, dlg.m_strPhone, dlg.m_dbMoney);
		MyConnectionExecute(strSQL);

		strSQL.Format(_T("insert into 会员卡信息表(\
						 CardDate, CardInfo, CardMoney, CardVipCode, CardVipName, CardVipPhone) \
						 values('%s', '%s', %.2lf, '%s', '%s', '%s')"),
						 strTim, _T("创建新会员"), dlg.m_dbMoney, dlg.m_strCode, dlg.m_strName, dlg.m_strPhone);
		MyConnectionExecute(strSQL);

		MyConnectionClose();
	}
	else if (4 == m_nInfo)
	{
		CDlgWorker dlg;
		if (IDCANCEL == dlg.DoModal())
			return;

		MyConnectionOpen();

		CTime tim;
		tim = CTime::GetCurrentTime();

		CString strTim;
		strTim.Format(_T("%4d-%02d-%02d %02d:%02d:%02d"), tim.GetYear(), tim.GetMonth(), 
			tim.GetDay(), tim.GetHour(), tim.GetMinute(), tim.GetSecond());

		CString strSQL;
		strSQL.Format(_T("insert into 员工信息表\
						 (WorkerDate, WorkerCode, WorkerName, WorkerPhone) \
						 values('%s', '%s', '%s', '%s')"),
						 strTim, dlg.m_strCode, dlg.m_strName, dlg.m_strPhone, dlg);

		MyConnectionExecute(strSQL);

		MyConnectionClose();
	}
	
	MyListAllDataInfo();
}


void CHairCutView::OnOperateSearch()
{
	if (m_pDlgSearch != NULL)
		m_pDlgSearch->SetFocus();
	else
	{
		m_pDlgSearch = new CDlgSearch;
		m_pDlgSearch->Create(IDD_DIALOG_SEARCH);
		m_pDlgSearch->ShowWindow(SW_SHOW);
	}
}


void CHairCutView::OnDestroy()
{
	CListView::OnDestroy();
}


void CHairCutView::MyRecordsetOpen(CString strSQL)
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


void CHairCutView::MyConnectionOpen()
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
		AfxMessageBox(_T("数据库连接失败，确认数据库HairCutDataBase.accdb是否在Sys文件夹中！"));
	}
}


void CHairCutView::MyConnectionExecute(CString strSQL)
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


void CHairCutView::MyConnectionClose()
{
	if (m_pConnection->State)
		m_pConnection->Close();
	m_pConnection = NULL;
}


void CHairCutView::OnUpdateOperateIncome(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(5 != m_nInfo);
}


void CHairCutView::OnOperateInfo()
{
	CListCtrl& listCtrl = GetListCtrl();
	int nIndex = listCtrl.GetSelectionMark();
	if (nIndex < 0)
		return;

	if (3 == m_nInfo)
	{
		CDlgVipInfo dlg;
		dlg.m_strCode = listCtrl.GetItemText(nIndex, 0);
		dlg.m_strName = listCtrl.GetItemText(nIndex, 1);
		dlg.m_strPhone = listCtrl.GetItemText(nIndex, 2);
		dlg.m_dbBalance = _ttof(listCtrl.GetItemText(nIndex, 3));
		dlg.DoModal();

		MyListAllDataInfo();
	}
	else if (4 == m_nInfo)
	{
		CDlgWrkInfo dlg;
		dlg.m_strName = listCtrl.GetItemText(nIndex, 1);
		dlg.m_strPhone = listCtrl.GetItemText(nIndex, 2);
		dlg.DoModal();
		MyListAllDataInfo();
	}
	else if (2 == m_nInfo)
	{
		CDlgProjInfo dlg;
		dlg.m_strName = listCtrl.GetItemText(nIndex, 1);
		dlg.m_strDate = listCtrl.GetItemText(nIndex, 4);
		dlg.m_strCode = listCtrl.GetItemText(nIndex, 0);
		dlg.m_dbPrice = _ttof(listCtrl.GetItemText(nIndex, 2));
		dlg.m_dbVipPrice = _ttof(listCtrl.GetItemText(nIndex, 3));
		dlg.DoModal();
		MyListAllDataInfo();
	}
}


void CHairCutView::OnVipDmoney()
{
	CListCtrl& listCtrl = GetListCtrl();
	int nIndex = listCtrl.GetSelectionMark();
	if (nIndex < 0)
		return;

	if (3 == m_nInfo)
	{
		CString strCode = listCtrl.GetItemText(nIndex, 0);
		CString strName = listCtrl.GetItemText(nIndex, 1);
		CString strPhone = listCtrl.GetItemText(nIndex, 2);
		double dbBalance = _ttof(listCtrl.GetItemText(nIndex, 3));
		
		CDlgVipPMoney dlg;
		dlg.m_bDMoney = TRUE;
		dlg.m_dbBalance = dbBalance;
		dlg.m_strName = strName;
		dlg.m_strPhone = strPhone;

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
						 strTim, _T("会员卡提现"), -dlg.m_dbPMoney, strCode, strName, strPhone);
		MyConnectionExecute(strSQL);

		dbBalance -= dlg.m_dbPMoney;
		strSQL.Format(_T("update 会员信息表 set VipBalance = %.2lf where VipPhone = '%s'"), dbBalance, strPhone);
		MyConnectionExecute(strSQL);

		MyConnectionClose();

		MyListAllDataInfo();
	}
}


void CHairCutView::OnVipPmoney()
{
	CListCtrl& listCtrl = GetListCtrl();
	int nIndex = listCtrl.GetSelectionMark();
	if (nIndex < 0)
		return;

	if (3 == m_nInfo)
	{
		CString strCode = listCtrl.GetItemText(nIndex, 0);
		CString strName = listCtrl.GetItemText(nIndex, 1);
		CString strPhone = listCtrl.GetItemText(nIndex, 2);
		double dbBalance = _ttof(listCtrl.GetItemText(nIndex, 3));

		CDlgVipPMoney dlg;
		dlg.m_bDMoney = FALSE;
		dlg.m_dbBalance = dbBalance;
		dlg.m_strName = strName;
		dlg.m_strPhone = strPhone;

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
						 strTim, _T("会员卡充值"), dlg.m_dbPMoney, strCode, strName, strPhone);
		MyConnectionExecute(strSQL);

		dbBalance += dlg.m_dbPMoney;
		strSQL.Format(_T("update 会员信息表 set VipBalance = %.2lf where VipPhone = '%s'"), dbBalance, strPhone);
		MyConnectionExecute(strSQL);

		MyConnectionClose();

		MyListAllDataInfo();
	}
}


void CHairCutView::OnWrkPmoney()
{
	CListCtrl& listCtrl = GetListCtrl();
	int nIndex = listCtrl.GetSelectionMark();
	if (nIndex < 0)
		return;

	if (4 == m_nInfo)
	{
		CDlgWrkPMoney dlg;
		dlg.m_dbPMoney = FALSE;
		dlg.m_strName = listCtrl.GetItemText(nIndex, 1);
		dlg.m_strPhone = listCtrl.GetItemText(nIndex, 2); 

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
						 strTim, dlg.m_dbPMoney, _T("发放工资"), dlg.m_strName, dlg.m_strPhone);
		MyConnectionExecute(strSQL);

		MyConnectionClose();

		MyListAllDataInfo();
	}
}


void CHairCutView::OnWrkDelete()
{
	int nIndex = GetListCtrl().GetSelectionMark();
	CString strPhone = GetListCtrl().GetItemText(nIndex, 2);	
	CString strName = GetListCtrl().GetItemText(nIndex, 1);

	CString strMB;
	strMB.Format(_T("员工名：%s\n\n确定要删除该员工？"), strName);
	if (IDCANCEL == MessageBox(strMB, _T("提示"), MB_OKCANCEL | MB_ICONQUESTION))
		return;

	MyConnectionOpen();
	CString strSQL;
	strSQL.Format(_T("delete from 员工信息表 where WorkerPhone = '%s'"), strPhone);

	MyConnectionExecute(strSQL);
	MyConnectionClose();

	MyListAllDataInfo();
}


void CHairCutView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	
	OnOperateInfo();
}


LRESULT CHairCutView::OnSearch(WPARAM wParam, LPARAM lParam)
{
	SEARCHINFO* sInfo = (SEARCHINFO*)lParam;

	CString strSInfo = sInfo->strSearchInfo;
	
	CString strSQL;

	switch (m_nInfo)
	{
	case 0:
		strSQL.Format(_T("select * from 销售信息表 where \
						 SellDate like '%c%s%c' or \
						 SellProjectCode like '%c%s%c' or \
						 SellProjectName like '%c%s%c' or \
						 SellWorkerCode like '%c%s%c' or \
						 SellWorkerName like '%c%s%c' or \
						 SellWorkerPhone like '%c%s%c' or \
						 SellVipCode like '%c%s%c' or \
						 SellVipName like '%c%s%c' or \
						 SellVipPhone like '%c%s%c' \
						 order by SellDate DESC"),
						 _T('%'), strSInfo, _T('%'), _T('%'), strSInfo, _T('%'), 
						 _T('%'), strSInfo, _T('%'), _T('%'), strSInfo, _T('%'), 
						 _T('%'), strSInfo, _T('%'), _T('%'), strSInfo, _T('%'),
						 _T('%'), strSInfo, _T('%'), _T('%'), strSInfo, _T('%'), 
						 _T('%'), strSInfo, _T('%'));
		break;

	case 1:
		strSQL.Format(_T("select * from 支出信息表 where \
						 PayDate like '%c%s%c' or \
						 PayInfo like '%c%s%c' or \
						 PayWrkName like '%c%s%c' or \
						 PayWrkPhone like '%c%s%c' \
						 order by PayDate DESC"),
						 _T('%'), strSInfo, _T('%'), _T('%'), strSInfo, _T('%'),
						 _T('%'), strSInfo, _T('%'), _T('%'), strSInfo, _T('%'));
		break;

	case 2:
		strSQL.Format(_T("select * from 项目信息表 where \
						 ProjectDate like '%c%s%c' or \
						 ProjectCode like '%c%s%c' or \
						 ProjectName like '%c%s%c' \
						 order by ProjectDate DESC"),
						 _T('%'), strSInfo, _T('%'), _T('%'), strSInfo, _T('%'), 
						 _T('%'), strSInfo, _T('%'));
		break;

	case 3:
		strSQL.Format(_T("select * from 会员信息表 where \
						 VipDate like '%c%s%c' or \
						 VipCode like '%c%s%c' or \
						 VipName like '%c%s%c' or \
						 VipPhone like '%c%s%c' \
						 order by VipDate DESC"),
						 _T('%'), strSInfo, _T('%'), _T('%'), strSInfo, _T('%'), 
						 _T('%'), strSInfo, _T('%'), _T('%'), strSInfo, _T('%'));
		break;

	case 4:
		strSQL.Format(_T("select * from 员工信息表 where \
						 WorkerDate like '%c%s%c' or \
						 WorkerCode like '%c%s%c' or \
						 WorkerName like '%c%s%c' or \
						 WorkerPhone like '%c%s%c' \
						 order by WorkerDate DESC"),
						 _T('%'), strSInfo, _T('%'), _T('%'), strSInfo, _T('%'), 
						 _T('%'), strSInfo, _T('%'), _T('%'), strSInfo, _T('%'));
		break;

	case 5:
		strSQL.Format(_T("select * from 会员卡信息表 where \
						 CardDate like '%c%s%c' or \
						 CardInfo like '%c%s%c' or \
						 CardVipCode like '%c%s%c' or \
						 CardVipName like '%c%s%c' or \
						 CardVipPhone like '%c%s%c' \
						 order by CardDate DESC"),
						 _T('%'), strSInfo, _T('%'), _T('%'), strSInfo, _T('%'), 
						 _T('%'), strSInfo, _T('%'), _T('%'), strSInfo, _T('%'),
						 _T('%'), strSInfo, _T('%'));
		break;
	}

	MyClearListCtrl();
	MyCreateListLayout();
	MyListDataInfo(strSQL);

	return 0;
}


LRESULT CHairCutView::OnDialogDestroyed(WPARAM wParam, LPARAM lParam)
{
	m_pDlgSearch = NULL;
	MyListAllDataInfo();
	return 0;
}


void CHairCutView::OnInfoTotal()
{
	CDlgInfo dlg;

	dlg.DoModal();
}
