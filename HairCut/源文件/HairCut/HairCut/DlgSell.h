#pragma once


// CDlgSell 对话框

class CDlgSell : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSell)

public:
	CDlgSell(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSell();

// 对话框数据
	enum { IDD = IDD_DIALOG_SELL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL m_bHandInput;
	double m_dbPrice;
	double m_dbTmpPrice;
	double m_dbTmpPriceVip;
	CString m_strProjCode;
	CString m_strVipCode;
	CString m_strWrkCode;
	CListCtrl m_listProj;
	CListCtrl m_listVip;
	CListCtrl m_listWrk;

	CString m_strProjDateInfo;
	CString m_strProjCodeInfo;
	CString m_strProjInfo;
	CString m_strWrkCodeInfo;
	CString m_strWrkPhoneInfo;
	CString m_strWrkInfo;
	CString m_strVipCodeInfo;
	CString m_strVipPhoneInfo;
	CString m_strVipInfo;

	BOOL m_bIsVip;

	double m_dbVipBalance;

public:
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordSet;

	void MyConnectionOpen();
	void MyConnectionExecute(CString strSQL);
	void MyConnectionClose();
	void MyRecordsetOpen(CString strSQL);

	void MyListProjInfo();
	void MyListVipInfo();
	void MyListWrkInfo();

	void MyUpdateWndStatus();

	afx_msg void OnEnChangeEditProjcode();
	afx_msg void OnEnChangeEditVipcode();
	afx_msg void OnEnChangeEditWrkcode();
	afx_msg void OnBnClickedCheckIsvip();
	
	afx_msg void OnBnClickedCheckHandinput();
	afx_msg void OnNMDblclkListProj(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListVip(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListWrk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
