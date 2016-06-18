#pragma once
#include "afxwin.h"


// CPastDrugDlg 对话框

class CPastDrugDlg : public CDialog
{
	DECLARE_DYNAMIC(CPastDrugDlg)

public:
	CPastDrugDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPastDrugDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_PAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_search;
	CString m_code;
	CString m_name;
	float m_totalPrice;
	COleDateTime m_pastTime;
	UINT m_num;
	int m_counts;
	CString m_specification;
	CString m_ingredient;
	CString m_efficacy;
	CString m_dosage;
	float m_selPrice;
	BOOL m_ifUpdate;
	afx_msg void OnEnUpdatePastSearch();
	afx_msg void OnEnUpdatePastNum();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_CSearch;
	CEdit m_CNum;
	afx_msg void OnBnClickedOk();
	void AddSellRecord();
	CString m_mark;
};
