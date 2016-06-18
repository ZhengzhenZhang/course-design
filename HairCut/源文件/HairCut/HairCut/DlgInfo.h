#pragma once


// CDlgInfo 对话框

class CDlgInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInfo)

public:
	CDlgInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_TOTAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_timDate;
	CString m_strKWORD;
	double m_dbGMoney;
	double m_dbPMoney;
	double m_dbSMoney;
	double m_dbVMoney;
	CListCtrl m_listPInfo;
	CListCtrl m_listSInfo;
	int m_nChange;

public:
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordSet;
	void MyConnectionOpen();
	void MyConnectionExecute(CString strSQL);
	void MyConnectionClose();
	void MyRecordsetOpen(CString strSQL);

public:
	void MyListSellInfo();
	void MyListPayInfo();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioAll();
	afx_msg void OnBnClickedRadioDay();
	afx_msg void OnBnClickedRadioMonth();
	afx_msg void OnBnClickedRadioYear();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonExport();
};
