#pragma once
#include "afxwin.h"


// CUpdateDlg 对话框

class CUpdateDlg : public CDialog
{
	DECLARE_DYNAMIC(CUpdateDlg)

public:
	CUpdateDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUpdateDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_UPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_search;
	virtual BOOL OnInitDialog();
	CString m_code;
	CString m_name;
	CString m_specification;
	CString m_efficacy;
	CString m_ingredient;
	CString m_dosage;
	int m_counts;
	int m_tmpCounts;
	int m_tmpNum;
	float m_selPrice;
	float m_tmpPrice;
	CString m_num;
	afx_msg void OnEnUpdateUpdateSearch();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnUpdateUpdateNum();
	void AddUpdateRecord();
public:
	BOOL m_ifStore; // 库存信息中直接更新已有药品，如果为真则直接更新
	BOOL m_ifUpdate;	// 是否已更新，判断文号框是否为空
	CString m_newCode;
public:
	// 为单击全选编辑框文字专门建立的编辑框控件和提前截取消息函数
	// 这三个编辑框是最需要这种功能的
	CEdit m_CNewCode;
	CEdit m_CSearch;
	CEdit m_CSelPrice;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
