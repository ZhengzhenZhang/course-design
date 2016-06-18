// DlgPatientInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CenterServer.h"
#include "DlgPatientInfo.h"
#include "RecordsetPatient.h"
#include "RecordsetDiag.h"
#include "RecordsetFee.h"


// CDlgPatientInfo �Ի���

IMPLEMENT_DYNAMIC(CDlgPatientInfo, CDialog)

CDlgPatientInfo::CDlgPatientInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPatientInfo::IDD, pParent)
	, m_strPName(_T(""))
	, m_strPSex(_T(""))
	, m_strPNum(_T(""))
	, m_strPAge(0)
	, m_strPId(_T(""))
	, m_strPPhone(_T(""))
	, m_strPAddr(_T(""))
	, m_strPAllergy(_T(""))
	, m_strPRemark(_T(""))
	, m_strDDId(_T(""))
	, m_strDNum(_T(""))
	, m_strDDeclare(_T(""))
	, m_strDInitCheck(_T(""))
	, m_strDInstruCheck(_T(""))
	, m_strDResult(_T(""))
	, m_strDScheme(_T(""))
	, m_strDRemark(_T(""))
	, m_strFeedBack(_T(""))
	, m_floatFDrug(0)
	, m_floatFDiag(0)
	, m_floatFTrans(0)
	, m_floatFCheck(0)
	, m_floatFConsum(0)
	, m_floatFRadiate(0)
	, m_floatTotalFee(0)
{
	m_flagOperate = 0;
	m_ifModify = 0;
}

CDlgPatientInfo::~CDlgPatientInfo()
{
}

void CDlgPatientInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PNAME, m_strPName);
	DDX_Text(pDX, IDC_EDIT_PSEX, m_strPSex);
	DDX_Text(pDX, IDC_EDIT_PNUM, m_strPNum);
	DDX_Text(pDX, IDC_EDIT_PAGE, m_strPAge);
	DDX_Text(pDX, IDC_EDIT_PID, m_strPId);
	DDX_Text(pDX, IDC_EDIT_PPHONE, m_strPPhone);
	DDX_Text(pDX, IDC_EDIT_PADDR, m_strPAddr);
	DDX_Text(pDX, IDC_EDIT_PALLERGY, m_strPAllergy);
	DDX_Text(pDX, IDC_EDIT_PREMARK, m_strPRemark);
	DDX_Control(pDX, IDC_COMBO_DTIME, m_comboDTime);
	DDX_Text(pDX, IDC_EDIT_DDID, m_strDDId);
	DDX_Text(pDX, IDC_EDIT_DNUM, m_strDNum);
	DDX_Text(pDX, IDC_EDIT_DDECLARE, m_strDDeclare);
	DDX_Text(pDX, IDC_EDIT_DINITCHECK, m_strDInitCheck);
	DDX_Text(pDX, IDC_EDIT_DINSTRUCHECK, m_strDInstruCheck);
	DDX_Text(pDX, IDC_EDIT_DRESULT, m_strDResult);
	DDX_Text(pDX, IDC_EDIT_DSCHEME, m_strDScheme);
	DDX_Text(pDX, IDC_EDIT_DREMARK, m_strDRemark);
	DDX_Text(pDX, IDC_EDIT_FEEDBACK, m_strFeedBack);

	DDX_Text(pDX, IDC_EDIT_FDRUG, m_floatFDrug);
	DDX_Text(pDX, IDC_EDIT_FDIAG, m_floatFDiag);
	DDX_Text(pDX, IDC_EDIT_FTRANS, m_floatFTrans);
	DDX_Text(pDX, IDC_EDIT_FCHECK, m_floatFCheck);
	DDX_Text(pDX, IDC_EDIT_FCONSUM, m_floatFConsum);
	DDX_Text(pDX, IDC_EDIT_FRADIATE, m_floatFRadiate);
	DDX_Text(pDX, IDC_EDIT_TOTALFEE, m_floatTotalFee);
	DDX_Control(pDX, IDC_EDIT_PNAME, m_ctrlPName);
	DDX_Control(pDX, IDC_EDIT_PSEX, m_ctrlPSex);
	DDX_Control(pDX, IDC_EDIT_PNUM, m_ctrlPNum);
	DDX_Control(pDX, IDC_EDIT_PID, m_ctrlPId);
	DDX_Control(pDX, IDC_EDIT_PAGE, m_ctrlPAge);
	DDX_Control(pDX, IDC_EDIT_PPHONE, m_ctrlPPhone);
	DDX_Control(pDX, IDC_EDIT_PADDR, m_ctrlPAddr);
	DDX_Control(pDX, IDC_EDIT_PALLERGY, m_ctrlPAllergy);
	DDX_Control(pDX, IDC_EDIT_PREMARK, m_ctrlPRemark);
	DDX_Control(pDX, IDC_EDIT_DDID, m_ctrlDDId);
	DDX_Control(pDX, IDC_EDIT_DDECLARE, m_ctrlDDeclare);
	DDX_Control(pDX, IDC_EDIT_DINITCHECK, m_ctrlDInitCheck);
	DDX_Control(pDX, IDC_EDIT_DINSTRUCHECK, m_ctrlDInstruCheck);
	DDX_Control(pDX, IDC_EDIT_DRESULT, m_ctrlDResult);
	DDX_Control(pDX, IDC_EDIT_DSCHEME, m_ctrlDScheme);
	DDX_Control(pDX, IDC_EDIT_DREMARK, m_ctrlDRemark);
	DDX_Control(pDX, IDC_EDIT_FDRUG, m_ctrlFDrug);
	DDX_Control(pDX, IDC_EDIT_FDIAG, m_ctrlFDiag);
	DDX_Control(pDX, IDC_EDIT_FTRANS, m_ctrlFTrans);
	DDX_Control(pDX, IDC_EDIT_FCHECK, m_ctrlFCheck);
	DDX_Control(pDX, IDC_EDIT_FCONSUM, m_ctrlFConsum);
	DDX_Control(pDX, IDC_EDIT_FRADIATE, m_ctrlFRadiate);
	DDX_Control(pDX, IDC_EDIT_TOTALFEE, m_ctrlTotalFee);
	DDX_Control(pDX, IDC_EDIT_FEEDBACK, m_ctrlFeedBack);
}


