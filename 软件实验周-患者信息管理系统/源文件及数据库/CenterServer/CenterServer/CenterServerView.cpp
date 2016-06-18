// CenterServerView.cpp : CCenterServerView 类的实现
//

#include "stdafx.h"
#include "CenterServer.h"

#include "CenterServerDoc.h"
#include "CenterServerView.h"

#include "RecordsetPatient.h"
#include "RecordsetDiag.h"
#include "DlgPatientInfo.h"

#include "DlgConfigPort.h"

#include "MainFrm.h"

#include "ThreadProc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCenterServerView

IMPLEMENT_DYNCREATE(CCenterServerView, CListView)

BEGIN_MESSAGE_MAP(CCenterServerView, CListView)
	ON_COMMAND(ID_MY_PATIENT, &CCenterServerView::OnMyPatient)
	ON_COMMAND(ID_MY_DIAG, &CCenterServerView::OnMyDiag)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CCenterServerView::OnNMDblclk)
	ON_COMMAND(ID_MY_SEARCH, OnMySearch)
	ON_COMMAND(IDOK, OnOK)
	ON_COMMAND(ID_MYMENU_ADD, &CCenterServerView::OnMymenuAdd)
	ON_COMMAND(ID_MYMENU_DELETE, &CCenterServerView::OnMymenuDelete)
	ON_COMMAND(ID_MYMENU_MODIFY, &CCenterServerView::OnMymenuModify)
	ON_COMMAND(ID_MYMENU_ADDNEW, &CCenterServerView::OnMymenuAddnew)
	ON_COMMAND(ID_MYMENU_CONFIGPORT, &CCenterServerView::OnMymenuConfigport)
	ON_COMMAND(ID_PATIENT_LISTEN, &CCenterServerView::OnPatientListen)
	// ON_CBN_SELENDOK(ID_MY_COMBOBOX, &CCenterServerView::OnCbnSelendokSearch)
END_MESSAGE_MAP()

// CCenterServerView 构造/析构

CCenterServerView::CCenterServerView()
{
	// TODO: 在此处添加构造代码
	m_whichList = 0;
	m_ifSearch = 0;
	m_uintRegPort = 5001;
	m_uintDocPort = 5002;
	m_uintFeePort = 5003;
}

CCenterServerView::~CCenterServerView()
{
}

BOOL CCenterServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CListView::PreCreateWindow(cs);
}

void CCenterServerView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: 调用 GetListCtrl() 直接访问 ListView 的列表控件，
	//  从而可以用项填充 ListView。
	OnMyDiag();
}


// CCenterServerView 诊断

#ifdef _DEBUG
void CCenterServerView::AssertValid() const
{
	CListView::AssertValid();
}

void CCenterServerView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CCenterServerDoc* CCenterServerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCenterServerDoc)));
	return (CCenterServerDoc*)m_pDocument;
}
#endif //_DEBUG

// MY代码
//---------------
//---功能：工具栏搜索按钮消息响应函数---
//---完成人：张政桢---
//---完成时间：2012-12-25---
//---修改时间：---
//---------------
void CCenterServerView::OnMySearch()
{
	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
	CString strTmp;
	pMFram->m_wndComboBox.GetWindowText(strTmp);

	SuperSearch(strTmp);	// 调用搜索函数
	
	// 下面实现在组合框中添加元素，记录历史
	
	if (strTmp == _T(""))	// 如果组合框为空则返回不执行下面操作
		return;
	int index = pMFram->m_wndComboBox.FindStringExact(-1, strTmp);
	if (index != CB_ERR) 
	{
		pMFram->m_wndComboBox.DeleteString(index);

	}

	pMFram->m_wndComboBox.InsertString(0, strTmp);
	pMFram->m_wndComboBox.SetWindowText(strTmp);

	m_whichList = 2;	// 标记变量，用于标记患者信息窗口的状态
	m_ifSearch = 1;
}

//---------------
//---功能：使工具栏组合框响应回车消息---
//---完成人：张政桢---
//---完成时间：2012-12-25---
//---修改时间：---
//---------------
void CCenterServerView::OnOK()
{
	OnMySearch();
}

// // 响应用户选择组合框控件内容
// void CCenterServerView::OnCbnSelendokSearch()
// {
//		OnMySearch();
// }

