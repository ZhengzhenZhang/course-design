// PastDrugDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Begin.h"
#include "PastDrugDlg.h"
#include "DtlDrugSet.h"
#include "LoginDlg.h"


// CPastDrugDlg 对话框

IMPLEMENT_DYNAMIC(CPastDrugDlg, CDialog)

CPastDrugDlg::CPastDrugDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPastDrugDlg::IDD, pParent)
	, m_search(_T("批准文号"))
	, m_code(_T(""))
	, m_name(_T(""))
	, m_totalPrice(0)
	, m_pastTime(COleDateTime::GetCurrentTime())
	, m_num(0)
	, m_counts(0)
	, m_specification(_T(""))
	, m_ingredient(_T(""))
	, m_efficacy(_T(""))
	, m_dosage(_T(""))
	, m_selPrice(0)
	, m_ifUpdate(FALSE)
	, m_mark(_T(""))
{

}

CPastDrugDlg::~CPastDrugDlg()
{
}

void CPastDrugDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDE_PAST_SEARCH, m_search);
	DDX_Text(pDX, IDE_PAST_CODE, m_code);
	DDX_Text(pDX, IDE_PAST_NAME, m_name);
	DDX_Text(pDX, IDE_PAST_TOTALV, m_totalPrice);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, m_pastTime);
	DDX_Text(pDX, IDE_PAST_NUM, m_num);
	DDX_Text(pDX, IDE_PAST_COUNTS, m_counts);
	DDX_Text(pDX, IDE_PAST_SPEC, m_specification);
	DDX_Text(pDX, IDE_PAST_INGDNT, m_ingredient);
	DDX_Text(pDX, IDE_PAST_EFF, m_efficacy);
	DDX_Text(pDX, IDE_PAST_DOSAGE, m_dosage);
	DDX_Text(pDX, IDE_PAST_SPRICE, m_selPrice);
	DDX_Control(pDX, IDE_PAST_SEARCH, m_CSearch);
	DDX_Control(pDX, IDE_PAST_NUM, m_CNum);
	DDX_Text(pDX, IDE_PAST_MARK, m_mark);
}


BEGIN_MESSAGE_MAP(CPastDrugDlg, CDialog)
	ON_EN_UPDATE(IDE_PAST_SEARCH, &CPastDrugDlg::OnEnUpdatePastSearch)
	ON_EN_UPDATE(IDE_PAST_NUM, &CPastDrugDlg::OnEnUpdatePastNum)
	ON_BN_CLICKED(IDOK, &CPastDrugDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPastDrugDlg 消息处理程序

void CPastDrugDlg::OnEnUpdatePastSearch()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数，将 EM_SETEVENTMASK 消息发送到控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。
	
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CDtlDrugSet setDtl;
	setDtl.m_strFilter = _T("code like '%");
	setDtl.m_strFilter += m_search;
	setDtl.m_strFilter += _T("%'");
	if (!setDtl.Open())
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);

	if (!setDtl.IsEOF() && m_search != _T(""))	// 因为是模糊搜索所以搜索框不能为空
	{
		setDtl.m_code.TrimRight();
		m_code = setDtl.m_code;
		setDtl.m_name.TrimRight();
		m_name = setDtl.m_name;
		setDtl.m_specification.TrimRight();
		m_specification = setDtl.m_specification;
		setDtl.m_efficacy.TrimRight();
		m_efficacy = setDtl.m_efficacy;
		setDtl.m_ingredient.TrimRight();
		m_ingredient = setDtl.m_ingredient;
		setDtl.m_dosage.TrimRight();
		m_dosage = setDtl.m_dosage;

		m_selPrice = setDtl.m_selPrice;
		m_counts = setDtl.m_counts;	

		m_ifUpdate = TRUE;		// 数据库中有数据
		//m_tmpCounts = m_counts;	// 保存原有的信息
		//m_tmpPrice = m_selPrice;
	}
	else
	{
		m_code = _T("");
		m_name = _T("");
		m_specification = _T("");
		m_efficacy = _T("");
		m_ingredient = _T("");
		m_dosage = _T("");
		m_selPrice = 0;
		m_counts = 0;
		m_mark = _T("");
		m_num = 0;
		
		m_ifUpdate = FALSE;		// 数据库中无此文号
		
		//m_tmpPrice = 0;
		//m_tmpCounts = 0;

		UpdateData(FALSE);
	}
	setDtl.Close();
	UpdateData(FALSE);
}

