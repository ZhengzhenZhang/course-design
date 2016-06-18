
// HairCutView.h : CHairCutView 类的接口
//

#pragma once

#include "DlgSearch.h"

class CHairCutView : public CListView
{
protected: // 仅从序列化创建
	CHairCutView();
	DECLARE_DYNCREATE(CHairCutView)

// 特性
public:
	CHairCutDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CHairCutView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	int m_nInfo;		// 0:销售信息 1：支出信息 2：项目信息 3：会员信息 4：员工信息 5：会员卡记录
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

// 生成的消息映射函数
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

#ifndef _DEBUG  // HairCutView.cpp 中的调试版本
inline CHairCutDoc* CHairCutView::GetDocument() const
   { return reinterpret_cast<CHairCutDoc*>(m_pDocument); }
#endif