//---------------
//---功能：完成模糊搜索并将就诊信息结果显示在视图中---
//---完成人：张政桢---
//---完成时间：2012-12-25---
//---修改时间：---
//---------------
void CCenterServerView::SuperSearch(CString strSearch)
{
	CString strSQL;

	strSearch.Replace(_T(" "), _T("%"));

	strSQL = _T("idNumber like '%");
	strSQL += strSearch;
	strSQL += _T("%'");

	strSQL += _T(" or ");

	strSQL += _T("patientSex like '%");
	strSQL += strSearch;
	strSQL += _T("%'"); 

	strSQL += _T(" or ");

	strSQL += _T("patientName like '%");
	strSQL += strSearch;
	strSQL += _T("%'"); 

	strSQL += _T(" or ");

	strSQL += _T("patientPhone like '%");
	strSQL += strSearch;
	strSQL += _T("%'"); 

	strSQL += _T(" or ");

	strSQL += _T("patientAge like '%");
	strSQL += strSearch;
	strSQL += _T("%'"); 

	strSQL += _T(" or ");

	strSQL += _T("patientAddress like '%");
	strSQL += strSearch;
	strSQL += _T("%'"); 

	strSQL += _T(" or ");

	strSQL += _T("diagDoctorID like '%");
	strSQL += strSearch;
	strSQL += _T("%'"); 

	strSQL += _T(" or ");

	strSQL += _T("diagNum like '%");
	strSQL += strSearch;
	strSQL += _T("%'"); 

	strSQL += _T(" or ");

	strSQL += _T("patientNum like '%");
	strSQL += strSearch;
	strSQL += _T("%'"); 

	strSQL += _T(" or ");

	strSQL += _T("diagDeclare like '%");
	strSQL += strSearch;
	strSQL += _T("%'"); 

	CreateDiagLayout();
	ListDiagInfo(strSQL);
}

//---------------
//---功能：双击列表视图消息响应函数弹出对应患者的就诊信息窗口---
//---完成人：张政桢---
//---完成时间：2012-12-25---
//---修改时间：---
//---------------
void CCenterServerView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	DialogOprate(0);

	*pResult = 0;
}

//---------------
//---功能：添加按钮消息响应---
//---下面依次是添加新患者、删除、修改消息响应
//---完成人：张政桢---
//---完成时间：2012-12-26---
//---修改时间：---
//---------------
void CCenterServerView::OnMymenuAdd()
{
	// TODO: 在此添加命令处理程序代码
	DialogOprate(3);	// 传递标识参数
}
void CCenterServerView::OnMymenuAddnew()
{
	// TODO: 在此添加命令处理程序代码
	DialogOprate(2);
}
void CCenterServerView::OnMymenuDelete()
{
	// TODO: 在此添加命令处理程序代码
	DleteInfo();
}

void CCenterServerView::OnMymenuModify()
{
	// TODO: 在此添加命令处理程序代码
	DialogOprate(1);
}

//---------------
//---功能：清除视图区域的列表---
//---完成人：张政桢---
//---完成时间：2012-12-25---
//---修改时间：---
//---------------
void CCenterServerView::ClearList()
{
	CListCtrl& m_myListCtrl = GetListCtrl();

	m_myListCtrl.DeleteAllItems();
	// Delete all of the columns.
	while (m_myListCtrl.DeleteColumn(0));
}

//---------------
//---功能：根据用户操作调用患者就诊信息对话框
//---     参数为0代表只读  1代表修改 2代表添加新患者 3代表添加就诊信息
//---完成人：张政桢---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
void CCenterServerView::DialogOprate(int m_whichOperate)
{
	CDlgPatientInfo dlg;

	dlg.m_flagOperate = m_whichOperate;

	CListCtrl& listCtrl = GetListCtrl();
	int n = listCtrl.GetSelectionMark();

	if (n >= 0 && (m_whichOperate != 2))
	{		
		if (1 == m_whichList)
		{
			dlg.m_strPId = listCtrl.GetItemText(n, 4);
		}
		else if (2 == m_whichList) 
		{
			dlg.m_strPId = listCtrl.GetItemText(n, 5);
			dlg.m_strDNum = listCtrl.GetItemText(n, 1);
		}
	}
	else if (m_whichOperate != 2)
	{
		MessageBox(_T("请选择您要查询的选项！"), _T("提示"), MB_OK);
		return;
	}

	dlg.DoModal();
	if (dlg.m_ifModify)	// 如果用户进行了修改则更新视图显示列表
	{
		if (m_ifSearch) 
			OnMySearch();
		else if (1 == m_whichList)
			ListPatientInfo(_T(""));
		else if (2 == m_whichList)
			ListDiagInfo(_T(""));
	}
}

