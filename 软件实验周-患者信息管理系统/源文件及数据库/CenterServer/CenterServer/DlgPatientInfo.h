#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgPatientInfo �Ի���

class CDlgPatientInfo : public CDialog
{
	DECLARE_DYNAMIC(CDlgPatientInfo)

public:
	CDlgPatientInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPatientInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_PATIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelendokComboDtime();
	afx_msg void OnBnClickedButtonOkcancel();
	afx_msg void OnBnClickedEditModsave();
	DECLARE_MESSAGE_MAP()
public:
	void ListPatientInfo(CString strSQL);
	void ListDiagInfo(CString strSQL);
	void ListTimeCombox(CString strSQL);
	void ListFeeInfo(CString strSQL);
	BOOL ModifyDatabase();
	void SetReadOnly(BOOL bReadOnly);
	void InitDialogInfo();
public:
	//0�����ڲ鿴״̬  1�������޸�״̬  2:��ӻ�����Ϣ  3����Ӿ�����Ϣ
	int m_flagOperate;

	//0�����޸�  1�����޸�
	int m_ifModify;	

	CString m_strOldPId;
	CString m_strOldDNum;

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
	CComboBox m_comboDTime;
	CString m_strDDId;
	CString m_strDNum;
	CString m_strDDeclare;
	CString m_strDInitCheck;
	CString m_strDInstruCheck;
	CString m_strDResult;
	CString m_strDScheme;
	CString m_strDRemark;
	CString m_strFeedBack;

	float m_floatFDrug;
	float m_floatFDiag;
	float m_floatFTrans;
	float m_floatFCheck;
	float m_floatFConsum;
	float m_floatFRadiate;
	float m_floatTotalFee;

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
	CEdit m_ctrlDDeclare;
	CEdit m_ctrlDInitCheck;
	CEdit m_ctrlDInstruCheck;
	CEdit m_ctrlDResult;
	CEdit m_ctrlDScheme;
	CEdit m_ctrlDRemark;
	CEdit m_ctrlFDrug;
	CEdit m_ctrlFDiag;
	CEdit m_ctrlFTrans;
	CEdit m_ctrlFCheck;
	CEdit m_ctrlFConsum;
	CEdit m_ctrlFRadiate;
	CEdit m_ctrlTotalFee;
	CEdit m_ctrlFeedBack;
};
