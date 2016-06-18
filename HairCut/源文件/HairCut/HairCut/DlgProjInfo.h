#pragma once


// CDlgProjInfo 对话框

class CDlgProjInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgProjInfo)

public:
	CDlgProjInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgProjInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_PROJINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_timDate;
	CString m_strKWORD;
	CString m_strName;
	int m_nTNum;
	double m_dbTMoney;
	CListCtrl m_listInfo;
	int m_nChange;
	CString m_strDate;
	CString m_strCode;
	double m_dbPrice;
	double m_dbVipPrice;

public:
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordSet;
	void MyConnectionOpen();
	void MyConnectionExecute(CString strSQL);
	void MyConnectionClose();
	void MyRecordsetOpen(CString strSQL);
	virtual BOOL OnInitDialog();
	void MyListProjInfo();
	afx_msg void OnBnClickedRadioAll();
	afx_msg void OnBnClickedRadioDay();
	afx_msg void OnBnClickedRadioMonth();
	afx_msg void OnBnClickedRadioYear();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonSearch();
};
