// CenterServerView.cpp : CCenterServerView ���ʵ��
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

// CCenterServerView ����/����

CCenterServerView::CCenterServerView()
{
	// TODO: �ڴ˴���ӹ������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CListView::PreCreateWindow(cs);
}

void CCenterServerView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: ���� GetListCtrl() ֱ�ӷ��� ListView ���б�ؼ���
	//  �Ӷ������������ ListView��
	OnMyDiag();
}


// CCenterServerView ���

#ifdef _DEBUG
void CCenterServerView::AssertValid() const
{
	CListView::AssertValid();
}

void CCenterServerView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CCenterServerDoc* CCenterServerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCenterServerDoc)));
	return (CCenterServerDoc*)m_pDocument;
}
#endif //_DEBUG

// MY����
//---------------
//---���ܣ�������������ť��Ϣ��Ӧ����---
//---����ˣ�������---
//---���ʱ�䣺2012-12-25---
//---�޸�ʱ�䣺---
//---------------
void CCenterServerView::OnMySearch()
{
	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();
	CString strTmp;
	pMFram->m_wndComboBox.GetWindowText(strTmp);

	SuperSearch(strTmp);	// ������������
	
	// ����ʵ������Ͽ������Ԫ�أ���¼��ʷ
	
	if (strTmp == _T(""))	// �����Ͽ�Ϊ���򷵻ز�ִ���������
		return;
	int index = pMFram->m_wndComboBox.FindStringExact(-1, strTmp);
	if (index != CB_ERR) 
	{
		pMFram->m_wndComboBox.DeleteString(index);

	}

	pMFram->m_wndComboBox.InsertString(0, strTmp);
	pMFram->m_wndComboBox.SetWindowText(strTmp);

	m_whichList = 2;	// ��Ǳ��������ڱ�ǻ�����Ϣ���ڵ�״̬
	m_ifSearch = 1;
}

//---------------
//---���ܣ�ʹ��������Ͽ���Ӧ�س���Ϣ---
//---����ˣ�������---
//---���ʱ�䣺2012-12-25---
//---�޸�ʱ�䣺---
//---------------
void CCenterServerView::OnOK()
{
	OnMySearch();
}

// // ��Ӧ�û�ѡ����Ͽ�ؼ�����
// void CCenterServerView::OnCbnSelendokSearch()
// {
//		OnMySearch();
// }

//---------------
//---���ܣ����ģ����������������Ϣ�����ʾ����ͼ��---
//---����ˣ�������---
//---���ʱ�䣺2012-12-25---
//---�޸�ʱ�䣺---
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
//---���ܣ�˫���б���ͼ��Ϣ��Ӧ����������Ӧ���ߵľ�����Ϣ����---
//---����ˣ�������---
//---���ʱ�䣺2012-12-25---
//---�޸�ʱ�䣺---
//---------------
void CCenterServerView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	DialogOprate(0);

	*pResult = 0;
}

//---------------
//---���ܣ���Ӱ�ť��Ϣ��Ӧ---
//---��������������»��ߡ�ɾ�����޸���Ϣ��Ӧ
//---����ˣ�������---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺---
//---------------
void CCenterServerView::OnMymenuAdd()
{
	// TODO: �ڴ���������������
	DialogOprate(3);	// ���ݱ�ʶ����
}
void CCenterServerView::OnMymenuAddnew()
{
	// TODO: �ڴ���������������
	DialogOprate(2);
}
void CCenterServerView::OnMymenuDelete()
{
	// TODO: �ڴ���������������
	DleteInfo();
}

void CCenterServerView::OnMymenuModify()
{
	// TODO: �ڴ���������������
	DialogOprate(1);
}

//---------------
//---���ܣ������ͼ������б�---
//---����ˣ�������---
//---���ʱ�䣺2012-12-25---
//---�޸�ʱ�䣺---
//---------------
void CCenterServerView::ClearList()
{
	CListCtrl& m_myListCtrl = GetListCtrl();

	m_myListCtrl.DeleteAllItems();
	// Delete all of the columns.
	while (m_myListCtrl.DeleteColumn(0));
}

