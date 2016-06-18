#pragma once


// CDlgVip 对话框

class CDlgVip : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVip)

public:
	CDlgVip(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVip();

// 对话框数据
	enum { IDD = IDD_DIALOG_VIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CString m_strCode;
	CString m_strName;
	double m_dbMoney;
	CString m_strPhone;
	virtual void OnOK();
	CString m_strCode;
};
