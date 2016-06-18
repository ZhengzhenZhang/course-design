// BeginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Begin.h"
#include "BeginDlg.h"
#include "LoginDlg.h"
#include "SellDlg.h"
#include "WorkerDlg.h"
#include "BussiInfoDlg.h"
#include "StoreInfoDlg.h"
#include "RecordSellDlg.h"
#include "UpdateDlg.h"
#include "RecordUpDlg.h"
#include "PastDrugDlg.h"
#include "RecordPastDlg.h"
#include "BackRecoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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


// CBeginDlg �Ի���




CBeginDlg::CBeginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBeginDlg::IDD, pParent)
	, m_search(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBeginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BEGIN, m_list);
	DDX_Text(pDX, IDE_BEGIN_SEARCH, m_search);
}

BEGIN_MESSAGE_MAP(CBeginDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDB_BEGIN_SEARCH, &CBeginDlg::OnBnClickedBeginSearch)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BEGIN, &CBeginDlg::OnNMDblclkListBegin)
	ON_COMMAND(IDM_QUIT, &CBeginDlg::OnQuit)
	ON_COMMAND(IDM_SELL_SELECT, &CBeginDlg::OnSellSelect)
	ON_COMMAND(IDM_WORKER_INFO, &CBeginDlg::OnWorkerInfo)
	ON_COMMAND(IDM_BUSSI_INFO, &CBeginDlg::OnBussiInfo)
	ON_COMMAND(IDM_STORE_INFO, &CBeginDlg::OnStoreInfo)
	ON_COMMAND(IDM_RECORD_SELL, &CBeginDlg::OnRecordSell)
	ON_COMMAND(IDM_RECORD_UPDATE, &CBeginDlg::OnRecordUpdate)
	ON_COMMAND(IDM_UPDATE_DRUG, &CBeginDlg::OnUpdateDrug)
	ON_COMMAND(IDM_PAST_REGISTER, &CBeginDlg::OnPastRegister)
	ON_COMMAND(IDM_RECORD_PAST, &CBeginDlg::OnRecordPast)
	ON_COMMAND(IDM_BACKUP_REC, &CBeginDlg::OnBackupRec)
END_MESSAGE_MAP()


// CBeginDlg ��Ϣ�������

