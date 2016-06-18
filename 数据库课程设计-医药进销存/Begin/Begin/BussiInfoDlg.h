#pragma once
#include "afxcmn.h"


// CBussiInfoDlg �Ի���

class CBussiInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CBussiInfoDlg)

public:
	CBussiInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBussiInfoDlg();

// �Ի�������
	enum { IDD = IDD_BUSSI_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	afx_msg void OnBnClickedBussiAdd();
	afx_msg void OnBnClickedBussiDelete();
	afx_msg void OnBnClickedBussiModify();
	void ListTheInfo();
	afx_msg void OnNMDblclkBussiInfo(NMHDR *pNMHDR, LRESULT *pResult);
};
