// DlgPatientInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "RegisterClient.h"
#include "DlgPatientInfo.h"


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

{

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

	DDX_Text(pDX, IDC_EDIT_DDID, m_strDDId);
	DDX_Text(pDX, IDC_EDIT_DNUM, m_strDNum);
	

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
	
}


BEGIN_MESSAGE_MAP(CDlgPatientInfo, CDialog)
END_MESSAGE_MAP()


// CDlgPatientInfo 消息处理程序
