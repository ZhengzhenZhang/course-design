// WorkerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Begin.h"
#include "WorkerDlg.h"
#include "WorkerInfoSet.h"
#include "WorkerInfoAddDlg.h"


// CWorkerDlg �Ի���

IMPLEMENT_DYNAMIC(CWorkerDlg, CDialog)

CWorkerDlg::CWorkerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkerDlg::IDD, pParent)
{

}

CWorkerDlg::~CWorkerDlg()
{
}

void CWorkerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDL_WORKER_INFO, m_list);
}


BEGIN_MESSAGE_MAP(CWorkerDlg, CDialog)
	ON_BN_CLICKED(IDB_WORKER_ADD, &CWorkerDlg::OnBnClickedWorkerAdd)
	ON_BN_CLICKED(IDB_WORKER_MODIFY, &CWorkerDlg::OnBnClickedWorkerModify)
	ON_BN_CLICKED(IDB_WORKER_DELETE, &CWorkerDlg::OnBnClickedWorkerDelete)
	ON_NOTIFY(NM_DBLCLK, IDL_WORKER_INFO, &CWorkerDlg::OnNMDblclkWorkerInfo)
END_MESSAGE_MAP()


// CWorkerDlg ��Ϣ�������

// ��ʼ���Ի���ʱ��ֱ�Ӱ�ְ�����е����ݶ���list �б�
BOOL CWorkerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list.InsertColumn(0, _T("����"), LVCFMT_CENTER, 55);
	m_list.InsertColumn(1, _T("����"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(2, _T("ְλ"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(3, _T("��ϵ��ʽ"), LVCFMT_CENTER, 120);
	//m_list.SetBkColor(RGB(26, 231, 151));
	//m_list.SetTextBkColor(RGB(26, 231, 151));
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES);

	ListTheInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CWorkerDlg::ListTheInfo()
{
	CWorkerInfoSet setWorker;

	setWorker.m_strFilter.Format(_T(""));
	if (!setWorker.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	m_list.DeleteAllItems();
	if(setWorker.IsEOF())                           
		MessageBox(_T("����ְ����Ϣ"), _T("��ʾ"), MB_OK);
	else
	{
		for(int i=0; !setWorker.IsEOF(); i++,setWorker.MoveNext())
		{
			//setWorker.m_ID.TrimRight();
			m_list.InsertItem(i, setWorker.m_ID);
			setWorker.m_name.TrimRight();
			m_list.SetItemText(i, 1, setWorker.m_name);
			setWorker.m_position.TrimRight();
			m_list.SetItemText(i, 2, setWorker.m_position);
			setWorker.m_phone.TrimRight();
			m_list.SetItemText(i, 3, setWorker.m_phone);
		}
	}
	setWorker.Close();
}

void CWorkerDlg::OnBnClickedWorkerAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWorkerInfoAddDlg dlg;
	if (dlg.DoModal() == IDOK)
		ListTheInfo();
}

void CWorkerDlg::OnBnClickedWorkerModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int n = m_list.GetSelectionMark();
	if (n >= 0){
		CWorkerInfoAddDlg dlg;

		dlg.m_csOp.Format(_T("ID = '%s'"),m_list.GetItemText(n,0));
		dlg.m_ifAdd = FALSE;

		if (dlg.DoModal() == IDOK)
			ListTheInfo();
	}
	else
	{
		MessageBox(_T("��ְ����Ϣ�򵥻�ѡ��ְ�����"), _T("��ʾ"), MB_OK);
	}
}

void CWorkerDlg::OnBnClickedWorkerDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString cs;
	int n = m_list.GetSelectionMark();

	if (n >= 0)
	{
		cs.Format(_T("ȷ��Ҫɾ�� ��%s��"), m_list.GetItemText(n, 1));
		if (IDOK != MessageBox(cs, _T("��ʾ"), MB_OKCANCEL))
		{
			return;
		}

		CDatabase db;
		if (!db.Open(_T("ҽҩ���������ݿ�")))
			MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

		cs.Format(_T("delete from ְ����Ϣ where	ID = '%s'"), 
			m_list.GetItemText(n, 0));
		db.ExecuteSQL(cs);
		db.Close();
		ListTheInfo();
	}
	else
	{
		MessageBox(_T("��ְ����Ϣ�򵥻�ѡ�й���"), 
			_T("��ʾ"), MB_OK);
	}
}

void CWorkerDlg::OnNMDblclkWorkerInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedWorkerModify();
	*pResult = 0;
}
