// BeginDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "DrugInfoSet.h"
#define   IsCTRLPressed()  ((GetKeyState(VK_CONTROL) & (1<<(sizeof(SHORT)*8-1)))!= 0)  //判断Ctrl键是否按下.


// CBeginDlg 对话框
class CBeginDlg : public CDialog
{
// 构造
public:
	CBeginDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BEGIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void PreInitDialog();
public:
	afx_msg void OnBnClickedBeginSearch();
	CListCtrl m_list;
	CString m_search;
	CDrugInfoSet setDrug;
	afx_msg void OnNMDblclkListBegin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnQuit();
	afx_msg void OnSellSelect();
	afx_msg void OnWorkerInfo();
	afx_msg void OnBussiInfo();
	afx_msg void OnStoreInfo();
	afx_msg void OnRecordSell();
	afx_msg void OnRecordUpdate();
	afx_msg void OnUpdateDrug();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPastRegister();
	afx_msg void OnRecordPast();
	afx_msg void OnBackupRec();
};