//---------------
//---���ܣ������û��������û��߾�����Ϣ�Ի���
//---     ����Ϊ0����ֻ��  1�����޸� 2��������»��� 3������Ӿ�����Ϣ
//---����ˣ�������---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
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
		MessageBox(_T("��ѡ����Ҫ��ѯ��ѡ�"), _T("��ʾ"), MB_OK);
		return;
	}

	dlg.DoModal();
	if (dlg.m_ifModify)	// ����û��������޸��������ͼ��ʾ�б�
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
//---���ܣ�ɾ���û�ѡ��Ļ�����Ϣ�������Ϣ---
//---����ˣ�������---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺---
//---------------
void CCenterServerView::DleteInfo()
{
	CListCtrl& listCtrl = GetListCtrl();
	int n = listCtrl.GetSelectionMark();

	CString strDelete, strSQL;

	if (n>=0 && 2 == m_whichList)		// ���Ϊɾ��������Ϣ
	{
		if (IDOK != MessageBox(_T("ȷ��Ҫɾ���þ�����Ϣ��"), _T("��ʾ"), MB_OKCANCEL))
			return;
		strDelete = listCtrl.GetItemText(n, 1);
		DleteInfoItem(strDelete);
		ListDiagInfo(_T(""));
	}
	else if (n>=0 && 1 == m_whichList)		// ���Ϊɾ��������Ϣ
	{
		if (IDOK != MessageBox(_T("ȷ��Ҫɾ���û�����Ϣ���������Ϣ��"), _T("��ʾ"), MB_OKCANCEL))
			return;
		strDelete = listCtrl.GetItemText(n, 4);

		CRecordsetDiag setDiag;				// ���ȵû�øû��ߵ����о�����Ϣ��¼����Ȼ���ٵ���ɾ��

		strSQL.Format(_T("idNumber = '%s'"), strDelete);
		setDiag.m_strFilter = strSQL;

		if (!setDiag.Open())
			MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

		for (int i=0; !setDiag.IsEOF(); i++)
		{
			CString strTmp;
			strTmp.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
				setDiag.m_diagNum.GetYear(), setDiag.m_diagNum.GetMonth(), setDiag.m_diagNum.GetDay(),
				setDiag.m_diagNum.GetHour(), setDiag.m_diagNum.GetMinute(), setDiag.m_diagNum.GetSecond());
			DleteInfoItem(strTmp);		// ��ɾ�����ߵ����о�����Ϣ
			setDiag.MoveNext();	
		}
		setDiag.Close();

		DleteInfoItem(strDelete, TRUE);	// ���ɾ��������Ϣ

		ListPatientInfo(_T(""));
	}
	else
	{
		MessageBox(_T("��ѡ����Ҫ��ѯ��ѡ�"), _T("��ʾ"), MB_OK);
		return;
	}
	MessageBox(_T("ɾ���ɹ�"), _T("��ʾ"), MB_OK);
}
//---------------
//---���ܣ�ɾ���û�ѡ��Ļ�����Ϣ�������Ϣ�ӹ���ģ��
//---     bInfoΪTURE��ʾɾ��������Ϣ��Ĭ��FALSEΪɾ��������Ϣ
//---����ˣ�������---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
void CCenterServerView::DleteInfoItem(CString strDelete, BOOL bInfo)
{
	CString strSQL;
	CDatabase db;
	if (!db.Open(_T("���߾������ݿ�")))
	{
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
		return;
	}

	if (bInfo)
	{
		strSQL.Format(_T("DELETE FROM ������Ϣ WHERE idNumber = '%s'"), strDelete);
		db.ExecuteSQL(strSQL);
		db.Close();
		return;
	}

	strSQL.Format(_T("DELETE FROM ������Ϣ WHERE diagNum = '%s'"), strDelete);
	db.ExecuteSQL(strSQL);

	strSQL.Format(_T("DELETE FROM ������Ϣ WHERE diagNum = '%s'"), strDelete);
	db.ExecuteSQL(strSQL);

	strSQL.Format(_T("DELETE FROM ���ָ������Ϣ WHERE diagNum = '%s'"), strDelete);
	db.ExecuteSQL(strSQL);

	db.Close();
}



