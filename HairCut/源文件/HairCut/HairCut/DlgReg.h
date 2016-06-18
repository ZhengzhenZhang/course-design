#pragma once


// CDlgReg 对话框

class CDlgReg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgReg)

public:
	CDlgReg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgReg();

// 对话框数据
	enum { IDD = IDD_DIALOG_REG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strMachine;
	CString m_strReg;
	CString m_strRightReg;
	virtual void OnOK();
};
