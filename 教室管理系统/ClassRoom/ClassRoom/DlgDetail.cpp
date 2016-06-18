// DlgDetail.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ClassRoom.h"
#include "DlgDetail.h"
#include "RecordsetCS.h"
#include "RecordsetTBCInfo.h"
#include "RecordsetOC.h"


// CDlgDetail �Ի���

IMPLEMENT_DYNAMIC(CDlgDetail, CDialog)

CDlgDetail::CDlgDetail(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDetail::IDD, pParent)
	, m_strDTime(_T("1989-07-15  ����һ"))
	, m_strDClass1(_T(""))
	, m_strDClass2(_T(""))
	, m_strDClass3(_T(""))
	, m_strDClass4(_T(""))
	, m_strDClass5(_T(""))
	, m_strDOther(_T(""))
	, m_strDCNum(_T(""))
	, m_strDTBNum(_T(""))
	, m_strDManager(_T(""))
	, m_strPhone(_T(""))
	, m_checkDisPro(FALSE)
	, m_checkIsDam(FALSE)
	, m_strDAddr(_T(""))
	, m_strRemark(_T(""))
	, m_intDVolume(0)
{
	m_nWeek = 0;
	m_oldDTBNum = _T("");
	m_oldDCNum = _T("");
}

CDlgDetail::~CDlgDetail()
{
}

void CDlgDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_DTIME, m_strDTime);
	DDX_Text(pDX, IDC_EDIT_DCLASS1, m_strDClass1);
	DDX_Text(pDX, IDC_EDIT_DCLASS2, m_strDClass2);
	DDX_Text(pDX, IDC_EDIT_DCLASS3, m_strDClass3);
	DDX_Text(pDX, IDC_EDIT_DCLASS4, m_strDClass4);
	DDX_Text(pDX, IDC_EDIT_DCLASS5, m_strDClass5);
	DDX_Text(pDX, IDC_EDIT_DOTHER, m_strDOther);
	DDX_Text(pDX, IDC_EDIT_DCNUM, m_strDCNum);
	DDX_Text(pDX, IDC_STATIC_DTBNUM, m_strDTBNum);
	DDX_Text(pDX, IDC_EDIT_DMANAGER, m_strDManager);
	DDX_Text(pDX, IDC_EDIT_DPHONE, m_strPhone);
	DDX_Check(pDX, IDC_CHECK_DISPRO, m_checkDisPro);
	DDX_Check(pDX, IDC_CHECK_ISDAM, m_checkIsDam);
	DDX_Text(pDX, IDC_EDIT_DADDR, m_strDAddr);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_strRemark);
	DDX_Text(pDX, IDC_EDIT_DVOLUME, m_intDVolume);
	DDX_Control(pDX, IDC_EDIT_DCLASS1, m_editDClass1);
	DDX_Control(pDX, IDC_EDIT_DCLASS2, m_editDClass2);
	DDX_Control(pDX, IDC_EDIT_DCLASS3, m_editDClass3);
	DDX_Control(pDX, IDC_EDIT_DCLASS4, m_editDClass4);
	DDX_Control(pDX, IDC_EDIT_DCLASS5, m_editDClass5);
}


