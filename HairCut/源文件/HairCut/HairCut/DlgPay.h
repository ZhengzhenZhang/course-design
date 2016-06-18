#pragma once


// CDlgPay 对话框

class CDlgPay : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPay)

public:
	CDlgPay(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPay();

// 对话框数据
	enum { IDD = IDD_DIALOG_PAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	double m_dbMoney;
	CString m_strInfo;
	double m_dbMoney;
	virtual void OnOK();
};
