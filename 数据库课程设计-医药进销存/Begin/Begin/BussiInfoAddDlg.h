#pragma once


// CBussiInfoAddDlg 对话框

class CBussiInfoAddDlg : public CDialog
{
	DECLARE_DYNAMIC(CBussiInfoAddDlg)

public:
	CBussiInfoAddDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBussiInfoAddDlg();

// 对话框数据
	enum { IDD = IDD_BUSSI_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_bcode;
	CString m_tmpCode;
	CString m_phone;
	CString m_name;
	CString m_addr;
	CString m_remark;
	afx_msg void OnBnClickedOk();
	void AddBussiInfo();
	void ModifyBussiInfo();
	BOOL m_ifAdd;
	CString m_csOp;
	virtual BOOL OnInitDialog();
};
