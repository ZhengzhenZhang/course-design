#pragma once


// CDlgWorker �Ի���

class CDlgWorker : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWorker)

public:
	CDlgWorker(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWorker();

// �Ի�������
	enum { IDD = IDD_DIALOG_WORKER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CString m_strPhone;
	CString m_strName;
	CString m_strCode;
};
