#pragma once
#include "afxwin.h"


// CDlgLogin 对话框

class CDlgLogin : public CDialog
{
	DECLARE_DYNAMIC(CDlgLogin)

public:
	CDlgLogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLogin();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strDocId;
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
public:
	int m_Style;
	CString m_strDocPas;
};
