// WorkerInfoAddDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Begin.h"
#include "WorkerInfoAddDlg.h"
#include "WorkerInfoSet.h"


// CWorkerInfoAddDlg 对话框

IMPLEMENT_DYNAMIC(CWorkerInfoAddDlg, CDialog)

CWorkerInfoAddDlg::CWorkerInfoAddDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkerInfoAddDlg::IDD, pParent)
	, m_ID(_T(""))
	, m_name(_T(""))
	, m_position(_T(""))
	, m_phone(_T(""))
	, m_ifAdd(TRUE)
	, m_tmpID(_T(""))
	, m_csOp(_T(""))
{

}

CWorkerInfoAddDlg::~CWorkerInfoAddDlg()
{
}

void CWorkerInfoAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDE_WORKER_ID, m_ID);
	DDX_Text(pDX, IDE_WORKER_NAME, m_name);
	DDX_Text(pDX, IDE_WORKER_POS, m_position);
	DDX_Text(pDX, IDE_WORKER_PHONE, m_phone);
}


BEGIN_MESSAGE_MAP(CWorkerInfoAddDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CWorkerInfoAddDlg::OnBnClickedOk)
END_MESSAGE_MAP()


BOOL CWorkerInfoAddDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (!m_ifAdd)
	{
		CWorkerInfoSet setDtl;
		setDtl.m_strFilter = m_csOp;
		if (!setDtl.Open())
			MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

		setDtl.m_ID.TrimRight();
		m_ID = setDtl.m_ID;
		m_tmpID = m_ID;

		setDtl.m_name.TrimRight();
		m_name = setDtl.m_name;

		setDtl.m_position.TrimRight();
		m_position = setDtl.m_position;

		setDtl.m_phone.TrimRight();
		m_phone = setDtl.m_phone;

		setDtl.Close();
		UpdateData(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


// CWorkerInfoAddDlg 消息处理程序

void CWorkerInfoAddDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (_T("") == m_ID)
	{
		MessageBox(_T("工号不能为空"), _T("提示"), MB_OK);
		GetDlgItem(IDE_WORKER_ID)->SetFocus();
		SendDlgItemMessage(IDE_WORKER_ID, EM_SETSEL, 0, -1);
		return;
	}
	if (m_ifAdd)
	{
		AddWorkerInfo();
	}
	else 
	{
		if (IDOK != MessageBox(_T("确认修改？"), 
			_T("提示"), MB_OKCANCEL))
		{
			return;
		}
		ModifyWorkerInfo();
	}
	OnOK();
}

void CWorkerInfoAddDlg::AddWorkerInfo()
{
	CDatabase db;
	if (!db.Open(_T("医药进销存数据库")))
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

	CString cs;
	cs.Format(_T("insert into 职工信息 values('%s', '%s', '%s', '%s')"),
		m_ID, m_name, m_position, m_phone);
	db.ExecuteSQL(cs);
	db.Close();
	OnOK();
}

void CWorkerInfoAddDlg::ModifyWorkerInfo()
{
	CDatabase db;
	if (!db.Open(_T("医药进销存数据库")))
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

	CString cs;
	cs.Format(_T("delete from 职工信息 where ID = '%s'"), 
		m_tmpID);
	db.ExecuteSQL(cs);

	cs.Format(_T("insert into 职工信息 values('%s', '%s', '%s', '%s')"),
		m_ID, m_name, m_position, m_phone);
	db.ExecuteSQL(cs);
	db.Close();
	OnOK();
}

