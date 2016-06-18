#pragma once
#include "afxcmn.h"
#include "SellDtlSet.h"
#include "afxwin.h"


// CRecordSellDlg 对话框

class CRecordSellDlg : public CDialog
{
	DECLARE_DYNAMIC(CRecordSellDlg)

public:
	CRecordSellDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRecordSellDlg();

// 对话框数据
	enum { IDD = IDD_RECORD_SELL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	int m_radio;
	CSellDtlSet set;
	void ListTheInfo();
	afx_msg void OnBnClickedSellAll();
	afx_msg void OnBnClickedSellLmon();
	afx_msg void OnBnClickedSellLweek();
	afx_msg void OnBnClickedSellLyest();
	float m_sumMny;
	COleDateTime m_ftime;
	COleDateTime m_totime;
	CString m_edit;
	afx_msg void OnBnClickedSellSearch();
	UINT m_sumNum;
public:
	// 相应鼠标单击消息
	CEdit m_CSell;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedRadio1();
};
