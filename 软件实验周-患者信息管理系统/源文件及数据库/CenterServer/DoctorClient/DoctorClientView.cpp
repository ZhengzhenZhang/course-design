// DoctorClientView.cpp : CDoctorClientView 类的实现
//

#include "stdafx.h"
#include "DoctorClient.h"

#include "DoctorClientDoc.h"
#include "DoctorClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDoctorClientView

IMPLEMENT_DYNCREATE(CDoctorClientView, CListView)

BEGIN_MESSAGE_MAP(CDoctorClientView, CListView)
END_MESSAGE_MAP()

// CDoctorClientView 构造/析构

CDoctorClientView::CDoctorClientView()
{
	// TODO: 在此处添加构造代码

}

CDoctorClientView::~CDoctorClientView()
{
}

BOOL CDoctorClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CListView::PreCreateWindow(cs);
}

void CDoctorClientView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: 调用 GetListCtrl() 直接访问 ListView 的列表控件，
	//  从而可以用项填充 ListView。
}


// CDoctorClientView 诊断

#ifdef _DEBUG
void CDoctorClientView::AssertValid() const
{
	CListView::AssertValid();
}

void CDoctorClientView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CDoctorClientDoc* CDoctorClientView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDoctorClientDoc)));
	return (CDoctorClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CDoctorClientView 消息处理程序
