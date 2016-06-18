#pragma once


// CDlgProject 对话框

class CDlgProject : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgProject)

public:
	CDlgProject(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgProject();

// 对话框数据
	enum { IDD = IDD_DIALOG_PROJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CString m_strCode;
	CString m_strInfo;
	double m_dbPrice;
	double m_dbVipPrice;

	bool m_bIsModify;
};
