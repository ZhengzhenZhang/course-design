#pragma once
#include "afxwin.h"


// CPastDrugDlg �Ի���

class CPastDrugDlg : public CDialog
{
	DECLARE_DYNAMIC(CPastDrugDlg)

public:
	CPastDrugDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPastDrugDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_PAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