BEGIN_MESSAGE_MAP(CDlgPatientInfo, CDialog)
	ON_CBN_SELENDOK(IDC_COMBO_DTIME, &CDlgPatientInfo::OnCbnSelendokComboDtime)
	ON_BN_CLICKED(ID_BUTTON_OKCANCEL, &CDlgPatientInfo::OnBnClickedButtonOkcancel)
	ON_BN_CLICKED(ID_EDIT_MODSAVE, &CDlgPatientInfo::OnBnClickedEditModsave)
END_MESSAGE_MAP()


// CDlgPatientInfo ��Ϣ�������

BOOL CDlgPatientInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	InitDialogInfo();	// ���ȵ��ó�ʼ���Ի��򲼾ֺ���
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//---------------
//---���ܣ��ھ�����Ϣ��Ͽ���ѡ����Ӧ�ľ�����Ϣ---
//---����ˣ�������---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺---
//---------------
void CDlgPatientInfo::OnCbnSelendokComboDtime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index;
	index = m_comboDTime.GetCurSel();
	CString strTmp, strSQL;
	m_comboDTime.GetLBText(index, strTmp);
	
	strSQL.Format(_T("diagNum = '%s'"), strTmp);

	ListDiagInfo(strSQL);

	ListFeeInfo(strSQL);
}