//---------------
//---功能：删除用户选择的患者信息或就诊信息---
//---完成人：张政桢---
//---完成时间：2012-12-26---
//---修改时间：---
//---------------
void CCenterServerView::DleteInfo()
{
	CListCtrl& listCtrl = GetListCtrl();
	int n = listCtrl.GetSelectionMark();

	CString strDelete, strSQL;

	if (n>=0 && 2 == m_whichList)		// 如果为删除就诊信息
	{
		if (IDOK != MessageBox(_T("确定要删除该就诊信息？"), _T("提示"), MB_OKCANCEL))
			return;
		strDelete = listCtrl.GetItemText(n, 1);
		DleteInfoItem(strDelete);
		ListDiagInfo(_T(""));
	}
	else if (n>=0 && 1 == m_whichList)		// 如果为删除患者信息
	{
		if (IDOK != MessageBox(_T("确定要删除该患者信息及其就诊信息？"), _T("提示"), MB_OKCANCEL))
			return;
		strDelete = listCtrl.GetItemText(n, 4);

		CRecordsetDiag setDiag;				// 首先得获得该患者的所有就诊信息记录集，然后再单独删除

		strSQL.Format(_T("idNumber = '%s'"), strDelete);
		setDiag.m_strFilter = strSQL;

		if (!setDiag.Open())
			MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

		for (int i=0; !setDiag.IsEOF(); i++)
		{
			CString strTmp;
			strTmp.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
				setDiag.m_diagNum.GetYear(), setDiag.m_diagNum.GetMonth(), setDiag.m_diagNum.GetDay(),
				setDiag.m_diagNum.GetHour(), setDiag.m_diagNum.GetMinute(), setDiag.m_diagNum.GetSecond());
			DleteInfoItem(strTmp);		// 先删除患者的所有就诊信息
			setDiag.MoveNext();	
		}
		setDiag.Close();

		DleteInfoItem(strDelete, TRUE);	// 最后删除患者信息

		ListPatientInfo(_T(""));
	}
	else
	{
		MessageBox(_T("请选择您要查询的选项！"), _T("提示"), MB_OK);
		return;
	}
	MessageBox(_T("删除成功"), _T("提示"), MB_OK);
}
//---------------
//---功能：删除用户选择的患者信息或就诊信息子功能模块
//---     bInfo为TURE表示删除患者信息，默认FALSE为删除就诊信息
//---完成人：张政桢---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
void CCenterServerView::DleteInfoItem(CString strDelete, BOOL bInfo)
{
	CString strSQL;
	CDatabase db;
	if (!db.Open(_T("患者就诊数据库")))
	{
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
		return;
	}

	if (bInfo)
	{
		strSQL.Format(_T("DELETE FROM 患者信息 WHERE idNumber = '%s'"), strDelete);
		db.ExecuteSQL(strSQL);
		db.Close();
		return;
	}

	strSQL.Format(_T("DELETE FROM 就诊信息 WHERE diagNum = '%s'"), strDelete);
	db.ExecuteSQL(strSQL);

	strSQL.Format(_T("DELETE FROM 费用信息 WHERE diagNum = '%s'"), strDelete);
	db.ExecuteSQL(strSQL);

	strSQL.Format(_T("DELETE FROM 诊后恢复结果信息 WHERE diagNum = '%s'"), strDelete);
	db.ExecuteSQL(strSQL);

	db.Close();
}



//---------------
//---功能：在视图中列出所有的患者信息---
//---完成人：魏强---
//---完成时间：2012-12-25---
//---修改时间：---
//---------------
void CCenterServerView::OnMyPatient()
{
	// TODO: 在此添加命令处理程序代码
	CreatePatientLayout();
	ListPatientInfo(_T(""));

	m_whichList = 1;
	m_ifSearch = 0;
}

//---------------
//---功能：在视图中列出所有的就诊信息---
//---完成人：魏强---
//---完成时间：2012-12-25---
//---修改时间：---
//---------------
void CCenterServerView::OnMyDiag()
{
	// TODO: 在此添加命令处理程序代码
	CreateDiagLayout();
	ListDiagInfo(_T(""));

	m_whichList = 2;
	m_ifSearch = 0;
}




