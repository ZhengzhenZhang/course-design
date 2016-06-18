#pragma once
#include "afxwin.h"


// CUpdateDlg �Ի���

class CUpdateDlg : public CDialog
{
	DECLARE_DYNAMIC(CUpdateDlg)

public:
	CUpdateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUpdateDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_UPDATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	BOOL m_ifStore; // �����Ϣ��ֱ�Ӹ�������ҩƷ�����Ϊ����ֱ�Ӹ���
	BOOL m_ifUpdate;	// �Ƿ��Ѹ��£��ж��ĺſ��Ƿ�Ϊ��
	CString m_newCode;
public:
	// Ϊ����ȫѡ�༭������ר�Ž����ı༭��ؼ�����ǰ��ȡ��Ϣ����
	// �������༭��������Ҫ���ֹ��ܵ�
	CEdit m_CNewCode;
	CEdit m_CSearch;
	CEdit m_CSelPrice;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