BEGIN_MESSAGE_MAP(CDlgDetail, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgDetail::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgDetail::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CDlgDetail::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	// ��ʼ��������Ϣ�Ի���ʱ�����ݿ���Ϣ�г�
	ListClassInfo();
	ListCRoomInfo();
	ListOCInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


// CDlgDetail ��Ϣ�������
//---------------
//---���ܣ��г�����ռ����Ϣ---
//---����ˣ���ϡ��---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
void CDlgDetail::ListClassInfo()
{
	CRecordsetCS setCS;
	
	CString strSQL;
	strSQL.Format(_T("csWeek = '%d' AND cRoomNum = '%s'"), 
			m_nWeek, m_strDCNum);
	setCS.m_strFilter = strSQL;

	if (!setCS.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	if (setCS.IsEOF()) {
		setCS.Close();
		return;
	}
	
	m_strDClass1 = setCS.m_csFirst;
	m_strDClass1.TrimRight();	// ȥ���ұߵĿո�
	if (m_strDClass1 != _T(""))
		m_editDClass1.SetReadOnly();

	m_strDClass2 = setCS.m_csSecond;
	m_strDClass2.TrimRight();	// ȥ���ұߵĿո�
	if (m_strDClass2 != _T(""))
		m_editDClass2.SetReadOnly();

	m_strDClass3 = setCS.m_csThird;
	m_strDClass3.TrimRight();	// ȥ���ұߵĿո�
	if (m_strDClass3 != _T(""))
		m_editDClass3.SetReadOnly();

	m_strDClass4 = setCS.m_csFourth;
	m_strDClass4.TrimRight();	// ȥ���ұߵĿո�
	if (m_strDClass4 != _T(""))
		m_editDClass4.SetReadOnly();

	m_strDClass5 = setCS.m_csFifth;
	m_strDClass5.TrimRight();	// ȥ���ұߵĿո�
	if (m_strDClass5 != _T(""))
		m_editDClass5.SetReadOnly();
	
	UpdateData(FALSE);
	setCS.Close();
}

//---------------
//---���ܣ��г����һ�����Ϣ---
//---����ˣ���ϡ��---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
void CDlgDetail::ListCRoomInfo()
{
	CRecordsetTBCInfo setTBCinfo;

	CString strSQL;
	strSQL.Format(_T("cRoomNum = '%s'"), m_strDCNum);
	setTBCinfo.m_strFilter = strSQL;

	if (!setTBCinfo.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	if (setTBCinfo.IsEOF()) {
		setTBCinfo.Close();
		return;
	}
	
	m_strDTBNum = setTBCinfo.m_tBuildNum;
	m_strDTBNum.TrimRight();	// ȥ���ұߵĿո�
	m_oldDTBNum = m_strDTBNum;	// ��¼ԭ�ȵĽ�ѧ¥���
	m_strDTBNum += _T("��ѧ¥");

	m_strDCNum = setTBCinfo.m_cRoomNum;
	m_strDCNum.TrimRight();		// ȥ���ұߵĿո�
	m_oldDCNum = m_strDCNum;	// ��¼ԭ�Ƚ��ұ��

	m_strDManager = setTBCinfo.m_tBuildManager;
	m_strDManager.TrimRight();	// ȥ���ұߵĿո�

	m_strPhone = setTBCinfo.m_tBuildPhone;
	m_strPhone.TrimRight();	// ȥ���ұߵĿո�

	m_checkDisPro = setTBCinfo.m_cRoomIsProjector;
	m_checkIsDam = setTBCinfo.m_cRoomIsDamage;
	m_intDVolume = setTBCinfo.m_cRoomVolume;

	m_strDAddr = setTBCinfo.m_tBuildAddress;
	m_strDAddr.TrimRight();	// ȥ���ұߵĿո�

	m_strRemark = setTBCinfo.m_cRoomRemark;
	m_strRemark.TrimRight();	// ȥ���ұߵĿո�

	UpdateData(FALSE);
	setTBCinfo.Close();
}

//---------------
//---���ܣ��г�����ռ����Ϣ---
//---����ˣ���ϡ��---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
void CDlgDetail::ListOCInfo()
{
	CRecordsetOC setOC;

	CString strSQL;
	strSQL.Format(_T("ocTime = '%s' AND cRoomNum = '%s'"), 
		m_strDTime, m_strDCNum);

	setOC.m_strFilter = strSQL;

	if (!setOC.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	if (setOC.IsEOF()) {
		setOC.Close();
		return;
	}

	if (_T("") == m_strDClass1)
	{
		m_strDClass1 = setOC.m_ocFirst;
		m_strDClass1.TrimRight();	// ȥ���ұߵĿո�
	}
	if (_T("") == m_strDClass2)
	{
		m_strDClass2 = setOC.m_ocSecond;
		m_strDClass2.TrimRight();	// ȥ���ұߵĿո�
	}
	if (_T("") == m_strDClass3)
	{
		m_strDClass3 = setOC.m_ocThird;
		m_strDClass3.TrimRight();	// ȥ���ұߵĿո�
	}
	if (_T("") == m_strDClass4)
	{
		m_strDClass4 = setOC.m_ocFourth;
		m_strDClass4.TrimRight();	// ȥ���ұߵĿո�
	}
	if (_T("") == m_strDClass5)
	{
		m_strDClass5 = setOC.m_ocFifth;
		m_strDClass5.TrimRight();	// ȥ���ұߵĿո�
	}
	if (_T("") == m_strDOther)
	{
		m_strDOther = setOC.m_ocOther;
		m_strDOther.TrimRight();	// ȥ���ұߵĿո�
	}
	UpdateData(FALSE);
	setOC.Close();
}

//---------------
//---���ܣ��Խ�����Ϣ�����޸�---
//---����ˣ���ϡ��---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
BOOL CDlgDetail::ModifyCRData()
{
	UpdateData(TRUE);
	CDatabase db;
	if (!db.Open(_T("������Ϣ����ϵͳ")))
	{
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
		return FALSE;
	}
	CString strSQL;

	// ��ɾ��������Ϣ
	strSQL.Format(_T("DELETE FROM ������Ϣ�� WHERE cRoomNum = '%s'"), m_oldDCNum);
	db.ExecuteSQL(strSQL);
	// Ȼ������µĽ�����Ϣ
	strSQL.Format(_T("INSERT INTO ������Ϣ�� VALUES ")
		_T("('%s','%s','%d','%d','%d','%s')"),
		m_strDCNum, m_oldDTBNum, m_intDVolume, m_checkDisPro, m_checkIsDam,
		m_strRemark);
	db.ExecuteSQL(strSQL);

	// ��ɾ����ѧ¥��Ϣ
	strSQL.Format(_T("DELETE FROM ��ѧ¥��Ϣ�� WHERE tBuildNum = '%s'"), m_oldDTBNum);
	db.ExecuteSQL(strSQL);
	// Ȼ������µĽ�����Ϣ
	strSQL.Format(_T("INSERT INTO ��ѧ¥��Ϣ�� VALUES ")
		_T("('%s','%s','%s','%s','��')"),
		m_oldDTBNum, m_strDManager, m_strPhone, m_strDAddr);
	db.ExecuteSQL(strSQL);

	// ��ɾ������ռ����Ϣ
	strSQL.Format(_T("DELETE FROM ����ռ����Ϣ�� WHERE ocTime = '%s' AND cRoomNum = '%s'"), 
			m_strDTime, m_oldDCNum);
	db.ExecuteSQL(strSQL);
	// Ȼ������µĽ���ռ����Ϣ
	strSQL.Format(_T("INSERT INTO ����ռ����Ϣ�� VALUES ")
		_T("('%s', '%s', '%s', '%s','%s', '%s', '%s','%s')"),
		m_strDTime, m_oldDCNum, m_strDClass1, m_strDClass2, 
		m_strDClass3, m_strDClass4, m_strDClass5, m_strDOther);
	db.ExecuteSQL(strSQL);

	return TRUE;
}

//---------------
//---���ܣ��Խ�����Ϣ��ռ����Ϣ�����޸�---
//---����ˣ���ϡ��---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
void CDlgDetail::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (IDOK == MessageBox(_T("ȷ���޸ģ�"), _T("��ʾ"), MB_OKCANCEL))
	{
		// ����ִ�����ݿ��޸Ĳ���
		if (ModifyCRData())
		{
			MessageBox(_T("�޸ĳɹ�"), _T("��ʾ"), MB_OK);

		}
		else
		{
			MessageBox(_T("�޸�ʧ��"), _T("��ʾ"), MB_OK);
		}
		OnOK();
	}
}

void CDlgDetail::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	
	OnCancel();
}
