
// HairCutView.h : CHairCutView ��Ľӿ�
//

#pragma once

#include "DlgSearch.h"

class CHairCutView : public CListView
{
protected: // �������л�����
	CHairCutView();
	DECLARE_DYNCREATE(CHairCutView)

// ����
public:
	CHairCutDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CHairCutView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	int m_nInfo;		// 0:������Ϣ 1��֧����Ϣ 2����Ŀ��Ϣ 3����Ա��Ϣ 4��Ա����Ϣ 5����Ա����¼
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordSet;
	CFont m_font;
	CDlgSearch* m_pDlgSearch;

public:
	void MyListAllDataInfo();
	void MyListDataInfo(CString strSQL);
	void MyCreateListLayout();
	void MyClearListCtrl();

	void MyConnectionOpen();
	void MyConnectionExecute(CString strSQL);
	void MyConnectionClose();
	void MyRecordsetOpen(CString strSQL);

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnInfoPay();
	afx_msg void OnInfoProject();
	afx_msg void OnUpdateInfoProject(CCmdUI *pCmdUI);
	afx_msg void OnUpdateInfoPay(CCmdUI *pCmdUI);
	afx_msg void OnInfoSell();
	afx_msg void OnUpdateInfoSell(CCmdUI *pCmdUI);
	afx_msg void OnInfoVip();
	afx_msg void OnUpdateInfoVip(CCmdUI *pCmdUI);
	afx_msg void OnInfoWorker();
	afx_msg void OnUpdateInfoWorker(CCmdUI *pCmdUI);
	afx_msg void OnOperateIncome();
	afx_msg void OnOperateSearch();
	afx_msg void OnDestroy();
	afx_msg void OnInfoCard();
	afx_msg void OnUpdateInfoCard(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOperateIncome(CCmdUI *pCmdUI);
	afx_msg void OnOperateInfo();
	afx_msg void OnVipDmoney();
	afx_msg void OnVipPmoney();
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg LRESULT OnSearch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDialogDestroyed(WPARAM wParam, LPARAM lParam);
	afx_msg void OnWrkPmoney();
	afx_msg void OnProjDelete();
	afx_msg void OnProjModify();
	afx_msg void OnWrkDelete();
	afx_msg void OnInfoTotal();
};

#ifndef _DEBUG  // HairCutView.cpp �еĵ��԰汾
inline CHairCutDoc* CHairCutView::GetDocument() const
   { return reinterpret_cast<CHairCutDoc*>(m_pDocument); }
#endif

