#pragma once


// CDlgConfigPort 对话框

class CDlgConfigPort : public CDialog
{
	DECLARE_DYNAMIC(CDlgConfigPort)

public:
	CDlgConfigPort(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgConfigPort();

// 对话框数据
	enum { IDD = IDD_DIALOG_CONFIGPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	UINT m_uintRegPort;
	UINT m_uintDocPort;
	UINT m_uintFeePort;
	virtual BOOL OnInitDialog();
	void GetHostIp(CString &strIp);
	afx_msg void OnBnClickedOk();
};
