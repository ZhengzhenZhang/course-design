// ClassRoomDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ClassRoom.h"
#include "ClassRoomDlg.h"
#include "RecordsetCS.h"
#include "RecordsetTBuild.h"
#include "DlgDetail.h"
#include "RecordsetOC.h"
#include "DlgLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

TCHAR weekDay[] = L"��һ����������";		// ������ʾ���ڵ�����

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CClassRoomDlg �Ի���




CClassRoomDlg::CClassRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClassRoomDlg::IDD, pParent)
	, m_dTime(COleDateTime::GetCurrentTime())
	, m_strComboTBuild(_T(""))
	, m_strCRommNum(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_isSearch = FALSE;
}

void CClassRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CRINFO, m_listCrInfo);
	DDX_DateTimeCtrl(pDX, IDC_DATE_TIME, m_dTime);
	DDX_Control(pDX, IDC_COMBO_TBUILD, m_comboTBuild);
	DDX_CBString(pDX, IDC_COMBO_TBUILD, m_strComboTBuild);
	DDX_Text(pDX, IDC_EDIT_CROOMNUM, m_strCRommNum);
}

BEGIN_MESSAGE_MAP(CClassRoomDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(DTN_CLOSEUP, IDC_DATE_TIME, &CClassRoomDlg::OnDtnCloseupDateTime)
	ON_CBN_SELCHANGE(IDC_COMBO_TBUILD, &CClassRoomDlg::OnCbnSelchangeComboTbuild)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CClassRoomDlg::OnBnClickedButtonSearch)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CRINFO, &CClassRoomDlg::OnNMDblclkListCrinfo)
END_MESSAGE_MAP()


// CClassRoomDlg ��Ϣ�������

BOOL CClassRoomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_myFont.CreatePointFont(150, _T("���Ŀ���"));
	m_myColor = RGB(255, 0, 255);

	CreateLayout();
	ListTBuildComboBox();
	ListThisTime();
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CClassRoomDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClassRoomDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CClassRoomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClassRoomDlg::OnDtnCloseupDateTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CreateLayout();		// ���ȶԿؼ����в���
	ListThisTime();		// Ȼ���г���Ӧ������
	*pResult = 0;
}

void CClassRoomDlg::OnCbnSelchangeComboTbuild()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CreateLayout();		// ���ȶԿؼ����в���
	ListThisTime();		// Ȼ���г���Ӧ������
}



