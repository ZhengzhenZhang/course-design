// DlgConfigPort.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CenterServer.h"
#include "DlgConfigPort.h"


// CDlgConfigPort �Ի���

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


// CDlgConfigPort ��Ϣ�������


BOOL CDlgConfigPort::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString strIp, str;
	GetHostIp(strIp);
	// �õ�����IP�󸳸���̬�ı��ؼ�
	str.Format(_T("�����IPΪ��%s"), strIp);
	GetDlgItem(IDC_STATIC_HOSTIP)->SetWindowText(str);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//---------------
//---���ܣ��õ�����IP������strIp����
//---����ˣ�
//---���ʱ�䣺
//---�޸�ʱ�䣺
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (IDOK != MessageBox(_T("ȷ���޸ģ�"), _T("��ʾ"), MB_OKCANCEL))
	{
		return;
	}
	OnOK();
}
