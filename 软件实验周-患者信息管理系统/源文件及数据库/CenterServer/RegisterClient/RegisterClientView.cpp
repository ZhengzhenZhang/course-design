// RegisterClientView.cpp : CRegisterClientView ���ʵ��
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

// CRegisterClientView ����/����

CRegisterClientView::CRegisterClientView()
{
	// TODO: �ڴ˴���ӹ������

}

CRegisterClientView::~CRegisterClientView()
{
}

BOOL CRegisterClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

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
	listCtrl.InsertColumn(1, _T("ʱ��"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(2, _T("����"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(3, _T("�Ա�"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(4, _T("����"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(5, _T("���֤"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(6, _T("��ϵ��ʽ"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(7, _T("����ҽʦ���"), LVCFMT_CENTER, 100);

	// TODO: ���� GetListCtrl() ֱ�ӷ��� ListView ���б�ؼ���
	//  �Ӷ������������ ListView��
}


// CRegisterClientView ���

#ifdef _DEBUG
void CRegisterClientView::AssertValid() const
{
	CListView::AssertValid();
}

void CRegisterClientView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CRegisterClientDoc* CRegisterClientView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRegisterClientDoc)));
	return (CRegisterClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CRegisterClientView ��Ϣ�������

void CRegisterClientView::OnMymenuPatientinfo()
{
	// TODO: �ڴ���������������
	AfxBeginThread(ThreadProc1, this);
}


void CRegisterClientView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	*pResult = 0;
}