//---------------
//---���ܣ����Ի����е��ſ���Ϣ��ͼ����---
//---����ˣ���ϡ��---
//---���ʱ�䣺2012-12-25---
//---�޸�ʱ�䣺---
//---------------
void CClassRoomDlg::CreateLayout()
{
	ClearList();	// ���ֵ�ʱ�����������ǰ�Ĳ�����Ϣ
	m_listCrInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
					// ������չ����Ϊ�����ȫѡ
	m_listCrInfo.InsertColumn(0, _T(""), LVCFMT_CENTER, 40);
	m_listCrInfo.InsertColumn(1, _T("���ұ��"), LVCFMT_CENTER, 80);
	m_listCrInfo.InsertColumn(2, _T("��һ���"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(3, _T("�ڶ����"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(4, _T("�������"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(5, _T("���Ĵ��"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(6, _T("������"), LVCFMT_CENTER, 100);
}
//---------------
//---���ܣ������ſ���Ϣ��ͼ����---
//---����ˣ���ϡ��---
//---���ʱ�䣺2012-12-25---
//---�޸�ʱ�䣺---
//---------------
void CClassRoomDlg::CreateLayout2()
{
	ClearList();
	m_listCrInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_listCrInfo.InsertColumn(0, _T("����"), LVCFMT_CENTER, 40);
	m_listCrInfo.InsertColumn(1, _T("���ұ��"), LVCFMT_CENTER, 80);
	m_listCrInfo.InsertColumn(2, _T("��һ���"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(3, _T("�ڶ����"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(4, _T("�������"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(5, _T("���Ĵ��"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(6, _T("������"), LVCFMT_CENTER, 100);
}


//---------------
//---���ܣ�����б���ͼ�ؼ��е���---
//---����ˣ���ϡ��--
//---���ʱ�䣺2012-12-25---
//---�޸�ʱ�䣺---
//---------------
void CClassRoomDlg::ClearList()
{

	m_listCrInfo.DeleteAllItems();	// ����е�ʱ������Ҫɾ��ԭ�����е�Ԫ��
	// Delete all of the columns.
	while (m_listCrInfo.DeleteColumn(0));
									// ɾ����ֱ��ɾ���꣬����0ֵ���˳�ѭ��
}

//---------------
//---���ܣ��õ�ѡ����������Ȼ���г��ſ���Ϣ---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
void CClassRoomDlg::ListThisTime()
{
	m_isSearch = FALSE;	// �������ã�FALSE��ʾ�û����ǵ��������г��û���Ϣ

	UpdateData(TRUE);	// ���ؼ�ֵ���ݸ���������

	m_nWeek = m_dTime.GetDayOfWeek()-1;	
	// �õ����ڣ�0����������

	CString strTmp;
	strTmp.Format(_T("����%c"), weekDay[m_nWeek]);
	GetDlgItem(IDC_STATIC_WEEK)->SetWindowText(strTmp);

	CString strSQL;
	strSQL.Format(_T("csWeek = '%d' AND tBuildNum = '%s'"), m_nWeek, m_strComboTBuild);

	ListCSInfo(strSQL);
}

//---------------
//---���ܣ�����SQL��������г��ſ���Ϣ---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
void CClassRoomDlg::ListCSInfo(CString strSQL)
{
	m_listCrInfo.DeleteAllItems();
	CRecordsetCS setCS;

	setCS.m_strFilter = strSQL;

	if (!setCS.Open())
	{
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
		setCS.Close();
		return;
	}
	CString strTmp;

	for (int i=0; !setCS.IsEOF(); i++)
	{
		if (m_isSearch)
		{
			strTmp.Format(_T("%c"), weekDay[setCS.m_csWeek]);
		}
		else
		{
			strTmp.Format(_T("%d"), i+1);
		}
		m_listCrInfo.InsertItem(i, strTmp);

		setCS.m_cRoomNum.TrimRight();		
		m_listCrInfo.SetItemText(i, 1, setCS.m_cRoomNum);

		setCS.m_csFirst.TrimRight();
		m_listCrInfo.SetItemText(i, 2, setCS.m_csFirst);

		setCS.m_csSecond.TrimRight();
		m_listCrInfo.SetItemText(i, 3, setCS.m_csSecond);

		setCS.m_csThird.TrimRight();
		m_listCrInfo.SetItemText(i, 4, setCS.m_csThird);

		setCS.m_csFourth.TrimRight();
		m_listCrInfo.SetItemText(i, 5, setCS.m_csFourth);

		setCS.m_csFifth.TrimRight();
		m_listCrInfo.SetItemText(i, 6, setCS.m_csFifth);

		setCS.MoveNext();
	}

	setCS.Close();
	ListOCInfoSearch();
}

//---------------
//---���ܣ������г��б���ͼ�е�ռ����Ϣ---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
void CClassRoomDlg::ListOCInfoSearch()
{
	int n = m_listCrInfo.GetItemCount();

	for (int i=0; i<n; i++)
	{
		ListOCInfo(i, m_listCrInfo.GetItemText(i, 1));
	}
}
void CClassRoomDlg::ListOCInfo(int nIndex, CString myCNum)
{
	CString strTime;// ���ȵõ�ʱ��
	GetDlgItem(IDC_DATE_TIME)->GetWindowText(strTime);
	strTime += _T("  ����");
	if (m_isSearch)
		strTime += m_listCrInfo.GetItemText(nIndex, 0);
	else
		strTime += weekDay[m_nWeek];

	// �ӽ���ռ����Ϣ���ݿ���ȡ������
	CRecordsetOC setOC;

	CString strSQL;
	strSQL.Format(_T("ocTime = '%s' AND cRoomNum = '%s'"), 
		strTime, myCNum);

	setOC.m_strFilter = strSQL;

	if (!setOC.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
	if (setOC.IsEOF()) {
		setOC.Close();
		return;	// ���û�оͲ��޸�
	}
	
	CString strTmp;
	
	strTmp = m_listCrInfo.GetItemText(nIndex, 2);
	setOC.m_ocFirst.TrimRight();
	if (_T("") == strTmp && _T("") != setOC.m_ocFirst)
	{
		strTmp += _T("*");			// �Բ��ǿγ���Ϣ��������
		strTmp += setOC.m_ocFirst;
		strTmp += _T("*");
		m_listCrInfo.SetItemText(nIndex, 2, strTmp);
	}
	
	strTmp = m_listCrInfo.GetItemText(nIndex, 3);
	setOC.m_ocSecond.TrimRight();
	if (_T("") == strTmp && _T("") != setOC.m_ocSecond)
	{
		
		strTmp += _T("*");			// �Բ��ǿγ���Ϣ��������
		strTmp += setOC.m_ocSecond;
		strTmp += _T("*");
		m_listCrInfo.SetItemText(nIndex, 3, strTmp);
	}
	
	strTmp = m_listCrInfo.GetItemText(nIndex, 4);
	setOC.m_ocThird.TrimRight();
	if (_T("") == strTmp && _T("") != setOC.m_ocThird)
	{
		strTmp += _T("*");			// �Բ��ǿγ���Ϣ��������
		strTmp += setOC.m_ocThird;
		strTmp += _T("*");
		m_listCrInfo.SetItemText(nIndex, 4, strTmp);
	}
	
	strTmp = m_listCrInfo.GetItemText(nIndex, 5);
	setOC.m_ocFourth.TrimRight();
	if (_T("") == strTmp && _T("") != setOC.m_ocFourth)
	{
		strTmp += _T("*");			// �Բ��ǿγ���Ϣ��������
		strTmp += setOC.m_ocFourth;
		strTmp += _T("*");
		m_listCrInfo.SetItemText(nIndex, 5, strTmp);
	}
	
	strTmp = m_listCrInfo.GetItemText(nIndex, 6);
	setOC.m_ocFifth.TrimRight();
	if (_T("") == strTmp && _T("") != setOC.m_ocFifth)
	{
		strTmp += _T("*");			// �Բ��ǿγ���Ϣ��������
		strTmp += setOC.m_ocFifth;
		strTmp += _T("*");
		m_listCrInfo.SetItemText(nIndex, 6, strTmp);
	}
}


//---------------
//---���ܣ�����Ͽ����г���ѧ¥���---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
void CClassRoomDlg::ListTBuildComboBox()
{
	CRecordsetTBuild setTBuild;

	if (!setTBuild.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	for (int i=0; !setTBuild.IsEOF(); i++)
	{
		setTBuild.m_tBuildNum.TrimRight();
		m_comboTBuild.AddString(setTBuild.m_tBuildNum);
		setTBuild.MoveNext();
	}
	m_comboTBuild.SetCurSel(0);

	setTBuild.Close();
}

//---------------
//---���ܣ����������Լ���ɫ��Ϣ��Ӧ����---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
HBRUSH CClassRoomDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if(pWnd->GetDlgCtrlID()==IDC_STATIC_WEEK)
	{
		pDC->SelectObject(&m_myFont);	// ��������
		pDC->SetTextColor(m_myColor);	// ������ɫ
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

//---------------
//---���ܣ�������ť��Ϣ��Ӧ����---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
void CClassRoomDlg::OnBnClickedButtonSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CreateLayout2();		// �л�������2
	m_isSearch = TRUE;		// �������ã�FALSE��ʾ�û��ǵ��������г��û���Ϣ
	
	UpdateData(TRUE);		// ���ؼ�ֵ���ݸ���������	

	if (_T("") == m_strCRommNum)
	{
		MessageBox(_T("�������������ݣ�"), _T("��ʾ"), MB_OK);
		GetDlgItem(IDC_EDIT_CROOMNUM)->SetFocus();
		return;
	}

	CString strSQL;
	strSQL = _T("cRoomNum like '%");
	strSQL += m_strCRommNum;
	strSQL += _T("%'");

	ListCSInfo(strSQL);
}

//---------------
//---���ܣ��޸�����Ĭ�ϻس���ESC��������Ӧ---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
void CClassRoomDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	OnBnClickedButtonSearch();
}
void CClassRoomDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	
	if (IDOK != MessageBox(_T("�Ƿ��˳���"), _T("��ʾ"), MB_OKCANCEL))
		return;
	CDialog::OnCancel();
}


//---------------
//---���ܣ�˫���б���ͼ�����¶Ի���---
//---����ˣ�κǿ---
//---���ʱ�䣺2012-12-26---
//---�޸�ʱ�䣺2012-12-28---
//---------------
void CClassRoomDlg::OnNMDblclkListCrinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgDetail dlg;		// ����һ��������Ϣ�Ի������
	
	int n = m_listCrInfo.GetSelectionMark();
						// �õ�˫�����б���ͼԪ�ر��
	
	if (n >= 0 && n<m_listCrInfo.GetItemCount()) 
						// ˫����Ԫ�����б���ͼ��
	{
		// ��ʼ���¶Ի�������е�һЩ��Ϣ
		dlg.m_strDCNum = m_listCrInfo.GetItemText(n, 1);
		dlg.m_nWeek = m_nWeek;

		GetDlgItem(IDC_DATE_TIME)->GetWindowText(dlg.m_strDTime);
		dlg.m_strDTime += _T("  ����");
		dlg.m_strDTime += weekDay[m_nWeek];
		
		if (IDOK == dlg.DoModal())
		{
			
			ListThisTime();
		}
	}

	*pResult = 0;
}


void CClassRoomDlg::PreInitDialog()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDlgLogin dlg;

	dlg.DoModal();
	CDialog::PreInitDialog();
}
