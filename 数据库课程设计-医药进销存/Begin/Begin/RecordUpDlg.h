#pragma once
#include "afxcmn.h"
#include "DtlUpdateSet.h"
#include "afxwin.h"


// CRecordUpDlg �Ի���

class CRecordUpDlg : public CDialog
{
	DECLARE_DYNAMIC(CRecordUpDlg)

public:
	CRecordUpDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRecordUpDlg();

// �Ի�������
	enum { IDD = IDD_RECORD_UPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CDtlUpdateSet set;
	CListCtrl m_list;
	int m_radio;
	COleDateTime m_ftime;
	COleDateTime m_totime;
	CString m_edit;
	afx_msg void OnBnClickedUpdateAll();
	afx_msg void OnBnClickedUpdateLmon();
	afx_msg void OnBnClickedUpdateLweek();
	afx_msg void OnBnClickedUpdateLyest();
	virtual BOOL OnInitDialog();
	void ListTheInfo();
	UINT m_sumNum;
	afx_msg void OnBnClickedUpdateSearch();
public:
	// ��Ӧ��������ȫѡ�༭������
	CEdit m_CSearch;
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
