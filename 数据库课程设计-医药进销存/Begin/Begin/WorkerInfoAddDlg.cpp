// WorkerInfoAddDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Begin.h"
#include "WorkerInfoAddDlg.h"
#include "WorkerInfoSet.h"


// CWorkerInfoAddDlg �Ի���

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (!m_ifAdd)
	{
		CWorkerInfoSet setDtl;
		setDtl.m_strFilter = m_csOp;
		if (!setDtl.Open())
			MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

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
	// �쳣: OCX ����ҳӦ���� FALSE
}


// CWorkerInfoAddDlg ��Ϣ�������

void CWorkerInfoAddDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (_T("") == m_ID)
	{
		MessageBox(_T("���Ų���Ϊ��"), _T("��ʾ"), MB_OK);
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
		if (IDOK != MessageBox(_T("ȷ���޸ģ�"), 
			_T("��ʾ"), MB_OKCANCEL))
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
	if (!db.Open(_T("ҽҩ���������ݿ�")))
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	CString cs;
	cs.Format(_T("insert into ְ����Ϣ values('%s', '%s', '%s', '%s')"),
		m_ID, m_name, m_position, m_phone);
	db.ExecuteSQL(cs);
	db.Close();
	OnOK();
}

void CWorkerInfoAddDlg::ModifyWorkerInfo()
{
	CDatabase db;
	if (!db.Open(_T("ҽҩ���������ݿ�")))
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	CString cs;
	cs.Format(_T("delete from ְ����Ϣ where ID = '%s'"), 
		m_tmpID);
	db.ExecuteSQL(cs);

	cs.Format(_T("insert into ְ����Ϣ values('%s', '%s', '%s', '%s')"),
		m_ID, m_name, m_position, m_phone);
	db.ExecuteSQL(cs);
	db.Close();
	OnOK();
}

