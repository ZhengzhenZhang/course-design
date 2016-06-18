#pragma once


// CWorkerInfoAddDlg �Ի���

class CWorkerInfoAddDlg : public CDialog
{
	DECLARE_DYNAMIC(CWorkerInfoAddDlg)

public:
	CWorkerInfoAddDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWorkerInfoAddDlg();

// �Ի�������
	enum { IDD = IDD_WORKER_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_ID;
	CString m_name;
	CString m_position;
	CString m_phone;
	BOOL m_ifAdd;
	CString m_tmpID;
	CString m_csOp;
	afx_msg void OnBnClickedOk();
	void ModifyWorkerInfo();
	void AddWorkerInfo();
	virtual BOOL OnInitDialog();
};
