#pragma once
#include "afxcmn.h"


// CBussiInfoDlg 对话框

class CBussiInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CBussiInfoDlg)

public:
	CBussiInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBussiInfoDlg();

// 对话框数据
	enum { IDD = IDD_BUSSI_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	afx_msg void OnBnClickedBussiAdd();
	afx_msg void OnBnClickedBussiDelete();
	afx_msg void OnBnClickedBussiModify();
	void ListTheInfo();
	afx_msg void OnNMDblclkBussiInfo(NMHDR *pNMHDR, LRESULT *pResult);
};
