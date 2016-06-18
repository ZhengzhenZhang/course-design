#pragma once


// CDlgVipInfo �Ի���

class CDlgVipInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVipInfo)

public:
	CDlgVipInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgVipInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_VIPINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	COleDateTime m_timDate;
	double m_dbBalance;
	CString m_strKWORD;
	CString m_strName;
	CString m_strPhone;
	double m_dbTMoney;
	CListCtrl m_listInfo;
	int m_nChange;
	CString m_strCode;

public:
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordSet;
	void MyConnectionOpen();
	void MyConnectionExecute(CString strSQL);
	void MyConnectionClose();
	void MyRecordsetOpen(CString strSQL);

public:
	void MyListVipCardInfo();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonPmoney();
	afx_msg void OnBnClickedRadioAll();
	afx_msg void OnBnClickedRadioYear();
	afx_msg void OnBnClickedRadioMonth();
	afx_msg void OnBnClickedButtonDmoney();
};
