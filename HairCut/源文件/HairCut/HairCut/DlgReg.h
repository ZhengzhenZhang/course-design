#pragma once


// CDlgReg �Ի���

class CDlgReg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgReg)

public:
	CDlgReg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgReg();

// �Ի�������
	enum { IDD = IDD_DIALOG_REG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strMachine;
	CString m_strReg;
	CString m_strRightReg;
	virtual void OnOK();
};
