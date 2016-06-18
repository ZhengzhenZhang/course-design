// BackRecoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Begin.h"
#include "BackRecoDlg.h"


// CBackRecoDlg 对话框

IMPLEMENT_DYNAMIC(CBackRecoDlg, CDialog)

CBackRecoDlg::CBackRecoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBackRecoDlg::IDD, pParent)
	, sPath(_T(""))
	, m_edit(_T(""))
{
	
}

CBackRecoDlg::~CBackRecoDlg()
{
}

void CBackRecoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDE_BACKUP, m_edit);
}


BEGIN_MESSAGE_MAP(CBackRecoDlg, CDialog)
	ON_BN_CLICKED(IDB_BACKUP, &CBackRecoDlg::OnBnClickedBackup)
END_MESSAGE_MAP()


// CBackRecoDlg 消息处理程序

void CBackRecoDlg::OnBnClickedBackup()
{
	// TODO: 在此添加控件通知处理程序代码
	CDatabase db;
	
	if(!db.Open(_T( "医药进销存数据库"))) 
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

	CString tcs;
	tcs.Format(_T("备份到%s"), sPath);
	if (MessageBox(tcs, _T("提示"), MB_OKCANCEL) != IDOK)
		return;

	CString strSQL; 
	strSQL = _T("backup database 医药进销存数据库 to disk = '");
	strSQL += sPath;
	strSQL += _T("'");
	
	db.ExecuteSQL(strSQL); 
	db.Close(); 
	MessageBox(_T("备份成功！"), _T("提示"), MB_OK);
}


BOOL CBackRecoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	sPath.ReleaseBuffer();   
	int nPos;   
	nPos = sPath.ReverseFind('\\');   
	sPath = sPath.Left(nPos);   //获取执行程序目录
	sPath += _T("\\Backup\\医药进销存数据库.bak"); //获取备份文件夹位置和备份文件存放路径

	m_edit.Format(_T("备份到%s"), sPath);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
