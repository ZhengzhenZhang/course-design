#pragma once


// CDlgPay �Ի���

class CDlgPay : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPay)

public:
	CDlgPay(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPay();

// �Ի�������
	enum { IDD = IDD_DIALOG_PAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	double m_dbMoney;
	CString m_strInfo;
	double m_dbMoney;
	virtual void OnOK();
};
