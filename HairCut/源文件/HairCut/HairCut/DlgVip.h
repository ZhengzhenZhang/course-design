#pragma once


// CDlgVip �Ի���

class CDlgVip : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVip)

public:
	CDlgVip(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgVip();

// �Ի�������
	enum { IDD = IDD_DIALOG_VIP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CString m_strCode;
	CString m_strName;
	double m_dbMoney;
	CString m_strPhone;
	virtual void OnOK();
	CString m_strCode;
};
