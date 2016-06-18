// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "CenterServer.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	if (!CreateComboBox())
	{
		TRACE0("组合框创建失败！");
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序

//---------------
//---功能：在工具栏添加组合框---
//---完成人：张政桢---
//---完成时间：2012-12-25---
//---修改时间：2012-12-28---
//---------------
BOOL CMainFrame::CreateComboBox()
{
	int nWidth = 300;	// 组合框宽度
	int nHeight = 200;	// 组合框高度

	int index = 0;

	while (m_wndToolBar.GetItemID(index) != ID_MY_COMBOBOX)
		index++;

	m_wndToolBar.SetButtonInfo(index, ID_MY_COMBOBOX, TBBS_SEPARATOR, nWidth);
	CRect rect;
	m_wndToolBar.GetItemRect(index, &rect);
	rect.top += 5;	// 位置调整
	rect.left += 5;
	rect.bottom = rect.top + nHeight;
	BOOL rel = m_wndComboBox.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_SORT|CBS_DROPDOWN,
		rect, &m_wndToolBar, ID_MY_COMBOBOX);
	if (!rel) 
	{
		TRACE0("创建组合框失败！");
		return FALSE;
	}

	return TRUE;
}


