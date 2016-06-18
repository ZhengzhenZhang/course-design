// ClassRoomDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CClassRoomDlg 对话框
class CClassRoomDlg : public CDialog
{
// 构造
public:
	CClassRoomDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLASSROOM_DIALOG };

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
	afx_msg void OnDtnCloseupDateTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboTbuild();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMDblclkListCrinfo(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

public:
	void CreateLayout();
	void CreateLayout2();
	void ListCSInfo(CString strSQL);
	void ListOCInfo(int nIndex, CString myCNum);
	void ListOCInfoSearch();
	void ListThisTime();
	void ListTBuildComboBox();
	void ClearList();
public:
	CListCtrl m_listCrInfo;
	COleDateTime m_dTime;
	CComboBox m_comboTBuild;
	CString m_strComboTBuild;
	CString m_strCRommNum;
	CFont m_myFont;
	COLORREF m_myColor;
	BOOL m_isSearch;
	int m_nWeek;
protected:
	virtual void OnOK();
	virtual void OnCancel();

	virtual void PreInitDialog();
};

