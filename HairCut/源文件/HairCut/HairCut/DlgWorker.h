#pragma once


// CDlgWorker 对话框

class CDlgWorker : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWorker)

public:
	CDlgWorker(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWorker();

// 对话框数据
	enum { IDD = IDD_DIALOG_WORKER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CString m_strPhone;
	CString m_strName;
	CString m_strCode;
};