//---------------
//---功能：显示病人信息的视图布局---
//---完成人：魏强---
//---完成时间：2012-12-25---
//---修改时间：---
//---------------
void CCenterServerView::CreatePatientLayout()
{

	ClearList();

	CListCtrl& listCtrl = GetListCtrl();

	listCtrl.ModifyStyle(0, LVS_REPORT);
	listCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
	listCtrl.InsertColumn(0, _T(""), LVCFMT_CENTER, 30);
	listCtrl.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(2, _T("性别"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(3, _T("年龄"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(4, _T("身份证"), LVCFMT_CENTER, 150);
	listCtrl.InsertColumn(5, _T("联系方式"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(6, _T("住址"), LVCFMT_CENTER, 200);
}

//---------------
//---功能：显示就诊信息的视图布局---
//---完成人：魏强---
//---完成时间：2012-12-25---
//---修改时间：---
//---------------
void CCenterServerView::CreateDiagLayout()
{

	ClearList();

	CListCtrl& listCtrl = GetListCtrl();


	listCtrl.ModifyStyle(0, LVS_REPORT);
	listCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	listCtrl.InsertColumn(0, _T(""), LVCFMT_CENTER, 30);
	listCtrl.InsertColumn(1, _T("时间"), LVCFMT_CENTER, 150);
	listCtrl.InsertColumn(2, _T("姓名"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(3, _T("性别"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(4, _T("年龄"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(5, _T("身份证"), LVCFMT_CENTER, 150);
	listCtrl.InsertColumn(6, _T("联系方式"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(7, _T("就诊医师编号"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(8, _T("住址"), LVCFMT_CENTER, 200);

}


//---------------
//---功能：接收SQL条件语句列出患者信息---
//---完成人：魏强---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
void CCenterServerView::ListPatientInfo(CString strSQL)
{
	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.DeleteAllItems();

	CRecordsetPatient setPatient;

	setPatient.m_strFilter = strSQL;

	if (!setPatient.Open())
	{
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
		setPatient.Close();
		return;
	}
	CString strTmp;

	for (int i=0; !setPatient.IsEOF() && i<500; i++)
	{
		strTmp.Format(_T("%d"), i+1);
		listCtrl.InsertItem(i, strTmp);

		setPatient.m_patientName.TrimRight();		
		listCtrl.SetItemText(i, 1, setPatient.m_patientName);
		
		setPatient.m_patientSex.TrimRight();
		listCtrl.SetItemText(i, 2, setPatient.m_patientSex);
		
		strTmp.Format(_T("%d"), setPatient.m_patientAge);
		listCtrl.SetItemText(i, 3, strTmp);

		setPatient.m_idNumber.TrimRight();
		listCtrl.SetItemText(i, 4, setPatient.m_idNumber);

		setPatient.m_patientPhone.TrimRight();
		listCtrl.SetItemText(i, 5, setPatient.m_patientPhone);

		setPatient.m_patientAddress.TrimRight();
		listCtrl.SetItemText(i, 6, setPatient.m_patientAddress);

		setPatient.MoveNext();
	}
	
	setPatient.Close();
}

//---------------
//---功能：接收SQL条件语句列出就诊信息
//---完成人：魏强---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
void CCenterServerView::ListDiagInfo(CString strSQL)
{
	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.DeleteAllItems();

	CRecordsetDiag setDiag;

	setDiag.m_strFilter = strSQL;

	if (!setDiag.Open())
	{
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
		setDiag.Close();
		return;
	}

	CString strTmp;
	
	for (int i=0; !setDiag.IsEOF() && i<500; i++)
	{
		strTmp.Format(_T("%d"), i+1);
		listCtrl.InsertItem(i, strTmp);

		strTmp.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
			setDiag.m_diagNum.GetYear(), setDiag.m_diagNum.GetMonth(), setDiag.m_diagNum.GetDay(),
			setDiag.m_diagNum.GetHour(), setDiag.m_diagNum.GetMinute(), setDiag.m_diagNum.GetSecond());
	
		listCtrl.SetItemText(i, 1, strTmp);

		setDiag.m_patientName.TrimRight();
		listCtrl.SetItemText(i, 2, setDiag.m_patientName);
		
		setDiag.m_patientSex.TrimRight();
		listCtrl.SetItemText(i, 3, setDiag.m_patientSex);

		strTmp.Format(_T("%d"), setDiag.m_patientAge);
		listCtrl.SetItemText(i, 4, strTmp);

		setDiag.m_idNumber.TrimRight();
		listCtrl.SetItemText(i, 5, setDiag.m_idNumber);

		setDiag.m_patientPhone.TrimRight();
		listCtrl.SetItemText(i, 6, setDiag.m_patientPhone);

		setDiag.m_diagDoctorID.TrimRight();
		listCtrl.SetItemText(i, 7, setDiag.m_diagDoctorID);

		setDiag.m_patientAddress.TrimRight();
		listCtrl.SetItemText(i, 8, setDiag.m_patientAddress);

		setDiag.MoveNext();
	}
	
	setDiag.Close();
}





//*******************************************************************/









//---功能：调用配置端口对话框（废弃代码）
//---完成人：
//---完成时间：
//---修改时间：
//---------------
void CCenterServerView::OnMymenuConfigport()
{
	// TODO: 在此添加命令处理程序代码
	CDlgConfigPort dlg;

	if (IDOK != dlg.DoModal())
	{	
		return;
	}
	m_uintRegPort = dlg.m_uintRegPort;
	m_uintDocPort = dlg.m_uintDocPort;
	m_uintFeePort = dlg.m_uintFeePort;
}
void CCenterServerView::OnPatientListen()
{
	// TODO: 在此添加命令处理程序代码
	AfxBeginThread(ThreadProc1, NULL);
	
}