//---------------
//---���ܣ�����SQL���������ʱ����Ͽ��г����о����¼---
//---����ˣ�������---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺---
//---------------
void CDlgPatientInfo::ListTimeCombox(CString strSQL)
{
	CRecordsetDiag setDiag;

	setDiag.m_strFilter = strSQL;

	if (!setDiag.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	CString strTmp;

	for (int i=0; !setDiag.IsEOF(); i++)
	{
		strTmp.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
			setDiag.m_diagNum.GetYear(), setDiag.m_diagNum.GetMonth(), setDiag.m_diagNum.GetDay(),
			setDiag.m_diagNum.GetHour(), setDiag.m_diagNum.GetMinute(), setDiag.m_diagNum.GetSecond());
		if (0==i && _T("") == m_strDNum)
			m_strDNum = strTmp;
		m_comboDTime.AddString(strTmp);
		setDiag.MoveNext();
	}

	setDiag.Close();
}
//---------------
//---���ܣ��޸ĺͱ��水ť��Ϣ��Ӧ����---
//---����ˣ�������---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
void CDlgPatientInfo::OnBnClickedEditModsave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (0 == m_flagOperate)
	{
		m_flagOperate = 1;
		SetReadOnly(FALSE);			// ��Ϊ�޸�״̬
		GetDlgItem(ID_BUTTON_MODSAVE)->SetWindowText(_T("����"));
		GetDlgItem(ID_BUTTON_OKCANCEL)->SetWindowText(_T("ȡ��"));
	}
	else if (1 == m_flagOperate)
	{
		if (IDOK == MessageBox(_T("ȷ���޸ģ�"), _T("��ʾ"), MB_OKCANCEL))
		{
			// ����ִ�����ݿ��޸Ĳ���
			if (ModifyDatabase())
			{
				MessageBox(_T("�޸ĳɹ�"), _T("��ʾ"), MB_OK);
				GetDlgItem(ID_BUTTON_MODSAVE)->SetWindowText(_T("�޸�"));
				GetDlgItem(ID_BUTTON_OKCANCEL)->SetWindowText(_T("ȷ��"));
				m_flagOperate = 0;
				UpdateData(FALSE);
				SetReadOnly(TRUE);		// ��Ϊֻ��״̬
			}
			else
			{
				MessageBox(_T("�޸�ʧ��"), _T("��ʾ"), MB_OK);
			}
		}
	}
	else if (2 == m_flagOperate || 3 == m_flagOperate)	// ���Ϊ���
	{
		if (IDOK == MessageBox(_T("ȷ����ӣ�"), _T("��ʾ"), MB_OKCANCEL))
		{
			// ����ִ�����ݿ��޸Ĳ���
			if (ModifyDatabase())
			{
				MessageBox(_T("��ӳɹ�"), _T("��ʾ"), MB_OK);
				OnOK();
			}
			else
			{
				MessageBox(_T("���ʧ��"), _T("��ʾ"), MB_OK);
			}
		}
	}
}

//---------------
//---���ܣ�ȷ����ȡ����ť��Ϣ��Ӧ����---
//---����ˣ�������---
//---���ʱ�䣺2012-12-27---
//---�޸�ʱ�䣺---
//---------------
void CDlgPatientInfo::OnBnClickedButtonOkcancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (0 == m_flagOperate)		
	{
		OnOK();
	}
	else if (1 == m_flagOperate) // ���Ϊ�޸�
	{
		m_flagOperate = 0;
		UpdateData(FALSE);
		GetDlgItem(ID_BUTTON_MODSAVE)->SetWindowText(_T("�޸�"));
		GetDlgItem(ID_BUTTON_OKCANCEL)->SetWindowText(_T("ȷ��"));

		SetReadOnly(TRUE);	// ��Ϊֻ��״̬
	}
	else if (2 == m_flagOperate || 3 == m_flagOperate) // ���Ϊ���
	{
		OnOK();
	}

}

