#pragma once


// CBackRecoDlg �Ի���

class CBackRecoDlg : public CDialog
{
	DECLARE_DYNAMIC(CBackRecoDlg)

public:
	CBackRecoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBackRecoDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_BARE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBackup();
	CString sPath;
	CString m_edit;
	virtual BOOL OnInitDialog();
};