//---------------
//---���ܣ�����ͼ���г����еĻ�����Ϣ---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-25---
//---�޸�ʱ�䣺---
//---------------
void CCenterServerView::OnMyPatient()
{
	// TODO: �ڴ���������������
	CreatePatientLayout();
	ListPatientInfo(_T(""));

	m_whichList = 1;
	m_ifSearch = 0;
}

//---------------
//---���ܣ�����ͼ���г����еľ�����Ϣ---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-25---
//---�޸�ʱ�䣺---
//---------------
void CCenterServerView::OnMyDiag()
{
	// TODO: �ڴ���������������
	CreateDiagLayout();
	ListDiagInfo(_T(""));

	m_whichList = 2;
	m_ifSearch = 0;
}




//---------------
//---���ܣ���ʾ������Ϣ����ͼ����---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-25---
//---�޸�ʱ�䣺---
//---------------
void CCenterServerView::CreatePatientLayout()
{

	ClearList();

	CListCtrl& listCtrl = GetListCtrl();

	listCtrl.ModifyStyle(0, LVS_REPORT);
	listCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	
	listCtrl.InsertColumn(0, _T(""), LVCFMT_CENTER, 30);
	listCtrl.InsertColumn(1, _T("����"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(2, _T("�Ա�"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(3, _T("����"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(4, _T("���֤"), LVCFMT_CENTER, 150);
	listCtrl.InsertColumn(5, _T("��ϵ��ʽ"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(6, _T("סַ"), LVCFMT_CENTER, 200);
}

//---------------
//---���ܣ���ʾ������Ϣ����ͼ����---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-25---
//---�޸�ʱ�䣺---
//---------------
void CCenterServerView::CreateDiagLayout()
{

	ClearList();

	CListCtrl& listCtrl = GetListCtrl();


	listCtrl.ModifyStyle(0, LVS_REPORT);
	listCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	listCtrl.InsertColumn(0, _T(""), LVCFMT_CENTER, 30);
	listCtrl.InsertColumn(1, _T("ʱ��"), LVCFMT_CENTER, 150);
	listCtrl.InsertColumn(2, _T("����"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(3, _T("�Ա�"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(4, _T("����"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(5, _T("���֤"), LVCFMT_CENTER, 150);
	listCtrl.InsertColumn(6, _T("��ϵ��ʽ"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(7, _T("����ҽʦ���"), LVCFMT_CENTER, 100);
	listCtrl.InsertColumn(8, _T("סַ"), LVCFMT_CENTER, 200);

}


//---------------
//---���ܣ�����SQL��������г�������Ϣ---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
void CCenterServerView::ListPatientInfo(CString strSQL)
{
	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.DeleteAllItems();

	CRecordsetPatient setPatient;

	setPatient.m_strFilter = strSQL;

	if (!setPatient.Open())
	{
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
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
//---���ܣ�����SQL��������г�������Ϣ
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
void CCenterServerView::ListDiagInfo(CString strSQL)
{
	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.DeleteAllItems();

	CRecordsetDiag setDiag;

	setDiag.m_strFilter = strSQL;

	if (!setDiag.Open())
	{
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
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









//---���ܣ��������ö˿ڶԻ��򣨷������룩
//---����ˣ�
//---���ʱ�䣺
//---�޸�ʱ�䣺
//---------------
void CCenterServerView::OnMymenuConfigport()
{
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
	AfxBeginThread(ThreadProc1, NULL);
	
}
