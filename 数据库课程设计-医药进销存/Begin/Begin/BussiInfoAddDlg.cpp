// BussiInfoAddDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Begin.h"
#include "BussiInfoAddDlg.h"
#include "BussiInfoSet.h"


// CBussiInfoAddDlg 对话框

IMPLEMENT_DYNAMIC(CBussiInfoAddDlg, CDialog)

CBussiInfoAddDlg::CBussiInfoAddDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBussiInfoAddDlg::IDD, pParent)
	, m_bcode(_T(""))
	, m_phone(_T(""))
	, m_name(_T(""))
	, m_addr(_T(""))
	, m_remark(_T(""))
	, m_csOp(_T(""))
	, m_tmpCode(_T(""))
	, m_ifAdd(TRUE)
{

}

CBussiInfoAddDlg::~CBussiInfoAddDlg()
{
}

void CBussiInfoAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDE_BUSSI_CODE, m_bcode);
	DDX_Text(pDX, IDE_BUSSI_PHONE, m_phone);
	DDX_Text(pDX, IDE_BUSSI_NAME, m_name);
	DDX_Text(pDX, IDE_BUSSI_ADDRESS, m_addr);
	DDX_Text(pDX, IDE_BUSSI_REMARK, m_remark);
}


BEGIN_MESSAGE_MAP(CBussiInfoAddDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CBussiInfoAddDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CBussiInfoAddDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (!m_ifAdd)
	{
		CBussiInfoSet setDtl;
		setDtl.m_strFilter = m_csOp;
		if (!setDtl.Open())
			MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

		setDtl.m_code.TrimRight();
		m_bcode = setDtl.m_code;
		m_tmpCode = m_bcode;

		setDtl.m_name.TrimRight();
		m_name = setDtl.m_name;

		setDtl.m_address.TrimRight();
		m_addr = setDtl.m_address;

		setDtl.m_phone.TrimRight();
		m_phone = setDtl.m_phone;

		setDtl.m_remark.TrimRight();
		m_remark = setDtl.m_remark;

		setDtl.Close();
		UpdateData(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// CBussiInfoAddDlg 消息处理程序

void CBussiInfoAddDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (_T("") == m_bcode)
	{
		MessageBox(_T("公司编号不能为空"), _T("提示"), MB_OK);
		GetDlgItem(IDE_BUSSI_CODE)->SetFocus();
		SendDlgItemMessage(IDE_BUSSI_CODE, EM_SETSEL, 0, -1);
		return;
	}
	if (m_ifAdd)
	{
		AddBussiInfo();
	}
	else 
	{
		if (IDOK != MessageBox(_T("确认修改？"), 
			_T("提示"), MB_OKCANCEL))
		{
			return;
		}
		ModifyBussiInfo();
	}
}

void CBussiInfoAddDlg::AddBussiInfo()
{
	CDatabase db;
	if (!db.Open(_T("医药进销存数据库")))
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

	CString cs;
	cs.Format(_T("insert into 供货商信息 values('%s', '%s', '%s', '%s', '%s')"),
		m_bcode, m_name, m_addr, m_phone, m_remark);
	db.ExecuteSQL(cs);
	db.Close();
	OnOK();
}

void CBussiInfoAddDlg::ModifyBussiInfo()
{
	CDatabase db;
	if (!db.Open(_T("医药进销存数据库")))
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

	CString cs;
	cs.Format(_T("delete from 供货商信息 where code = '%s'"), 
		m_tmpCode);
	db.ExecuteSQL(cs);

	cs.Format(_T("insert into 供货商信息 values('%s', '%s', '%s', '%s', '%s')"),
		m_bcode, m_name, m_addr, m_phone, m_remark);
	db.ExecuteSQL(cs);
	db.Close();
	OnOK();
}