BOOL CBeginDlg::OnInitDialog()
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
	m_list.InsertColumn(0, _T("��׼�ĺ�"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(1, _T("ҩƷ����"), LVCFMT_CENTER, 110);
	m_list.InsertColumn(2, _T("ҩƷ��Ч"), LVCFMT_CENTER, 430);
	m_list.InsertColumn(3, _T("ҩƷ����"), LVCFMT_CENTER, 65);
	//m_list.SetBkColor(RGB(26, 231, 151));
	//m_list.SetTextBkColor(RGB(26, 231, 151));
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBeginDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBeginDlg::OnPaint()
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
HCURSOR CBeginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBeginDlg::PreInitDialog()
{
	// TODO: �ڴ����ר�ô����/����û���
	CLoginDlg dlg;
	dlg.DoModal();
	CDialog::PreInitDialog();
}

// ������ť��Ӧ
void CBeginDlg::OnBnClickedBeginSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);
	// ��ǿģ����ѯԴ�ڴˣ���ٶ�ƥ��
	m_search.Replace(_T(" "), _T("%"));

	setDrug.m_strFilter = _T("name like '%");
	setDrug.m_strFilter += m_search;
	setDrug.m_strFilter += _T("%'"); 

	setDrug.m_strFilter += _T(" or ");

	setDrug.m_strFilter += _T("code like '%");
	setDrug.m_strFilter += m_search;
	setDrug.m_strFilter += _T("%'"); 

	setDrug.m_strFilter += _T(" or ");

	setDrug.m_strFilter += _T("efficacy like '%");
	setDrug.m_strFilter += m_search;
	setDrug.m_strFilter += _T("%'"); 

	setDrug.m_strFilter += _T(" or ");

	setDrug.m_strFilter += _T("ingredient like '%");
	setDrug.m_strFilter += m_search;
	setDrug.m_strFilter += _T("%'"); 
	
	if (!setDrug.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
	
	m_list.DeleteAllItems();
	if(setDrug.IsEOF())                           
		MessageBox(_T("�޿����Ϣ"), 
		_T("��ʾ"), MB_OK);
	else
	{
		CString str;
		for(int i=0; !setDrug.IsEOF(); i++,setDrug.MoveNext())
		{
			setDrug.m_code.TrimRight();
			m_list.InsertItem(i, setDrug.m_code);
			setDrug.m_name.TrimRight();
			m_list.SetItemText(i, 1, setDrug.m_name);
			setDrug.m_efficacy.TrimRight();
			m_list.SetItemText(i, 2, setDrug.m_efficacy);
			str.Format(_T("%.2f"), setDrug.m_selPrice);
			m_list.SetItemText(i, 3, str);
		}
	}
	setDrug.Close();
	GetDlgItem(IDE_BEGIN_SEARCH)->SetFocus();
	SendDlgItemMessage(IDE_BEGIN_SEARCH, EM_SETSEL, 0, -1);
	// ������������ѡ�з����´β���
}

// ˫���б������Ӧ
void CBeginDlg::OnNMDblclkListBegin(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int n=m_list.GetSelectionMark();
	if (n >= 0){
		CSellDlg dlg;

		dlg.m_csOp.Format(_T("code = '%s'"),m_list.GetItemText(n,0));
		
		dlg.DoModal();
	}
	else
	{
		MessageBox(_T("�޿����Ϣ�򵥻�ѡ��ҩƷ��׼�ĺ�"), 
			_T("��ʾ"), MB_OK);
	}
	*pResult = 0;
}
// �˵����˳���Ӧ
void CBeginDlg::OnQuit()
{
	// TODO: �ڴ���������������
	PostQuitMessage(0);
}

void CBeginDlg::OnSellSelect()
{
	// TODO: �ڴ���������������
	int n=m_list.GetSelectionMark();
	if (n >= 0){
		CSellDlg dlg;

		dlg.m_csOp.Format(_T("code = '%s'"),m_list.GetItemText(n,0));

		dlg.DoModal();
	}
	else
	{
		MessageBox(_T("�޿����Ϣ�򵥻�ѡ��ҩƷ��׼�ĺ�"), 
			_T("��ʾ"), MB_OK);
	}
}

void CBeginDlg::OnWorkerInfo()
{
	// TODO: �ڴ���������������
	CWorkerDlg dlg;
	dlg.DoModal();
}

void CBeginDlg::OnBussiInfo()
{
	// TODO: �ڴ���������������
	CBussiInfoDlg dlg;
	dlg.DoModal();
}

void CBeginDlg::OnStoreInfo()
{
	// TODO: �ڴ���������������
	CStoreInfoDlg dlg;
	dlg.DoModal();
}

void CBeginDlg::OnRecordSell()
{
	// TODO: �ڴ���������������
	CRecordSellDlg dlg;
	dlg.DoModal();
}



void CBeginDlg::OnUpdateDrug()
{
	// TODO: �ڴ���������������
	CUpdateDlg dlg;
	dlg.DoModal();
}

void CBeginDlg::OnRecordUpdate()
{
	// TODO: �ڴ���������������
	CRecordUpDlg dlg;
	dlg.DoModal();

}

void CBeginDlg::OnPastRegister()
{
	// TODO: �ڴ���������������
	CPastDrugDlg dlg;
	dlg.DoModal();
}


void CBeginDlg::OnRecordPast()
{
	// TODO: �ڴ���������������
	CRecordPastDlg dlg;
	dlg.DoModal();

}

void CBeginDlg::OnBackupRec()
{
	// TODO: �ڴ���������������
	CBackRecoDlg dlg;
	dlg.DoModal();
}


// �����ж��Ƿ��п�ݼ�����
BOOL CBeginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	// IsCTRLPressed()Ϊ�궨��
	if (pMsg->message==WM_KEYDOWN && IsCTRLPressed())
	{
		switch (pMsg->wParam)
		{
		case 'U':
			PostMessage(WM_COMMAND, IDM_UPDATE_DRUG);
			// ����֮������PostMessage ����Ϊ���������ַ�������ִ���
			// sendmessage �� ֱ�ӵ��� onUpdateDrug()
			// �ڶԻ������ʱ�������������Ϊϵͳ��û����Ҫ��Ӧ����Ϣ�������ֱ�ӵ��öԻ�����
			break;
		case 'S':
			PostMessage(WM_COMMAND, IDM_SELL_SELECT);
			break;
		case 'P':
			PostMessage(WM_COMMAND, IDM_PAST_REGISTER);
			break;
		case 'E':
			PostMessage(WM_COMMAND, IDM_RECORD_SELL);
			break;
		case 'D':
			PostMessage(WM_COMMAND, IDM_RECORD_UPDATE);
			break;
		case 'A':
			PostMessage(WM_COMMAND, IDM_RECORD_PAST);
			break;
		default:
			break;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