//---------------
//---���ܣ��ú���ʵ�ֶԻ��߾�����Ϣ���ݿ��������޸�---
//---����ˣ�������---
//---���ʱ�䣺2012-12-27---
//---�޸�ʱ�䣺---
//---------------
BOOL CDlgPatientInfo::ModifyDatabase()
{
	// ��ΪҪ����������Ҫ����ԭ������ֵ

	UpdateData(TRUE);
	CDatabase db;
	if (!db.Open(_T("���߾������ݿ�")))
	{
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
		return FALSE;
	}

	CString strSQL;
	// ���»�����Ϣ����ɾ������룬�ɱ���ԭ�ȱ��������ݣ�
	if (m_flagOperate = 1)	// ���Ϊ�޸ĵĻ�
	{
		strSQL.Format(_T("DELETE FROM ������Ϣ WHERE idNumber = '%s'"), m_strOldPId);
		db.ExecuteSQL(strSQL);
	}
	if (m_flagOperate != 3)	// ���������Ӿ�����Ϣ
	{
		strSQL.Format(_T("INSERT INTO ������Ϣ VALUES ")
			_T("('%s','%s','%s','%d','%s','%s','%s','%s','%s')"),
			m_strPId, m_strPName, m_strPSex, m_strPAge, m_strPPhone,
			m_strPAddr, m_strPNum, m_strPAllergy, m_strPRemark);
		db.ExecuteSQL(strSQL);
	}
	// ���¾�����Ϣ
	CString strTmp;
	GetDlgItem(IDC_STATIC_TIME)->GetWindowText(strTmp);

	if (1 == m_flagOperate)
	{
		strSQL.Format(_T("DELETE FROM ������Ϣ WHERE diagNum = '%s'"), m_strOldDNum);
		db.ExecuteSQL(strSQL);
		if ("" != m_strOldDNum)
			strTmp = m_strOldDNum;	// ������޸ĵĻ������޸�ʱ��
	}
	strSQL.Format(_T("INSERT INTO ������Ϣ VALUES ")
		_T("('%s','%s','%s','%s','%s','%s','%s','%s', '%s', '%s')"),
		strTmp, m_strPId, strTmp, m_strDDId, m_strDDeclare, m_strDInitCheck,
		m_strDInstruCheck, m_strDResult, m_strDScheme,m_strDRemark);
	db.ExecuteSQL(strSQL);

	// ���·�����Ϣ���ȼ����ܼ۸�
	m_floatTotalFee = m_floatFDrug+m_floatFDiag+m_floatFCheck
		+ m_floatFConsum+m_floatFTrans+m_floatFRadiate;
	if (1 == m_flagOperate)
	{
		strSQL.Format(_T("DELETE FROM ������Ϣ WHERE diagNum = '%s'"), m_strOldDNum);
		db.ExecuteSQL(strSQL);
	}
	strSQL.Format(_T("INSERT INTO ������Ϣ VALUES ")
		_T("('%s','%f','%f','%f','%f','%f','%f','%f')"),
		strTmp, m_floatFDrug, m_floatFDiag, m_floatFTrans,
		m_floatFCheck, m_floatFConsum, m_floatFRadiate, m_floatTotalFee);
	db.ExecuteSQL(strSQL);

	// ���·�����Ϣ
	if (1 == m_flagOperate)
	{
		strSQL.Format(_T("DELETE FROM ���ָ������Ϣ WHERE diagNum = '%s'"), m_strOldDNum);
		db.ExecuteSQL(strSQL);
	}
	strSQL.Format(_T("INSERT INTO ���ָ������Ϣ VALUES ")
		_T("('%s','%s')"), strTmp, m_strFeedBack);
	db.ExecuteSQL(strSQL);

	db.Close();

	m_ifModify = 1;	// ���Ϊ���޸�״̬

	return TRUE;
}