void CPastDrugDlg::OnEnUpdatePastNum()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数，将 EM_SETEVENTMASK 消息发送到控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_num > (UINT)m_counts)
	{
		MessageBox(_T("无更多库存"), _T("提示"), MB_OK);
		m_num = 0;
		m_totalPrice = m_selPrice * m_num;
		UpdateData(FALSE);
		SendDlgItemMessage(IDE_PAST_NUM, EM_SETSEL, 0, -1);
		return;
	}
	m_totalPrice = m_selPrice * m_num;
	CString tcs;
	GetDlgItem(IDE_PAST_NUM)->GetWindowText(tcs);
	if (tcs == "")		// 上下一大堆只为实现把编辑框内容全选，以便操作员使用
	{
		m_num = 0;
		UpdateData(FALSE);
		GetDlgItem(IDE_PAST_NUM)->SetFocus();
		SendDlgItemMessage(IDE_PAST_NUM, EM_SETSEL, 0, -1);
		return;
	}

	UpdateData(FALSE);
}

BOOL CPastDrugDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message==WM_LBUTTONDOWN)
	{
		if (pMsg->hwnd == m_CSearch.m_hWnd)
		{
			GetDlgItem(IDE_PAST_SEARCH)->PostMessage(EM_SETSEL, 0, -1);

		}
		if (pMsg->hwnd == m_CNum.m_hWnd)
		{
			GetDlgItem(IDE_PAST_NUM)->PostMessage(EM_SETSEL, 0, -1);
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CPastDrugDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString cs;

	cs.Format(_T("处理《%s》%d件 剩余 %d"), m_name, m_num, m_counts-m_num);
	if (IDOK != MessageBox(cs, _T("提示"),MB_OKCANCEL))
	{
		GetDlgItem(IDE_PAST_NUM)->SetFocus();
		SendDlgItemMessage(IDE_PAST_NUM, EM_SETSEL, 0, -1);
		return;
	}
	CDatabase db;
	if (!db.Open(_T("医药进销存数据库")))

	UpdateData(TRUE);
	cs.Format(_T("update 库存量 set counts='%d' where code='%s'"),
		m_counts-m_num, m_code);
	db.ExecuteSQL(cs);
	db.Close();

	if (m_num > 0)
	{
		AddSellRecord();
		MessageBox(_T("处理成功"), _T("提示"), MB_OK);
		// 更新完后用户有可能继续更新为了用户方便重新初始化
		m_search = _T("");
		m_code = _T("");
		m_name = _T("");
		m_specification = _T("");
		m_efficacy = _T("");
		m_ingredient = _T("");
		m_dosage = _T("");
		m_selPrice = 0;
		m_counts = 0;
		m_mark = _T("");
		m_num = 0;
		m_ifUpdate = FALSE;		// 数据库中无此文号
		m_pastTime = COleDateTime::GetCurrentTime();
		UpdateData(FALSE);
		GetDlgItem(IDE_PAST_SEARCH)->SetFocus();
		SendDlgItemMessage(IDE_PAST_SEARCH, EM_SETSEL, 0, -1);
	}
	else
	{
		MessageBox(_T("无处理"), _T("提示"), MB_OK);
		GetDlgItem(IDE_PAST_NUM)->SetFocus();
		SendDlgItemMessage(IDE_PAST_NUM, EM_SETSEL, 0, -1);
	}
	
	//OnOK();
}

extern CString login_ID;
void CPastDrugDlg::AddSellRecord()
{
	UpdateData(TRUE);

	CDatabase db;
	if (!db.Open(_T("医药进销存数据库")))
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
	COleDateTime date;
	date = COleDateTime::GetCurrentTime();
	CString time, pTime;	// 现在时间和过期时间
	time.Format(_T("%d-%d-%d %d:%d:%d"), 
		date.GetYear(), date.GetMonth(), date.GetDay(),
		date.GetHour(), date.GetMinute(), date.GetSecond());
	
	pTime.Format(_T("%d-%d-%d %d:%d:%d"), 
		m_pastTime.GetYear(), m_pastTime.GetMonth(), m_pastTime.GetDay(),
		m_pastTime.GetHour(), m_pastTime.GetMinute(), m_pastTime.GetSecond());

	CString cs;
	cs.Format(_T("insert into 过期药品处理 values('%s', '%s', '%s', '%d', '%.2f', '%s', '%s')"),
		time, m_code, pTime, m_num, m_totalPrice, m_mark, login_ID);
	db.ExecuteSQL(cs);
	db.Close();
}

