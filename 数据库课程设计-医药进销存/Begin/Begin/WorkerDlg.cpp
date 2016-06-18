// WorkerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Begin.h"
#include "WorkerDlg.h"
#include "WorkerInfoSet.h"
#include "WorkerInfoAddDlg.h"


// CWorkerDlg 对话框

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


// CWorkerDlg 消息处理程序

// 初始化对话框时候，直接吧职工表中的数据读入list 列表
BOOL CWorkerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list.InsertColumn(0, _T("工号"), LVCFMT_CENTER, 55);
	m_list.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(2, _T("职位"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(3, _T("联系方式"), LVCFMT_CENTER, 120);
	//m_list.SetBkColor(RGB(26, 231, 151));
	//m_list.SetTextBkColor(RGB(26, 231, 151));
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES);

	ListTheInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CWorkerDlg::ListTheInfo()
{
	CWorkerInfoSet setWorker;

	setWorker.m_strFilter.Format(_T(""));
	if (!setWorker.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

	m_list.DeleteAllItems();
	if(setWorker.IsEOF())                           
		MessageBox(_T("暂无职工信息"), _T("提示"), MB_OK);
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
	// TODO: 在此添加控件通知处理程序代码
	CWorkerInfoAddDlg dlg;
	if (dlg.DoModal() == IDOK)
		ListTheInfo();
}

void CWorkerDlg::OnBnClickedWorkerModify()
{
	// TODO: 在此添加控件通知处理程序代码
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
		MessageBox(_T("无职工信息或单击选中职工编号"), _T("提示"), MB_OK);
	}
}

void CWorkerDlg::OnBnClickedWorkerDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cs;
	int n = m_list.GetSelectionMark();

	if (n >= 0)
	{
		cs.Format(_T("确定要删除 “%s”"), m_list.GetItemText(n, 1));
		if (IDOK != MessageBox(cs, _T("提示"), MB_OKCANCEL))
		{
			return;
		}

		CDatabase db;
		if (!db.Open(_T("医药进销存数据库")))
			MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

		cs.Format(_T("delete from 职工信息 where	ID = '%s'"), 
			m_list.GetItemText(n, 0));
		db.ExecuteSQL(cs);
		db.Close();
		ListTheInfo();
	}
	else
	{
		MessageBox(_T("无职工信息或单击选中工号"), 
			_T("提示"), MB_OK);
	}
}

void CWorkerDlg::OnNMDblclkWorkerInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedWorkerModify();
	*pResult = 0;
}
