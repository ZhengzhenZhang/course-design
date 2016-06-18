#pragma once
#include "afxwin.h"


// CDlgDetail 对话框

class CDlgDetail : public CDialog
{
	DECLARE_DYNAMIC(CDlgDetail)

public:
	CDlgDetail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDetail();

// 对话框数据
	enum { IDD = IDD_DIALOG_DETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	DECLARE_MESSAGE_MAP()
public:
	void ListClassInfo();	// 列出上课信息
	void ListCRoomInfo();	// 列出教室信息
	void ListOCInfo();		// 列出教室占用信息
	
	BOOL ModifyCRData();	// 修改教室以及占用信息
public:
	CString m_strDTime;
	CString m_strDClass1;
	CString m_strDClass2;
	CString m_strDClass3;
	CString m_strDClass4;
	CString m_strDClass5;
	CString m_strDOther;
	CString m_strDCNum;
	CString m_strDTBNum;
	CString m_strDManager;
	CString m_strPhone;
	BOOL m_checkDisPro;
	BOOL m_checkIsDam;
	CString m_strDAddr;
	CString m_strRemark;
	int m_nWeek;
	virtual BOOL OnInitDialog();
	int m_intDVolume;
	CEdit m_editDClass1;
	CEdit m_editDClass2;
	CEdit m_editDClass3;
	CEdit m_editDClass4;
	CEdit m_editDClass5;

	CString m_oldDTBNum;
	CString m_oldDCNum;
	
};
