#pragma once


// CDlgWrkInfo 对话框

class CDlgWrkInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWrkInfo)

public:
	CDlgWrkInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWrkInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_WRKINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	COleDateTime m_timDate;
	CString m_strKWORD;
	CString m_strName;
	CString m_strPhone;
	double m_dbTMoney;
	int m_nTNum;
	CListCtrl m_listInfo;
	int m_nChange;
	virtual BOOL OnInitDialog();
	CListCtrl m_listWage;

public:
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordSet;
	void MyConnectionOpen();
	void MyConnectionExecute(CString strSQL);
	void MyConnectionClose();
	void MyRecordsetOpen(CString strSQL);

public:
	void MyListWrkInfo();
	void MyListWageInfo();
	afx_msg void OnBnClickedButtonSearch();
	
	afx_msg void OnBnClickedRadioAll();
	afx_msg void OnBnClickedRadioDay();
	afx_msg void OnBnClickedRadioMonth();
	afx_msg void OnBnClickedRadioYear();
	afx_msg void OnBnClickedButtonPmoney();
};
