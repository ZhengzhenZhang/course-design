#pragma once


// CDlgVipPMoney �Ի���

class CDlgVipPMoney : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVipPMoney)

public:
	CDlgVipPMoney(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgVipPMoney();

// �Ի�������
	enum { IDD = IDD_DIALOG_VIPPMONEY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
