// BackRecoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Begin.h"
#include "BackRecoDlg.h"


// CBackRecoDlg �Ի���

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


// CBackRecoDlg ��Ϣ�������

void CBackRecoDlg::OnBnClickedBackup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDatabase db;
	
	if(!db.Open(_T( "ҽҩ���������ݿ�"))) 
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	CString tcs;
	tcs.Format(_T("���ݵ�%s"), sPath);
	if (MessageBox(tcs, _T("��ʾ"), MB_OKCANCEL) != IDOK)
		return;

	CString strSQL; 
	strSQL = _T("backup database ҽҩ���������ݿ� to disk = '");
	strSQL += sPath;
	strSQL += _T("'");
	
	db.ExecuteSQL(strSQL); 
	db.Close(); 
	MessageBox(_T("���ݳɹ���"), _T("��ʾ"), MB_OK);
}


BOOL CBackRecoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	sPath.ReleaseBuffer();   
	int nPos;   
	nPos = sPath.ReverseFind('\\');   
	sPath = sPath.Left(nPos);   //��ȡִ�г���Ŀ¼
	sPath += _T("\\Backup\\ҽҩ���������ݿ�.bak"); //��ȡ�����ļ���λ�úͱ����ļ����·��

	m_edit.Format(_T("���ݵ�%s"), sPath);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
