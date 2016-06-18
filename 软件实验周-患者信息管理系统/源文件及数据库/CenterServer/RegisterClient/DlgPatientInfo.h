#pragma once


// CDlgPatientInfo 对话框

class CDlgPatientInfo : public CDialog
{
	DECLARE_DYNAMIC(CDlgPatientInfo)

public:
	CDlgPatientInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPatientInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_PATIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString m_strPName;
	CString m_strPSex;
	CString m_strPNum;
	UINT m_strPAge;
	CString m_strPId;
	CString m_strPPhone;
	CString m_strPAddr;
	CString m_strPAllergy;
	CString m_strPRemark;

public:

	CString m_strDDId;
	CString m_strDNum;

public:
	CEdit m_ctrlPName;
	CEdit m_ctrlPSex;
	CEdit m_ctrlPNum;
	CEdit m_ctrlPId;
	CEdit m_ctrlPAge;
	CEdit m_ctrlPPhone;
	CEdit m_ctrlPAddr;
	CEdit m_ctrlPAllergy;
	CEdit m_ctrlPRemark;
	CEdit m_ctrlDDId;
	
};
