#pragma once


// CDlgWrkPMoney �Ի���

class CDlgWrkPMoney : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWrkPMoney)

public:
	CDlgWrkPMoney(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWrkPMoney();

// �Ի�������
	enum { IDD = IDD_DIALOG_WRKPMONEY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	CString m_strPhone;
	double m_dbPMoney;
	virtual void OnOK();
};
