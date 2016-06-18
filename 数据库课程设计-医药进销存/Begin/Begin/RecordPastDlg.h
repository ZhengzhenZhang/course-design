#pragma once
#include "afxcmn.h"
#include "DtlPastSet.h"
#include "afxwin.h"


// CRecordPastDlg �Ի���

class CRecordPastDlg : public CDialog
{
	DECLARE_DYNAMIC(CRecordPastDlg)

public:
	CRecordPastDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRecordPastDlg();

// �Ի�������
	enum { IDD = IDD_RECORD_PAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	COleDateTime m_ftime;
	COleDateTime m_totime;
	CString m_edit;
	UINT m_sumNum;
	float m_sumMny;
	int m_radio;
	CListCtrl m_list;
	afx_msg void OnBnClickedPastAll();
	afx_msg void OnBnClickedPastLmon();
	afx_msg void OnBnClickedPastLweek();
	afx_msg void OnBnClickedPastLyest();
	virtual BOOL OnInitDialog();
	void ListTheInfo();
	CDtlPastSet set;
	afx_msg void OnBnClickedPastSearch();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_CPast;
};
