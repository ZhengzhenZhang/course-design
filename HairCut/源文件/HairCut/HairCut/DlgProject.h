#pragma once


// CDlgProject �Ի���

class CDlgProject : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgProject)

public:
	CDlgProject(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgProject();

// �Ի�������
	enum { IDD = IDD_DIALOG_PROJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CString m_strCode;
	CString m_strInfo;
	double m_dbPrice;
	double m_dbVipPrice;

	bool m_bIsModify;
};
