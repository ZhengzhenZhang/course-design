#pragma once
#include "afxcmn.h"
#include "DtlDrugSet.h"


// CStoreInfoDlg 对话框

class CStoreInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CStoreInfoDlg)

public:
	CStoreInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStoreInfoDlg();

// 对话框数据
	enum { IDD = IDD_STORE_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_code;
	CListCtrl m_list;
	int m_radio;
	CDtlDrugSet set;
	void ListTheInfo();
	afx_msg void OnBnClickedStoreAll();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedStoreSearch();
	afx_msg void OnBnClickedStoreLack();
	afx_msg void OnBnClickedStoreNormal();
	afx_msg void OnBnClickedStoreEx();
	afx_msg void OnNMDblclkStoreInfo(NMHDR *pNMHDR, LRESULT *pResult);
	UINT m_tNum;
};
