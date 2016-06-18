// DlgPatientInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "CenterServer.h"
#include "DlgPatientInfo.h"
#include "RecordsetPatient.h"
#include "RecordsetDiag.h"
#include "RecordsetFee.h"


// CDlgPatientInfo 对话框

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


// CDlgPatientInfo 消息处理程序

BOOL CDlgPatientInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	InitDialogInfo();	// 首先调用初始化对话框布局函数
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//---------------
//---功能：在就诊信息组合框中选择相应的就诊信息---
//---完成人：张政桢---
//---完成时间：2012-12-26---
//---修改时间：---
//---------------
void CDlgPatientInfo::OnCbnSelendokComboDtime()
{
	// TODO: 在此添加控件通知处理程序代码
	int index;
	index = m_comboDTime.GetCurSel();
	CString strTmp, strSQL;
	m_comboDTime.GetLBText(index, strTmp);
	
	strSQL.Format(_T("diagNum = '%s'"), strTmp);

	ListDiagInfo(strSQL);

	ListFeeInfo(strSQL);
}


//---------------
//---功能：接收SQL条件语句在时间组合框列出所有就诊记录---
//---完成人：张政桢---
//---完成时间：2012-12-26---
//---修改时间：---
//---------------
void CDlgPatientInfo::ListTimeCombox(CString strSQL)
{
	CRecordsetDiag setDiag;

	setDiag.m_strFilter = strSQL;

	if (!setDiag.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

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
//---功能：修改和保存按钮消息响应函数---
//---完成人：张政桢---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
void CDlgPatientInfo::OnBnClickedEditModsave()
{
	// TODO: 在此添加控件通知处理程序代码
	if (0 == m_flagOperate)
	{
		m_flagOperate = 1;
		SetReadOnly(FALSE);			// 设为修改状态
		GetDlgItem(ID_BUTTON_MODSAVE)->SetWindowText(_T("保存"));
		GetDlgItem(ID_BUTTON_OKCANCEL)->SetWindowText(_T("取消"));
	}
	else if (1 == m_flagOperate)
	{
		if (IDOK == MessageBox(_T("确认修改？"), _T("提示"), MB_OKCANCEL))
		{
			// 下面执行数据库修改操作
			if (ModifyDatabase())
			{
				MessageBox(_T("修改成功"), _T("提示"), MB_OK);
				GetDlgItem(ID_BUTTON_MODSAVE)->SetWindowText(_T("修改"));
				GetDlgItem(ID_BUTTON_OKCANCEL)->SetWindowText(_T("确定"));
				m_flagOperate = 0;
				UpdateData(FALSE);
				SetReadOnly(TRUE);		// 设为只读状态
			}
			else
			{
				MessageBox(_T("修改失败"), _T("提示"), MB_OK);
			}
		}
	}
	else if (2 == m_flagOperate || 3 == m_flagOperate)	// 如果为添加
	{
		if (IDOK == MessageBox(_T("确认添加？"), _T("提示"), MB_OKCANCEL))
		{
			// 下面执行数据库修改操作
			if (ModifyDatabase())
			{
				MessageBox(_T("添加成功"), _T("提示"), MB_OK);
				OnOK();
			}
			else
			{
				MessageBox(_T("添加失败"), _T("提示"), MB_OK);
			}
		}
	}
}

//---------------
//---功能：确定和取消按钮消息响应函数---
//---完成人：张政桢---
//---完成时间：2012-12-27---
//---修改时间：---
//---------------
void CDlgPatientInfo::OnBnClickedButtonOkcancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (0 == m_flagOperate)		
	{
		OnOK();
	}
	else if (1 == m_flagOperate) // 如果为修改
	{
		m_flagOperate = 0;
		UpdateData(FALSE);
		GetDlgItem(ID_BUTTON_MODSAVE)->SetWindowText(_T("修改"));
		GetDlgItem(ID_BUTTON_OKCANCEL)->SetWindowText(_T("确定"));

		SetReadOnly(TRUE);	// 设为只读状态
	}
	else if (2 == m_flagOperate || 3 == m_flagOperate) // 如果为添加
	{
		OnOK();
	}

}

//---------------
//---功能：该函数实现对患者就诊信息数据库进行添加修改---
//---完成人：张政桢---
//---完成时间：2012-12-27---
//---修改时间：---
//---------------
BOOL CDlgPatientInfo::ModifyDatabase()
{
	// 因为要更新所以需要保存原先主键值

	UpdateData(TRUE);
	CDatabase db;
	if (!db.Open(_T("患者就诊数据库")))
	{
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
		return FALSE;
	}

	CString strSQL;
	// 更新患者信息（先删除后插入，可避免原先表中无数据）
	if (m_flagOperate = 1)	// 如果为修改的话
	{
		strSQL.Format(_T("DELETE FROM 患者信息 WHERE idNumber = '%s'"), m_strOldPId);
		db.ExecuteSQL(strSQL);
	}
	if (m_flagOperate != 3)	// 如果不是添加就诊信息
	{
		strSQL.Format(_T("INSERT INTO 患者信息 VALUES ")
			_T("('%s','%s','%s','%d','%s','%s','%s','%s','%s')"),
			m_strPId, m_strPName, m_strPSex, m_strPAge, m_strPPhone,
			m_strPAddr, m_strPNum, m_strPAllergy, m_strPRemark);
		db.ExecuteSQL(strSQL);
	}
	// 更新就诊信息
	CString strTmp;
	GetDlgItem(IDC_STATIC_TIME)->GetWindowText(strTmp);

	if (1 == m_flagOperate)
	{
		strSQL.Format(_T("DELETE FROM 就诊信息 WHERE diagNum = '%s'"), m_strOldDNum);
		db.ExecuteSQL(strSQL);
		if ("" != m_strOldDNum)
			strTmp = m_strOldDNum;	// 如果是修改的话，不修改时间
	}
	strSQL.Format(_T("INSERT INTO 就诊信息 VALUES ")
		_T("('%s','%s','%s','%s','%s','%s','%s','%s', '%s', '%s')"),
		strTmp, m_strPId, strTmp, m_strDDId, m_strDDeclare, m_strDInitCheck,
		m_strDInstruCheck, m_strDResult, m_strDScheme,m_strDRemark);
	db.ExecuteSQL(strSQL);

	// 更新费用信息（先计算总价格）
	m_floatTotalFee = m_floatFDrug+m_floatFDiag+m_floatFCheck
		+ m_floatFConsum+m_floatFTrans+m_floatFRadiate;
	if (1 == m_flagOperate)
	{
		strSQL.Format(_T("DELETE FROM 费用信息 WHERE diagNum = '%s'"), m_strOldDNum);
		db.ExecuteSQL(strSQL);
	}
	strSQL.Format(_T("INSERT INTO 费用信息 VALUES ")
		_T("('%s','%f','%f','%f','%f','%f','%f','%f')"),
		strTmp, m_floatFDrug, m_floatFDiag, m_floatFTrans,
		m_floatFCheck, m_floatFConsum, m_floatFRadiate, m_floatTotalFee);
	db.ExecuteSQL(strSQL);

	// 更新反馈信息
	if (1 == m_flagOperate)
	{
		strSQL.Format(_T("DELETE FROM 诊后恢复结果信息 WHERE diagNum = '%s'"), m_strOldDNum);
		db.ExecuteSQL(strSQL);
	}
	strSQL.Format(_T("INSERT INTO 诊后恢复结果信息 VALUES ")
		_T("('%s','%s')"), strTmp, m_strFeedBack);
	db.ExecuteSQL(strSQL);

	db.Close();

	m_ifModify = 1;	// 标记为已修改状态

	return TRUE;
}

//---------------
//---功能：根据m_flagOperate标记的不同初始化对话框---
//---完成人：张政桢---
//---完成时间：2012-12-27---
//---修改时间：---
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
	// 如果为添加
	if (2 == m_flagOperate || 3 == m_flagOperate)	
	{
		GetDlgItem(ID_BUTTON_MODSAVE)->SetWindowText(_T("添加"));
		GetDlgItem(ID_BUTTON_OKCANCEL)->SetWindowText(_T("取消"));

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
		GetDlgItem(ID_BUTTON_MODSAVE)->SetWindowText(_T("保存"));
		GetDlgItem(ID_BUTTON_OKCANCEL)->SetWindowText(_T("取消"));
	}

	if (0 == m_flagOperate)
		SetReadOnly(TRUE);

	// 初始对话框显示患者信息
	// 首先显示患者基本信息
	// 然后列出患者就诊时间记录
	// 最后列出患者就诊信息
	CString strSQL;
	strSQL.Format(_T("idNumber = '%s'"), m_strPId);
	ListPatientInfo(strSQL);
	ListTimeCombox(strSQL);

	strSQL.Format(_T("diagNum = '%s'"), m_strDNum);
	ListFeeInfo(strSQL);
	ListDiagInfo(strSQL);
}










