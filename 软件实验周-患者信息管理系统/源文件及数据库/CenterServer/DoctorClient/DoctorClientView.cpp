// DoctorClientView.cpp : CDoctorClientView ���ʵ��
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

// CDoctorClientView ����/����

CDoctorClientView::CDoctorClientView()
{
	// TODO: �ڴ˴���ӹ������

}

CDoctorClientView::~CDoctorClientView()
{
}

BOOL CDoctorClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CListView::PreCreateWindow(cs);
}

void CDoctorClientView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: ���� GetListCtrl() ֱ�ӷ��� ListView ���б�ؼ���
	//  �Ӷ������������ ListView��
}


// CDoctorClientView ���

#ifdef _DEBUG
void CDoctorClientView::AssertValid() const
{
	CListView::AssertValid();
}

void CDoctorClientView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CDoctorClientDoc* CDoctorClientView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDoctorClientDoc)));
	return (CDoctorClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CDoctorClientView ��Ϣ�������
