#pragma once


// CDlgSearch 对话框

class CDlgSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSearch)

public:
	CDlgSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSearch();

// 对话框数据
	enum { IDD = IDD_DIALOG_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSearch;
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();
};
