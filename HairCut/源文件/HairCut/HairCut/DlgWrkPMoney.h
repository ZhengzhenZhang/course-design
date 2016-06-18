#pragma once


// CDlgWrkPMoney 对话框

class CDlgWrkPMoney : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWrkPMoney)

public:
	CDlgWrkPMoney(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWrkPMoney();

// 对话框数据
	enum { IDD = IDD_DIALOG_WRKPMONEY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	CString m_strPhone;
	double m_dbPMoney;
	virtual void OnOK();
};