//---------------
//---功能：接收SQL条件语句列出患者信息---
//---完成人：魏强---
//---完成时间：2012-12-26---
//---修改时间：---
//---------------
void CDlgPatientInfo::ListPatientInfo(CString strSQL)
{
	CRecordsetPatient setPatient;

	setPatient.m_strFilter = strSQL;

	if (!setPatient.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
	
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
//---功能：接收SQL条件语句列出就诊信息---
//---完成人：魏强---
//---完成时间：2012-12-27---
//---修改时间：---
//---------------
void CDlgPatientInfo::ListDiagInfo(CString strSQL)
{
	CRecordsetDiag setDiag;

	setDiag.m_strFilter = strSQL;

	if (!setDiag.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
	
	if (setDiag.IsEOF()) {
		setDiag.Close();
		return;
	}
	CString strTmp;
	strTmp.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
		setDiag.m_diagNum.GetYear(), setDiag.m_diagNum.GetMonth(), setDiag.m_diagNum.GetDay(),
		setDiag.m_diagNum.GetHour(), setDiag.m_diagNum.GetMinute(), setDiag.m_diagNum.GetSecond());
	m_comboDTime.SetWindowText(strTmp);
	
	m_strOldDNum = strTmp;	// 保存时间，该时间为就诊编号

	m_strDDId = setDiag.m_diagDoctorID;
	m_strDDId.TrimRight();
	strTmp.Format(_T("%04d%02d%02d%02d%02d%02d"),
		setDiag.m_diagNum.GetYear(), setDiag.m_diagNum.GetMonth(), setDiag.m_diagNum.GetDay(),
		setDiag.m_diagNum.GetHour(), setDiag.m_diagNum.GetMinute(), setDiag.m_diagNum.GetSecond());
	m_strDNum = strTmp;		// 用于显示的就诊编号
	
	m_strDDeclare = setDiag.m_diagDeclare;
	m_strDDeclare.TrimRight();	// 患者陈述
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
//---功能：接收SQL条件语句列出患者费用信息以及恢复情况---
//---完成人：魏强---
//---完成时间：2012-12-27---
//---修改时间：---
//---------------
void CDlgPatientInfo::ListFeeInfo(CString strSQL)
{
	CRecordsetFee setFee;

	setFee.m_strFilter = strSQL;

	if (!setFee.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

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
//---功能：设置患者就诊信息是否为只读状态---
//---完成人：魏强---
//---完成时间：2012-12-27---
//---修改时间：---
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