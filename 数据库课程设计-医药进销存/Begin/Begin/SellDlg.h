#pragma once


// CSellDlg �Ի���

class CSellDlg : public CDialog
{
	DECLARE_DYNAMIC(CSellDlg)

public:
	CSellDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSellDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SELL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_code;
	CString m_name;
	CString m_specification;
	CString m_efficacy;
	CString m_ingredient;
	CString m_dosage;
	float m_selPrice;
	int m_counts;
	UINT m_num;
	float m_totalPrice;
	CString m_csOp;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnUpdateSellNum();
	afx_msg void OnBnClickedOk();
	
	void AddSellRecord();
};
