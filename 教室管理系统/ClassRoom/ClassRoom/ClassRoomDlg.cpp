// ClassRoomDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

TCHAR weekDay[] = L"日一二三四五六";		// 设置显示星期的数组

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


// CClassRoomDlg 对话框




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


// CClassRoomDlg 消息处理程序

BOOL CClassRoomDlg::OnInitDialog()
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

	m_myFont.CreatePointFont(150, _T("华文楷体"));
	m_myColor = RGB(255, 0, 255);

	CreateLayout();
	ListTBuildComboBox();
	ListThisTime();
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClassRoomDlg::OnPaint()
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
HCURSOR CClassRoomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClassRoomDlg::OnDtnCloseupDateTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CreateLayout();		// 首先对控件进行布局
	ListThisTime();		// 然后列出相应的数据
	*pResult = 0;
}

void CClassRoomDlg::OnCbnSelchangeComboTbuild()
{
	// TODO: 在此添加控件通知处理程序代码
	CreateLayout();		// 首先对控件进行布局
	ListThisTime();		// 然后列出相应的数据
}



//---------------
//---功能：主对话框中的排课信息视图布局---
//---完成人：吴稀钰---
//---完成时间：2012-12-25---
//---修改时间：---
//---------------
void CClassRoomDlg::CreateLayout()
{
	ClearList();	// 布局的时候首先清除以前的布局信息
	m_listCrInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
					// 设置扩展类型为网格和全选
	m_listCrInfo.InsertColumn(0, _T(""), LVCFMT_CENTER, 40);
	m_listCrInfo.InsertColumn(1, _T("教室编号"), LVCFMT_CENTER, 80);
	m_listCrInfo.InsertColumn(2, _T("第一大节"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(3, _T("第二大节"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(4, _T("第三大节"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(5, _T("第四大节"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(6, _T("第五大节"), LVCFMT_CENTER, 100);
}
//---------------
//---功能：教室排课信息视图布局---
//---完成人：吴稀钰---
//---完成时间：2012-12-25---
//---修改时间：---
//---------------
void CClassRoomDlg::CreateLayout2()
{
	ClearList();
	m_listCrInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_listCrInfo.InsertColumn(0, _T("星期"), LVCFMT_CENTER, 40);
	m_listCrInfo.InsertColumn(1, _T("教室编号"), LVCFMT_CENTER, 80);
	m_listCrInfo.InsertColumn(2, _T("第一大节"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(3, _T("第二大节"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(4, _T("第三大节"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(5, _T("第四大节"), LVCFMT_CENTER, 100);
	m_listCrInfo.InsertColumn(6, _T("第五大节"), LVCFMT_CENTER, 100);
}


//---------------
//---功能：清除列表视图控件中的列---
//---完成人：吴稀钰--
//---完成时间：2012-12-25---
//---修改时间：---
//---------------
void CClassRoomDlg::ClearList()
{

	m_listCrInfo.DeleteAllItems();	// 清除列的时候首先要删除原先所有的元素
	// Delete all of the columns.
	while (m_listCrInfo.DeleteColumn(0));
									// 删除列直到删除完，返回0值，退出循环
}

//---------------
//---功能：得到选定日期星期然后列出排课信息---
//---完成人：魏强---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
void CClassRoomDlg::ListThisTime()
{
	m_isSearch = FALSE;	// 起标记作用，FALSE表示用户不是单击搜索列出用户信息

	UpdateData(TRUE);	// 将控件值传递给关联变量

	m_nWeek = m_dTime.GetDayOfWeek()-1;	
	// 得到星期，0代表星期日

	CString strTmp;
	strTmp.Format(_T("星期%c"), weekDay[m_nWeek]);
	GetDlgItem(IDC_STATIC_WEEK)->SetWindowText(strTmp);

	CString strSQL;
	strSQL.Format(_T("csWeek = '%d' AND tBuildNum = '%s'"), m_nWeek, m_strComboTBuild);

	ListCSInfo(strSQL);
}

//---------------
//---功能：接收SQL条件语句列出排课信息---
//---完成人：魏强---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
void CClassRoomDlg::ListCSInfo(CString strSQL)
{
	m_listCrInfo.DeleteAllItems();
	CRecordsetCS setCS;

	setCS.m_strFilter = strSQL;

	if (!setCS.Open())
	{
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
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
//---功能：重新列出列表视图中的占用信息---
//---完成人：魏强---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
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
	CString strTime;// 首先得到时间
	GetDlgItem(IDC_DATE_TIME)->GetWindowText(strTime);
	strTime += _T("  星期");
	if (m_isSearch)
		strTime += m_listCrInfo.GetItemText(nIndex, 0);
	else
		strTime += weekDay[m_nWeek];

	// 从教室占用信息数据库中取出信心
	CRecordsetOC setOC;

	CString strSQL;
	strSQL.Format(_T("ocTime = '%s' AND cRoomNum = '%s'"), 
		strTime, myCNum);

	setOC.m_strFilter = strSQL;

	if (!setOC.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
	if (setOC.IsEOF()) {
		setOC.Close();
		return;	// 如果没有就不修改
	}
	
	CString strTmp;
	
	strTmp = m_listCrInfo.GetItemText(nIndex, 2);
	setOC.m_ocFirst.TrimRight();
	if (_T("") == strTmp && _T("") != setOC.m_ocFirst)
	{
		strTmp += _T("*");			// 对不是课程信息做特殊标记
		strTmp += setOC.m_ocFirst;
		strTmp += _T("*");
		m_listCrInfo.SetItemText(nIndex, 2, strTmp);
	}
	
	strTmp = m_listCrInfo.GetItemText(nIndex, 3);
	setOC.m_ocSecond.TrimRight();
	if (_T("") == strTmp && _T("") != setOC.m_ocSecond)
	{
		
		strTmp += _T("*");			// 对不是课程信息做特殊标记
		strTmp += setOC.m_ocSecond;
		strTmp += _T("*");
		m_listCrInfo.SetItemText(nIndex, 3, strTmp);
	}
	
	strTmp = m_listCrInfo.GetItemText(nIndex, 4);
	setOC.m_ocThird.TrimRight();
	if (_T("") == strTmp && _T("") != setOC.m_ocThird)
	{
		strTmp += _T("*");			// 对不是课程信息做特殊标记
		strTmp += setOC.m_ocThird;
		strTmp += _T("*");
		m_listCrInfo.SetItemText(nIndex, 4, strTmp);
	}
	
	strTmp = m_listCrInfo.GetItemText(nIndex, 5);
	setOC.m_ocFourth.TrimRight();
	if (_T("") == strTmp && _T("") != setOC.m_ocFourth)
	{
		strTmp += _T("*");			// 对不是课程信息做特殊标记
		strTmp += setOC.m_ocFourth;
		strTmp += _T("*");
		m_listCrInfo.SetItemText(nIndex, 5, strTmp);
	}
	
	strTmp = m_listCrInfo.GetItemText(nIndex, 6);
	setOC.m_ocFifth.TrimRight();
	if (_T("") == strTmp && _T("") != setOC.m_ocFifth)
	{
		strTmp += _T("*");			// 对不是课程信息做特殊标记
		strTmp += setOC.m_ocFifth;
		strTmp += _T("*");
		m_listCrInfo.SetItemText(nIndex, 6, strTmp);
	}
}


//---------------
//---功能：在组合框中列出教学楼编号---
//---完成人：魏强---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
void CClassRoomDlg::ListTBuildComboBox()
{
	CRecordsetTBuild setTBuild;

	if (!setTBuild.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

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
//---功能：设置字体以及颜色消息响应函数---
//---完成人：魏强---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
HBRUSH CClassRoomDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	if(pWnd->GetDlgCtrlID()==IDC_STATIC_WEEK)
	{
		pDC->SelectObject(&m_myFont);	// 设置字体
		pDC->SetTextColor(m_myColor);	// 设置颜色
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

//---------------
//---功能：搜索按钮消息响应函数---
//---完成人：魏强---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
void CClassRoomDlg::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码

	CreateLayout2();		// 切换到布局2
	m_isSearch = TRUE;		// 起标记作用，FALSE表示用户是单击搜索列出用户信息
	
	UpdateData(TRUE);		// 将控件值传递给关联变量	

	if (_T("") == m_strCRommNum)
	{
		MessageBox(_T("请输入搜索内容！"), _T("提示"), MB_OK);
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
//---功能：修改了下默认回车和ESC按键的响应---
//---完成人：魏强---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
void CClassRoomDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	OnBnClickedButtonSearch();
}
void CClassRoomDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	
	if (IDOK != MessageBox(_T("是否退出？"), _T("提示"), MB_OKCANCEL))
		return;
	CDialog::OnCancel();
}


//---------------
//---功能：双击列表视图调用新对话框---
//---完成人：魏强---
//---完成时间：2012-12-26---
//---修改时间：2012-12-28---
//---------------
void CClassRoomDlg::OnNMDblclkListCrinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	// LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CDlgDetail dlg;		// 创建一个教室信息对话框对象
	
	int n = m_listCrInfo.GetSelectionMark();
						// 得到双击的列表视图元素编号
	
	if (n >= 0 && n<m_listCrInfo.GetItemCount()) 
						// 双击的元素在列表视图中
	{
		// 初始化新对话框对象中的一些信息
		dlg.m_strDCNum = m_listCrInfo.GetItemText(n, 1);
		dlg.m_nWeek = m_nWeek;

		GetDlgItem(IDC_DATE_TIME)->GetWindowText(dlg.m_strDTime);
		dlg.m_strDTime += _T("  星期");
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
	// TODO: 在此添加专用代码和/或调用基类
	CDlgLogin dlg;

	dlg.DoModal();
	CDialog::PreInitDialog();
}
