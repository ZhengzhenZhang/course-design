#pragma once


// CDlgSearch �Ի���

class CDlgSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSearch)

public:
	CDlgSearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSearch();

// �Ի�������
	enum { IDD = IDD_DIALOG_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSearch;
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();
};
