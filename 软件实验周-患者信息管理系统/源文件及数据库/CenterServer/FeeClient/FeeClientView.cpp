// FeeClientView.cpp : CFeeClientView 类的实现
//

#include "stdafx.h"
#include "FeeClient.h"

#include "FeeClientDoc.h"
#include "FeeClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFeeClientView

IMPLEMENT_DYNCREATE(CFeeClientView, CListView)

BEGIN_MESSAGE_MAP(CFeeClientView, CListView)
END_MESSAGE_MAP()

// CFeeClientView 构造/析构

CFeeClientView::CFeeClientView()
{
	// TODO: 在此处添加构造代码

}

CFeeClientView::~CFeeClientView()
{
}

BOOL CFeeClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CListView::PreCreateWindow(cs);
}

void CFeeClientView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: 调用 GetListCtrl() 直接访问 ListView 的列表控件，
	//  从而可以用项填充 ListView。
}


// CFeeClientView 诊断

#ifdef _DEBUG
void CFeeClientView::AssertValid() const
{
	CListView::AssertValid();
}

void CFeeClientView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CFeeClientDoc* CFeeClientView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFeeClientDoc)));
	return (CFeeClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CFeeClientView 消息处理程序
