#pragma once


// CDlgConfigPort �Ի���

class CDlgConfigPort : public CDialog
{
	DECLARE_DYNAMIC(CDlgConfigPort)

public:
	CDlgConfigPort(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgConfigPort();

// �Ի�������
	enum { IDD = IDD_DIALOG_CONFIGPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	UINT m_uintRegPort;
	UINT m_uintDocPort;
	UINT m_uintFeePort;
	virtual BOOL OnInitDialog();
	void GetHostIp(CString &strIp);
	afx_msg void OnBnClickedOk();
};
