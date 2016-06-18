// ClassRoomDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CClassRoomDlg �Ի���
class CClassRoomDlg : public CDialog
{
// ����
public:
	CClassRoomDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLASSROOM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDtnCloseupDateTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboTbuild();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMDblclkListCrinfo(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

public:
	void CreateLayout();
	void CreateLayout2();
	void ListCSInfo(CString strSQL);
	void ListOCInfo(int nIndex, CString myCNum);
	void ListOCInfoSearch();
	void ListThisTime();
	void ListTBuildComboBox();
	void ClearList();
public:
	CListCtrl m_listCrInfo;
	COleDateTime m_dTime;
	CComboBox m_comboTBuild;
	CString m_strComboTBuild;
	CString m_strCRommNum;
	CFont m_myFont;
	COLORREF m_myColor;
	BOOL m_isSearch;
	int m_nWeek;
protected:
	virtual void OnOK();
	virtual void OnCancel();

	virtual void PreInitDialog();
};

