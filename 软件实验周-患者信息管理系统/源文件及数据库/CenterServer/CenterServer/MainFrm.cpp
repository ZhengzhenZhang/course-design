// MainFrm.cpp : CMainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
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
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	// TODO: �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	if (!CreateComboBox())
	{
		TRACE0("��Ͽ򴴽�ʧ�ܣ�");
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}


// CMainFrame ���

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


// CMainFrame ��Ϣ�������

//---------------
//---���ܣ��ڹ����������Ͽ�---
//---����ˣ�������---
//---���ʱ�䣺2012-12-25---
//---�޸�ʱ�䣺2012-12-28---
//---------------
BOOL CMainFrame::CreateComboBox()
{
	int nWidth = 300;	// ��Ͽ���
	int nHeight = 200;	// ��Ͽ�߶�

	int index = 0;

	while (m_wndToolBar.GetItemID(index) != ID_MY_COMBOBOX)
		index++;

	m_wndToolBar.SetButtonInfo(index, ID_MY_COMBOBOX, TBBS_SEPARATOR, nWidth);
	CRect rect;
	m_wndToolBar.GetItemRect(index, &rect);
	rect.top += 5;	// λ�õ���
	rect.left += 5;
	rect.bottom = rect.top + nHeight;
	BOOL rel = m_wndComboBox.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_SORT|CBS_DROPDOWN,
		rect, &m_wndToolBar, ID_MY_COMBOBOX);
	if (!rel) 
	{
		TRACE0("������Ͽ�ʧ�ܣ�");
		return FALSE;
	}

	return TRUE;
}


