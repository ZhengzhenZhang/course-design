#pragma once
#include "afxcmn.h"


// CWorkerDlg 对话框

class CWorkerDlg : public CDialog
{
	DECLARE_DYNAMIC(CWorkerDlg)

public:
	CWorkerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWorkerDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_WORKER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedWorkerAdd();
	void ListTheInfo();
	afx_msg void OnBnClickedWorkerModify();
	afx_msg void OnBnClickedWorkerDelete();
	afx_msg void OnNMDblclkWorkerInfo(NMHDR *pNMHDR, LRESULT *pResult);
};
