// RegisterClientView.cpp : CRegisterClientView 类的实现
//

#include "stdafx.h"
#include "RegisterClient.h"

#include "RegisterClientDoc.h"
#include "RegisterClientView.h"

#include "ThreadProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRegisterClientView

IMPLEMENT_DYNCREATE(CRegisterClientView, CListView)

BEGIN_MESSAGE_MAP(CRegisterClientView, CListView)
	ON_COMMAND(ID_MYMENU_PATIENTINFO, &CRegisterClientView::OnMymenuPatientinfo)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CRegisterClientView::OnNMDblclk)
END_MESSAGE_MAP()

// CRegisterClientView 构造/析构

CRegisterClientView::CRegisterClientView()
{
	// TODO: 在此处添加构造代码

}

CRegisterClientView::~CRegisterClientView()
{
}

BOOL CRegisterClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CListView::PreCreateWindow(cs);
}

PatientInfo drg[500];
int tNum = 0;

void CRegisterClientView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	
	CListCtrl& listCtrl = GetListCtrl();


	listCtrl.ModifyStyle(0, LVS_REPORT);
	listCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	listCtrl.InsertColumn(0, _T(""), LVCFMT_CENTER, 30);
	listCtrl.InsertColumn(1, _T("时间"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(2, _T("姓名"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(3, _T("性别"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(4, _T("年龄"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(5, _T("身份证"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(6, _T("联系方式"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(7, _T("就诊医师编号"), LVCFMT_CENTER, 100);

	// TODO: 调用 GetListCtrl() 直接访问 ListView 的列表控件，
	//  从而可以用项填充 ListView。
}


// CRegisterClientView 诊断

#ifdef _DEBUG
void CRegisterClientView::AssertValid() const
{
	CListView::AssertValid();
}

void CRegisterClientView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CRegisterClientDoc* CRegisterClientView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRegisterClientDoc)));
	return (CRegisterClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CRegisterClientView 消息处理程序

void CRegisterClientView::OnMymenuPatientinfo()
{
	// TODO: 在此添加命令处理程序代码
	AfxBeginThread(ThreadProc1, this);
}


void CRegisterClientView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码


	*pResult = 0;
}

