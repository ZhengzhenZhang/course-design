#pragma once
#include "afxcmn.h"
#include "SellDtlSet.h"
#include "afxwin.h"


// CRecordSellDlg �Ի���

class CRecordSellDlg : public CDialog
{
	DECLARE_DYNAMIC(CRecordSellDlg)

public:
	CRecordSellDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRecordSellDlg();

// �Ի�������
	enum { IDD = IDD_RECORD_SELL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list;
	int m_radio;
	CSellDtlSet set;
	void ListTheInfo();
	afx_msg void OnBnClickedSellAll();
	afx_msg void OnBnClickedSellLmon();
	afx_msg void OnBnClickedSellLweek();
	afx_msg void OnBnClickedSellLyest();
	float m_sumMny;
	COleDateTime m_ftime;
	COleDateTime m_totime;
	CString m_edit;
	afx_msg void OnBnClickedSellSearch();
	UINT m_sumNum;
public:
	// ��Ӧ��굥����Ϣ
	CEdit m_CSell;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedRadio1();
};