//---------------
//---���ܣ�����m_flagOperate��ǵĲ�ͬ��ʼ���Ի���---
//---����ˣ�������---
//---���ʱ�䣺2012-12-27---
//---�޸�ʱ�䣺---
//---------------
void CDlgPatientInfo::InitDialogInfo()
{
	CTime tmpTime = CTime::GetCurrentTime();
	CString strTime;

	strTime.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
		tmpTime.GetYear(), tmpTime.GetMonth(), tmpTime.GetDay(),
		tmpTime.GetHour(), tmpTime.GetMinute(), tmpTime.GetSecond());

	GetDlgItem(IDC_STATIC_TIME)->SetWindowText(strTime);
	GetDlgItem(IDC_COMBO_DTIME)->SetWindowText(strTime);
	// ���Ϊ���
	if (2 == m_flagOperate || 3 == m_flagOperate)	
	{
		GetDlgItem(ID_BUTTON_MODSAVE)->SetWindowText(_T("���"));
		GetDlgItem(ID_BUTTON_OKCANCEL)->SetWindowText(_T("ȡ��"));

		if (3 == m_flagOperate)
		{
			CString strSQL;
			strSQL.Format(_T("idNumber = '%s'"), m_strPId);
			ListPatientInfo(strSQL);
		}
		return;
	}

	if (1 == m_flagOperate)
	{
		GetDlgItem(ID_BUTTON_MODSAVE)->SetWindowText(_T("����"));
		GetDlgItem(ID_BUTTON_OKCANCEL)->SetWindowText(_T("ȡ��"));
	}

	if (0 == m_flagOperate)
		SetReadOnly(TRUE);

	// ��ʼ�Ի�����ʾ������Ϣ
	// ������ʾ���߻�����Ϣ
	// Ȼ���г����߾���ʱ���¼
	// ����г����߾�����Ϣ
	CString strSQL;
	strSQL.Format(_T("idNumber = '%s'"), m_strPId);
	ListPatientInfo(strSQL);
	ListTimeCombox(strSQL);

	strSQL.Format(_T("diagNum = '%s'"), m_strDNum);
	ListFeeInfo(strSQL);
	ListDiagInfo(strSQL);
}










