// BeginDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CBeginDlg 对话框




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


// CBeginDlg 消息处理程序

BOOL CBeginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_list.InsertColumn(0, _T("批准文号"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(1, _T("药品名称"), LVCFMT_CENTER, 110);
	m_list.InsertColumn(2, _T("药品功效"), LVCFMT_CENTER, 430);
	m_list.InsertColumn(3, _T("药品报价"), LVCFMT_CENTER, 65);
	//m_list.SetBkColor(RGB(26, 231, 151));
	//m_list.SetTextBkColor(RGB(26, 231, 151));
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBeginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBeginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBeginDlg::PreInitDialog()
{
	// TODO: 在此添加专用代码和/或调用基类
	CLoginDlg dlg;
	dlg.DoModal();
	CDialog::PreInitDialog();
}

// 搜索按钮相应
void CBeginDlg::OnBnClickedBeginSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);
	// 超强模糊查询源于此，与百度匹敌
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
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
	
	m_list.DeleteAllItems();
	if(setDrug.IsEOF())                           
		MessageBox(_T("无库存信息"), 
		_T("提示"), MB_OK);
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
	// 把搜索框文字选中方便下次操作
}

// 双击列表框项相应
void CBeginDlg::OnNMDblclkListBegin(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int n=m_list.GetSelectionMark();
	if (n >= 0){
		CSellDlg dlg;

		dlg.m_csOp.Format(_T("code = '%s'"),m_list.GetItemText(n,0));
		
		dlg.DoModal();
	}
	else
	{
		MessageBox(_T("无库存信息或单击选中药品批准文号"), 
			_T("提示"), MB_OK);
	}
	*pResult = 0;
}
// 菜单栏退出相应
void CBeginDlg::OnQuit()
{
	// TODO: 在此添加命令处理程序代码
	PostQuitMessage(0);
}

void CBeginDlg::OnSellSelect()
{
	// TODO: 在此添加命令处理程序代码
	int n=m_list.GetSelectionMark();
	if (n >= 0){
		CSellDlg dlg;

		dlg.m_csOp.Format(_T("code = '%s'"),m_list.GetItemText(n,0));

		dlg.DoModal();
	}
	else
	{
		MessageBox(_T("无库存信息或单击选中药品批准文号"), 
			_T("提示"), MB_OK);
	}
}

void CBeginDlg::OnWorkerInfo()
{
	// TODO: 在此添加命令处理程序代码
	CWorkerDlg dlg;
	dlg.DoModal();
}

void CBeginDlg::OnBussiInfo()
{
	// TODO: 在此添加命令处理程序代码
	CBussiInfoDlg dlg;
	dlg.DoModal();
}

void CBeginDlg::OnStoreInfo()
{
	// TODO: 在此添加命令处理程序代码
	CStoreInfoDlg dlg;
	dlg.DoModal();
}

void CBeginDlg::OnRecordSell()
{
	// TODO: 在此添加命令处理程序代码
	CRecordSellDlg dlg;
	dlg.DoModal();
}



void CBeginDlg::OnUpdateDrug()
{
	// TODO: 在此添加命令处理程序代码
	CUpdateDlg dlg;
	dlg.DoModal();
}

void CBeginDlg::OnRecordUpdate()
{
	// TODO: 在此添加命令处理程序代码
	CRecordUpDlg dlg;
	dlg.DoModal();

}

void CBeginDlg::OnPastRegister()
{
	// TODO: 在此添加命令处理程序代码
	CPastDrugDlg dlg;
	dlg.DoModal();
}


void CBeginDlg::OnRecordPast()
{
	// TODO: 在此添加命令处理程序代码
	CRecordPastDlg dlg;
	dlg.DoModal();

}

void CBeginDlg::OnBackupRec()
{
	// TODO: 在此添加命令处理程序代码
	CBackRecoDlg dlg;
	dlg.DoModal();
}


// 用于判断是否有快捷键按下
BOOL CBeginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	// IsCTRLPressed()为宏定义
	if (pMsg->message==WM_KEYDOWN && IsCTRLPressed())
	{
		switch (pMsg->wParam)
		{
		case 'U':
			PostMessage(WM_COMMAND, IDM_UPDATE_DRUG);
			// 这里之所以用PostMessage 是因为用另外两种方法会出现错误
			// sendmessage 和 直接调用 onUpdateDrug()
			// 在对话框结束时候出错，我想是因为系统还没吧需要相应的消息处理完就直接调用对话框了
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

