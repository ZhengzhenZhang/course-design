// FeeClientView.cpp : CFeeClientView ���ʵ��
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

// CFeeClientView ����/����

CFeeClientView::CFeeClientView()
{
	// TODO: �ڴ˴���ӹ������

}

CFeeClientView::~CFeeClientView()
{
}

BOOL CFeeClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CListView::PreCreateWindow(cs);
}

void CFeeClientView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: ���� GetListCtrl() ֱ�ӷ��� ListView ���б�ؼ���
	//  �Ӷ������������ ListView��
}


// CFeeClientView ���

#ifdef _DEBUG
void CFeeClientView::AssertValid() const
{
	CListView::AssertValid();
}

void CFeeClientView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CFeeClientDoc* CFeeClientView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFeeClientDoc)));
	return (CFeeClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CFeeClientView ��Ϣ�������
