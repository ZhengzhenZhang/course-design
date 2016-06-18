// BussiInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Begin.h"
#include "BussiInfoDlg.h"
#include "BussiInfoSet.h"
#include "BussiInfoAddDlg.h"

// CBussiInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CBussiInfoDlg, CDialog)

CBussiInfoDlg::CBussiInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBussiInfoDlg::IDD, pParent)
{

}

CBussiInfoDlg::~CBussiInfoDlg()
{
}

void CBussiInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CBussiInfoDlg, CDialog)
	ON_BN_CLICKED(IDB_BUSSI_ADD, &CBussiInfoDlg::OnBnClickedBussiAdd)
	ON_BN_CLICKED(IDB_BUSSI_DELETE, &CBussiInfoDlg::OnBnClickedBussiDelete)
	ON_BN_CLICKED(IDB_BUSSI_MODIFY, &CBussiInfoDlg::OnBnClickedBussiModify)
	ON_NOTIFY(NM_DBLCLK, IDL_BUSSI_INFO, &CBussiInfoDlg::OnNMDblclkBussiInfo)
END_MESSAGE_MAP()


// CBussiInfoDlg ��Ϣ�������

BOOL CBussiInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list.InsertColumn(0, _T("���"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(1, _T("��˾"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, _T("��ַ"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(3, _T("��ϵ��ʽ"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(4, _T("��ע"), LVCFMT_CENTER, 200);
	//m_list.SetBkColor(RGB(26, 231, 151));
	//m_list.SetTextBkColor(RGB(26, 231, 151));
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES);

	ListTheInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CBussiInfoDlg::ListTheInfo()
{
	CBussiInfoSet setBussi;

	setBussi.m_strFilter.Format(_T(""));
	if (!setBussi.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	m_list.DeleteAllItems();
	if(setBussi.IsEOF())                           
		MessageBox(_T("���޹�������Ϣ"), _T("��ʾ"), MB_OK);
	else
	{
		for(int i=0; !setBussi.IsEOF(); i++,setBussi.MoveNext())
		{
			setBussi.m_code.TrimRight();
			m_list.InsertItem(i, setBussi.m_code);
			setBussi.m_name.TrimRight();
			m_list.SetItemText(i, 1, setBussi.m_name);
			setBussi.m_address.TrimRight();
			m_list.SetItemText(i, 2, setBussi.m_address);
			setBussi.m_phone.TrimRight();
			m_list.SetItemText(i, 3, setBussi.m_phone);
			setBussi.m_remark.TrimRight();
			m_list.SetItemText(i, 4, setBussi.m_remark);
		}
	}
	setBussi.Close();
}

void CBussiInfoDlg::OnBnClickedBussiAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CBussiInfoAddDlg dlg;
	if (dlg.DoModal() == IDOK)
		ListTheInfo();
}

void CBussiInfoDlg::OnBnClickedBussiDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString cs;
	int n = m_list.GetSelectionMark();
	
	if (n >= 0)
	{
		cs.Format(_T("ȷ��Ҫɾ�� ��%s��"), m_list.GetItemText(n, 1));
		if (IDOK != MessageBox(cs, 
			_T("��ʾ"), MB_OKCANCEL))
		{
			return;
		}

		CDatabase db;
		if (!db.Open(_T("ҽҩ���������ݿ�")))
			MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
	
		cs.Format(_T("delete from ��������Ϣ where code = '%s'"), 
			m_list.GetItemText(n, 0));
		db.ExecuteSQL(cs);
		db.Close();
		ListTheInfo();
	}
	else
	{
		MessageBox(_T("�޹�Ӧ����Ϣ�򵥻�ѡ�й�Ӧ�̱��"), 
		_T("��ʾ"), MB_OK);
	}
}

void CBussiInfoDlg::OnBnClickedBussiModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int n = m_list.GetSelectionMark();
	if (n >= 0){
		CBussiInfoAddDlg dlg;

		dlg.m_csOp.Format(_T("code = '%s'"),m_list.GetItemText(n,0));
		dlg.m_ifAdd = FALSE;

		if (dlg.DoModal() == IDOK)
			ListTheInfo();
	}
	else
	{
		MessageBox(_T("�޹�Ӧ����Ϣ�򵥻�ѡ�й�Ӧ�̱��"), 
			_T("��ʾ"), MB_OK);
	}
	
}

void CBussiInfoDlg::OnNMDblclkBussiInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedBussiModify();
	*pResult = 0;
}
