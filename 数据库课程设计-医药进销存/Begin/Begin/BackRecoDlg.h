#pragma once


// CBackRecoDlg 对话框

class CBackRecoDlg : public CDialog
{
	DECLARE_DYNAMIC(CBackRecoDlg)

public:
	CBackRecoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBackRecoDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_BARE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBackup();
	CString sPath;
	CString m_edit;
	virtual BOOL OnInitDialog();
};
