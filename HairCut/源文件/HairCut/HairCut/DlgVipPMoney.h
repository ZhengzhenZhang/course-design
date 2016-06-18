#pragma once


// CDlgVipPMoney 对话框

class CDlgVipPMoney : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVipPMoney)

public:
	CDlgVipPMoney(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgVipPMoney();

// 对话框数据
	enum { IDD = IDD_DIALOG_VIPPMONEY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	double m_dbBalance;
	CString m_strPhone;
	double m_dbPMoney;
	virtual BOOL OnInitDialog();

public:
	BOOL m_bDMoney;
	virtual void OnOK();
};
