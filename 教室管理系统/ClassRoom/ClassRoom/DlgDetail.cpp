// DlgDetail.cpp : 实现文件
//

#include "stdafx.h"
#include "ClassRoom.h"
#include "DlgDetail.h"
#include "RecordsetCS.h"
#include "RecordsetTBCInfo.h"
#include "RecordsetOC.h"


// CDlgDetail 对话框

IMPLEMENT_DYNAMIC(CDlgDetail, CDialog)

CDlgDetail::CDlgDetail(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDetail::IDD, pParent)
	, m_strDTime(_T("1989-07-15  星期一"))
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

	// TODO:  在此添加额外的初始化
	
	// 初始化教室信息对话框时将数据库信息列出
	ListClassInfo();
	ListCRoomInfo();
	ListOCInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


// CDlgDetail 消息处理程序
//---------------
//---功能：列出教室占用信息---
//---完成人：吴稀钰---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
void CDlgDetail::ListClassInfo()
{
	CRecordsetCS setCS;
	
	CString strSQL;
	strSQL.Format(_T("csWeek = '%d' AND cRoomNum = '%s'"), 
			m_nWeek, m_strDCNum);
	setCS.m_strFilter = strSQL;

	if (!setCS.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

	if (setCS.IsEOF()) {
		setCS.Close();
		return;
	}
	
	m_strDClass1 = setCS.m_csFirst;
	m_strDClass1.TrimRight();	// 去掉右边的空格
	if (m_strDClass1 != _T(""))
		m_editDClass1.SetReadOnly();

	m_strDClass2 = setCS.m_csSecond;
	m_strDClass2.TrimRight();	// 去掉右边的空格
	if (m_strDClass2 != _T(""))
		m_editDClass2.SetReadOnly();

	m_strDClass3 = setCS.m_csThird;
	m_strDClass3.TrimRight();	// 去掉右边的空格
	if (m_strDClass3 != _T(""))
		m_editDClass3.SetReadOnly();

	m_strDClass4 = setCS.m_csFourth;
	m_strDClass4.TrimRight();	// 去掉右边的空格
	if (m_strDClass4 != _T(""))
		m_editDClass4.SetReadOnly();

	m_strDClass5 = setCS.m_csFifth;
	m_strDClass5.TrimRight();	// 去掉右边的空格
	if (m_strDClass5 != _T(""))
		m_editDClass5.SetReadOnly();
	
	UpdateData(FALSE);
	setCS.Close();
}

//---------------
//---功能：列出教室基本信息---
//---完成人：吴稀钰---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
void CDlgDetail::ListCRoomInfo()
{
	CRecordsetTBCInfo setTBCinfo;

	CString strSQL;
	strSQL.Format(_T("cRoomNum = '%s'"), m_strDCNum);
	setTBCinfo.m_strFilter = strSQL;

	if (!setTBCinfo.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

	if (setTBCinfo.IsEOF()) {
		setTBCinfo.Close();
		return;
	}
	
	m_strDTBNum = setTBCinfo.m_tBuildNum;
	m_strDTBNum.TrimRight();	// 去掉右边的空格
	m_oldDTBNum = m_strDTBNum;	// 记录原先的教学楼编号
	m_strDTBNum += _T("教学楼");

	m_strDCNum = setTBCinfo.m_cRoomNum;
	m_strDCNum.TrimRight();		// 去掉右边的空格
	m_oldDCNum = m_strDCNum;	// 记录原先教室编号

	m_strDManager = setTBCinfo.m_tBuildManager;
	m_strDManager.TrimRight();	// 去掉右边的空格

	m_strPhone = setTBCinfo.m_tBuildPhone;
	m_strPhone.TrimRight();	// 去掉右边的空格

	m_checkDisPro = setTBCinfo.m_cRoomIsProjector;
	m_checkIsDam = setTBCinfo.m_cRoomIsDamage;
	m_intDVolume = setTBCinfo.m_cRoomVolume;

	m_strDAddr = setTBCinfo.m_tBuildAddress;
	m_strDAddr.TrimRight();	// 去掉右边的空格

	m_strRemark = setTBCinfo.m_cRoomRemark;
	m_strRemark.TrimRight();	// 去掉右边的空格

	UpdateData(FALSE);
	setTBCinfo.Close();
}

//---------------
//---功能：列出教室占用信息---
//---完成人：吴稀钰---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
void CDlgDetail::ListOCInfo()
{
	CRecordsetOC setOC;

	CString strSQL;
	strSQL.Format(_T("ocTime = '%s' AND cRoomNum = '%s'"), 
		m_strDTime, m_strDCNum);

	setOC.m_strFilter = strSQL;

	if (!setOC.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

	if (setOC.IsEOF()) {
		setOC.Close();
		return;
	}

	if (_T("") == m_strDClass1)
	{
		m_strDClass1 = setOC.m_ocFirst;
		m_strDClass1.TrimRight();	// 去掉右边的空格
	}
	if (_T("") == m_strDClass2)
	{
		m_strDClass2 = setOC.m_ocSecond;
		m_strDClass2.TrimRight();	// 去掉右边的空格
	}
	if (_T("") == m_strDClass3)
	{
		m_strDClass3 = setOC.m_ocThird;
		m_strDClass3.TrimRight();	// 去掉右边的空格
	}
	if (_T("") == m_strDClass4)
	{
		m_strDClass4 = setOC.m_ocFourth;
		m_strDClass4.TrimRight();	// 去掉右边的空格
	}
	if (_T("") == m_strDClass5)
	{
		m_strDClass5 = setOC.m_ocFifth;
		m_strDClass5.TrimRight();	// 去掉右边的空格
	}
	if (_T("") == m_strDOther)
	{
		m_strDOther = setOC.m_ocOther;
		m_strDOther.TrimRight();	// 去掉右边的空格
	}
	UpdateData(FALSE);
	setOC.Close();
}

//---------------
//---功能：对教室信息进行修改---
//---完成人：吴稀钰---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
BOOL CDlgDetail::ModifyCRData()
{
	UpdateData(TRUE);
	CDatabase db;
	if (!db.Open(_T("教室信息管理系统")))
	{
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
		return FALSE;
	}
	CString strSQL;

	// 先删除教室信息
	strSQL.Format(_T("DELETE FROM 教室信息表 WHERE cRoomNum = '%s'"), m_oldDCNum);
	db.ExecuteSQL(strSQL);
	// 然后插入新的教室信息
	strSQL.Format(_T("INSERT INTO 教室信息表 VALUES ")
		_T("('%s','%s','%d','%d','%d','%s')"),
		m_strDCNum, m_oldDTBNum, m_intDVolume, m_checkDisPro, m_checkIsDam,
		m_strRemark);
	db.ExecuteSQL(strSQL);

	// 先删除教学楼信息
	strSQL.Format(_T("DELETE FROM 教学楼信息表 WHERE tBuildNum = '%s'"), m_oldDTBNum);
	db.ExecuteSQL(strSQL);
	// 然后插入新的教室信息
	strSQL.Format(_T("INSERT INTO 教学楼信息表 VALUES ")
		_T("('%s','%s','%s','%s','无')"),
		m_oldDTBNum, m_strDManager, m_strPhone, m_strDAddr);
	db.ExecuteSQL(strSQL);

	// 先删除教室占用信息
	strSQL.Format(_T("DELETE FROM 教室占用信息表 WHERE ocTime = '%s' AND cRoomNum = '%s'"), 
			m_strDTime, m_oldDCNum);
	db.ExecuteSQL(strSQL);
	// 然后插入新的教室占用信息
	strSQL.Format(_T("INSERT INTO 教室占用信息表 VALUES ")
		_T("('%s', '%s', '%s', '%s','%s', '%s', '%s','%s')"),
		m_strDTime, m_oldDCNum, m_strDClass1, m_strDClass2, 
		m_strDClass3, m_strDClass4, m_strDClass5, m_strDOther);
	db.ExecuteSQL(strSQL);

	return TRUE;
}

//---------------
//---功能：对教室信息和占用信息进行修改---
//---完成人：吴稀钰---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
void CDlgDetail::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	if (IDOK == MessageBox(_T("确认修改？"), _T("提示"), MB_OKCANCEL))
	{
		// 下面执行数据库修改操作
		if (ModifyCRData())
		{
			MessageBox(_T("修改成功"), _T("提示"), MB_OK);

		}
		else
		{
			MessageBox(_T("修改失败"), _T("提示"), MB_OK);
		}
		OnOK();
	}
}

void CDlgDetail::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	
	OnCancel();
}
