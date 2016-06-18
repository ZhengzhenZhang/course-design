// DlgConfigPort.cpp : 实现文件
//

#include "stdafx.h"
#include "CenterServer.h"
#include "DlgConfigPort.h"


// CDlgConfigPort 对话框

IMPLEMENT_DYNAMIC(CDlgConfigPort, CDialog)

CDlgConfigPort::CDlgConfigPort(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConfigPort::IDD, pParent)
	, m_uintRegPort(5001)
	, m_uintDocPort(5002)
	, m_uintFeePort(5003)
{

}

CDlgConfigPort::~CDlgConfigPort()
{
}

void CDlgConfigPort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_REGPORT, m_uintRegPort);
	DDX_Text(pDX, IDC_EDIT_DOCPORT, m_uintDocPort);
	DDX_Text(pDX, IDC_EDIT_FEEPORT, m_uintFeePort);
}


BEGIN_MESSAGE_MAP(CDlgConfigPort, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgConfigPort::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgConfigPort 消息处理程序


BOOL CDlgConfigPort::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strIp, str;
	GetHostIp(strIp);
	// 得到主机IP后赋给静态文本控件
	str.Format(_T("服务端IP为：%s"), strIp);
	GetDlgItem(IDC_STATIC_HOSTIP)->SetWindowText(str);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//---------------
//---功能：得到主机IP并赋予strIp变量
//---完成人：
//---完成时间：
//---修改时间：
//---------------
void CDlgConfigPort::GetHostIp(CString &strIp)
{

	WSADATA wsaData; 
	char name[155];
	char *ip;
	PHOSTENT hostinfo; 
	if ( WSAStartup( MAKEWORD(2,0), &wsaData ) == 0 ) 
	{ 
		if( gethostname ( name, sizeof(name)) == 0) 
		{ 
			if((hostinfo = gethostbyname(name)) != NULL) 
			{ 
				ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list); 
				
				strIp = ip;
			} 
		} 
		WSACleanup(); 
	}
}
void CDlgConfigPort::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IDOK != MessageBox(_T("确认修改？"), _T("提示"), MB_OKCANCEL))
	{
		return;
	}
	OnOK();
}