//---------------
//---���ܣ�����SQL��������г�������Ϣ---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺---
//---------------
void CDlgPatientInfo::ListPatientInfo(CString strSQL)
{
	CRecordsetPatient setPatient;

	setPatient.m_strFilter = strSQL;

	if (!setPatient.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
	
	if (setPatient.IsEOF()) {
		setPatient.Close();
		return;
	}
	CString strTmp;

	m_strPName = setPatient.m_patientName;
	m_strPName.TrimRight();
	m_strPSex = setPatient.m_patientSex;
	m_strPSex.TrimRight();
	m_strPNum = setPatient.m_patientNum;
	m_strPNum.TrimRight();
	m_strPAge = (UINT)setPatient.m_patientAge;
	m_strPId = setPatient.m_idNumber;
	m_strPId.TrimRight();
	m_strOldPId = m_strPId;
	m_strPPhone = setPatient.m_patientPhone;
	m_strPPhone.TrimRight();
	m_strPAddr = setPatient.m_patientAddress;
	m_strPAddr.TrimRight();
	m_strPAllergy = setPatient.m_patientAllergy;
	m_strPAllergy.TrimRight();
	m_strPRemark = setPatient.m_patientRemark;
	m_strPRemark.TrimRight();

	setPatient.Close();
	
	UpdateData(FALSE);
}

//---------------
//---���ܣ�����SQL��������г�������Ϣ---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-27---
//---�޸�ʱ�䣺---
//---------------
void CDlgPatientInfo::ListDiagInfo(CString strSQL)
{
	CRecordsetDiag setDiag;

	setDiag.m_strFilter = strSQL;

	if (!setDiag.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
	
	if (setDiag.IsEOF()) {
		setDiag.Close();
		return;
	}
	CString strTmp;
	strTmp.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
		setDiag.m_diagNum.GetYear(), setDiag.m_diagNum.GetMonth(), setDiag.m_diagNum.GetDay(),
		setDiag.m_diagNum.GetHour(), setDiag.m_diagNum.GetMinute(), setDiag.m_diagNum.GetSecond());
	m_comboDTime.SetWindowText(strTmp);
	
	m_strOldDNum = strTmp;	// ����ʱ�䣬��ʱ��Ϊ������

	m_strDDId = setDiag.m_diagDoctorID;
	m_strDDId.TrimRight();
	strTmp.Format(_T("%04d%02d%02d%02d%02d%02d"),
		setDiag.m_diagNum.GetYear(), setDiag.m_diagNum.GetMonth(), setDiag.m_diagNum.GetDay(),
		setDiag.m_diagNum.GetHour(), setDiag.m_diagNum.GetMinute(), setDiag.m_diagNum.GetSecond());
	m_strDNum = strTmp;		// ������ʾ�ľ�����
	
	m_strDDeclare = setDiag.m_diagDeclare;
	m_strDDeclare.TrimRight();	// ���߳���
	m_strDInitCheck = setDiag.m_diagInitCheck;
	m_strDInitCheck.TrimRight();
	m_strDInstruCheck = setDiag.m_diagInstruCheck;
	m_strDInstruCheck.TrimRight();
	m_strDResult = setDiag.m_diagResult;
	m_strDResult.TrimRight();
	m_strDScheme = setDiag.m_diagScheme;
	m_strDScheme.TrimRight();
	m_strDRemark = setDiag.m_diagRemark;
	m_strDRemark.TrimRight();
	
	UpdateData(FALSE);
	setDiag.Close();
}

//---------------
//---���ܣ�����SQL��������г����߷�����Ϣ�Լ��ָ����---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-27---
//---�޸�ʱ�䣺---
//---------------
void CDlgPatientInfo::ListFeeInfo(CString strSQL)
{
	CRecordsetFee setFee;

	setFee.m_strFilter = strSQL;

	if (!setFee.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	if (setFee.IsEOF()) {
		setFee.Close();
		return;
	}

	m_floatFDrug = setFee.m_feeDrug;
	m_floatFDiag = setFee.m_feeDiag;
	m_floatFTrans = setFee.m_feeTransfusion;
	m_floatFCheck = setFee.m_feeCheck;
	m_floatFConsum = setFee.m_feeConsumable;
	m_floatFRadiate = setFee.m_feeRadiate;
	m_floatTotalFee = setFee.m_feeTotal;
	m_strFeedBack = setFee.m_feedback;
	m_strFeedBack.TrimRight();

	setFee.Close();

	UpdateData(FALSE);
}


//---------------
//---���ܣ����û��߾�����Ϣ�Ƿ�Ϊֻ��״̬---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-27---
//---�޸�ʱ�䣺---
//---------------
void CDlgPatientInfo::SetReadOnly(BOOL bReadOnly)
{
	m_ctrlPName.SetReadOnly(bReadOnly);
	m_ctrlPSex.SetReadOnly(bReadOnly);
	m_ctrlPNum.SetReadOnly(bReadOnly);
	m_ctrlPId.SetReadOnly(bReadOnly);
	m_ctrlPAge.SetReadOnly(bReadOnly);
	m_ctrlPPhone.SetReadOnly(bReadOnly);
	m_ctrlPAddr.SetReadOnly(bReadOnly);
	m_ctrlPAllergy.SetReadOnly(bReadOnly);
	m_ctrlPRemark.SetReadOnly(bReadOnly);
	m_ctrlDDId.SetReadOnly(bReadOnly);
	m_ctrlDDeclare.SetReadOnly(bReadOnly);
	m_ctrlDInitCheck.SetReadOnly(bReadOnly);
	m_ctrlDInstruCheck.SetReadOnly(bReadOnly);
	m_ctrlDResult.SetReadOnly(bReadOnly);
	m_ctrlDScheme.SetReadOnly(bReadOnly);
	m_ctrlDRemark.SetReadOnly(bReadOnly);
	m_ctrlFDrug.SetReadOnly(bReadOnly);
	m_ctrlFDiag.SetReadOnly(bReadOnly);
	m_ctrlFTrans.SetReadOnly(bReadOnly);
	m_ctrlFCheck.SetReadOnly(bReadOnly);
	m_ctrlFConsum.SetReadOnly(bReadOnly);
	m_ctrlFRadiate.SetReadOnly(bReadOnly);
	m_ctrlTotalFee.SetReadOnly(bReadOnly);
	m_ctrlFeedBack.SetReadOnly(bReadOnly);
	
}