// BussiInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Begin.h"
#include "BussiInfoDlg.h"
#include "BussiInfoSet.h"
#include "BussiInfoAddDlg.h"

// CBussiInfoDlg 对话框

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


// CBussiInfoDlg 消息处理程序

BOOL CBussiInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list.InsertColumn(0, _T("编号"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(1, _T("公司"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(2, _T("地址"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(3, _T("联系方式"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(4, _T("备注"), LVCFMT_CENTER, 200);
	//m_list.SetBkColor(RGB(26, 231, 151));
	//m_list.SetTextBkColor(RGB(26, 231, 151));
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES);

	ListTheInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CBussiInfoDlg::ListTheInfo()
{
	CBussiInfoSet setBussi;

	setBussi.m_strFilter.Format(_T(""));
	if (!setBussi.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

	m_list.DeleteAllItems();
	if(setBussi.IsEOF())                           
		MessageBox(_T("暂无供货商信息"), _T("提示"), MB_OK);
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
	// TODO: 在此添加控件通知处理程序代码
	CBussiInfoAddDlg dlg;
	if (dlg.DoModal() == IDOK)
		ListTheInfo();
}

void CBussiInfoDlg::OnBnClickedBussiDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cs;
	int n = m_list.GetSelectionMark();
	
	if (n >= 0)
	{
		cs.Format(_T("确定要删除 “%s”"), m_list.GetItemText(n, 1));
		if (IDOK != MessageBox(cs, 
			_T("提示"), MB_OKCANCEL))
		{
			return;
		}

		CDatabase db;
		if (!db.Open(_T("医药进销存数据库")))
			MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
	
		cs.Format(_T("delete from 供货商信息 where code = '%s'"), 
			m_list.GetItemText(n, 0));
		db.ExecuteSQL(cs);
		db.Close();
		ListTheInfo();
	}
	else
	{
		MessageBox(_T("无供应商信息或单击选中供应商编号"), 
		_T("提示"), MB_OK);
	}
}

void CBussiInfoDlg::OnBnClickedBussiModify()
{
	// TODO: 在此添加控件通知处理程序代码
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
		MessageBox(_T("无供应商信息或单击选中供应商编号"), 
			_T("提示"), MB_OK);
	}
	
}

void CBussiInfoDlg::OnNMDblclkBussiInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedBussiModify();
	*pResult = 0;
}
