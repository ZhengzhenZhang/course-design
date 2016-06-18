// UpdateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Begin.h"
#include "UpdateDlg.h"
#include "DtlDrugSet.h"
#include "LoginDlg.h"


// CUpdateDlg 对话框

IMPLEMENT_DYNAMIC(CUpdateDlg, CDialog)

CUpdateDlg::CUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateDlg::IDD, pParent)
	, m_search(_T("批准文号"))
	, m_code(_T(""))
	, m_name(_T(""))
	, m_specification(_T(""))
	, m_efficacy(_T(""))
	, m_ingredient(_T(""))
	, m_dosage(_T(""))
	, m_counts(0)
	, m_selPrice(0)
	, m_num(_T(""))
	, m_tmpCounts(0)
	, m_tmpNum(0)
	, m_ifStore(FALSE)
	, m_tmpPrice(0)
	, m_ifUpdate(FALSE)
	, m_newCode(_T("修改新文号"))
{

}

CUpdateDlg::~CUpdateDlg()
{
}

void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDE_UPDATE_SEARCH, m_search);
	DDX_Text(pDX, IDE_UPDATE_CODE, m_code);
	DDX_Text(pDX, IDE_UPDATE_NAME, m_name);
	DDX_Text(pDX, IDE_UPDATE_SPEC, m_specification);
	DDX_Text(pDX, IDE_UPDATE_EFF, m_efficacy);
	DDX_Text(pDX, IDE_UPDATE_INGDNT, m_ingredient);
	DDX_Text(pDX, IDE_UPDATE_DOSAGE, m_dosage);
	DDX_Text(pDX, IDE_UPDATE_COUNTS, m_counts);
	DDX_Text(pDX, IDE_UPDATE_SPRICE, m_selPrice);
	DDX_Text(pDX, IDE_UPDATE_NUM, m_num);
	DDX_Text(pDX, IDE_UPDATE_NEWCODE, m_newCode);
	DDX_Control(pDX, IDE_UPDATE_NEWCODE, m_CNewCode);
	DDX_Control(pDX, IDE_UPDATE_SEARCH, m_CSearch);
	DDX_Control(pDX, IDE_UPDATE_SPRICE, m_CSelPrice);
}


BEGIN_MESSAGE_MAP(CUpdateDlg, CDialog)
	ON_EN_UPDATE(IDE_UPDATE_SEARCH, &CUpdateDlg::OnEnUpdateUpdateSearch)
	ON_BN_CLICKED(IDOK, &CUpdateDlg::OnBnClickedOk)
	ON_EN_UPDATE(IDE_UPDATE_NUM, &CUpdateDlg::OnEnUpdateUpdateNum)
END_MESSAGE_MAP()


// CUpdateDlg 消息处理程序

BOOL CUpdateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (m_ifStore)
	{
		//MessageBox(m_code);
		UpdateData(FALSE);
		OnEnUpdateUpdateSearch();
	}
	
	GetDlgItem(IDE_UPDATE_SEARCH)->SetFocus();
	SendDlgItemMessage(IDE_UPDATE_SEARCH, EM_SETSEL, 0, -1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CUpdateDlg::OnEnUpdateUpdateSearch()
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
		m_tmpCounts = m_counts;	// 保存原有的信息
		m_tmpPrice = m_selPrice;
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
		m_tmpPrice = 0;
		m_counts = 0;
		m_tmpCounts = 0;
		m_num = _T("");

		m_ifUpdate = FALSE;		// 数据库中无此文号
		UpdateData(FALSE);
	}
	setDtl.Close();
	UpdateData(FALSE);
}

void CUpdateDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// 提示如果文号框为空，则判定为无更新，询问是否放弃更新，如果确定就退出
	if (m_search == _T("") || m_search == _T("批准文号"))
	{
		if (IDOK != MessageBox(_T("\n        无更新！\n"), _T("提示"),MB_OKCANCEL))
		{
			GetDlgItem(IDE_UPDATE_SEARCH)->SetFocus();
			SendDlgItemMessage(IDE_UPDATE_SEARCH, EM_SETSEL, 0, -1);
			return;
		}
		else
		{
			//OnOK();
			return;
		}
	}
	CString cs;
	UpdateData(TRUE);
	
	if (m_ifUpdate)	// 如果是更新的信息则先删除此条数据库再加入
	{
		cs.Format(_T("原文号“%s” 新文号“%s”\n\n《%s》更新数量 %s 更新后库存 %d\n\n原价 %.2f  现价 %.2f"), 
			m_code, m_newCode, m_name, m_num, m_counts, m_tmpPrice, m_selPrice);
		if (IDOK != MessageBox(cs, _T("提示"),MB_OKCANCEL))
		{
			GetDlgItem(IDE_UPDATE_NUM)->SetFocus();
			SendDlgItemMessage(IDE_UPDATE_NUM, EM_SETSEL, 0, -1);
			return;
		}
		CDatabase db;
		if (!db.Open(_T("医药进销存数据库")))
			MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
		cs.Format(_T("delete from 库存量 where code = '%s'"),
			m_code);
		db.ExecuteSQL(cs);
		CString m_tmpCs = m_code;	// 临时保留m_code 信息，下面修改药品信息还会用到
		if (m_newCode!=_T("修改新文号") && m_newCode!=_T(""))
		{
			m_code = m_newCode;
		}
		cs.Format(_T("insert into 库存量 values('%s', '%d')"),
			m_code, m_counts);
		db.ExecuteSQL(cs);

		m_code = m_tmpCs;
		cs.Format(_T("delete from 药品信息 where code = '%s'"),
			m_code);
		db.ExecuteSQL(cs);

		if (m_newCode!=_T("修改新文号") && m_newCode!=_T(""))
			m_code = m_newCode;
		cs.Format(_T("insert into 药品信息 values('%s', '%s', '%s', '%s', '%s', '%s', '%.2f')"),
			m_code, m_name, m_specification, m_efficacy, m_ingredient, m_dosage, m_selPrice);
		db.ExecuteSQL(cs);
		// m_code = m_tmpCs; // 这里不能回复m_code 如果已经更新则已新编号加入更新记录，在下面
		db.Close();
	}
	else 
	{
		cs.Format(_T("添加新药品《%s》%s 件 更新后库存 %d\n\n报价 %.2f 元"), 
			m_name, m_num, m_counts, m_selPrice);
		if (IDOK != MessageBox(cs, _T("请确保文号正确"),MB_OKCANCEL))
		{
			GetDlgItem(IDE_UPDATE_NUM)->SetFocus();
			SendDlgItemMessage(IDE_UPDATE_NUM, EM_SETSEL, 0, -1);
			return;
		}
		CDatabase db;
		if (!db.Open(_T("医药进销存数据库")))
			MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
		
		// 要注意这里m_search 为搜索框的文号，code为搜索框后面的文号，添加新药品必须为搜索框内容
		cs.Format(_T("insert into 药品信息 values('%s', '%s', '%s', '%s', '%s', '%s', '%.2f')"),
			m_search, m_name, m_specification, m_efficacy, m_ingredient, m_dosage, m_selPrice);
		db.ExecuteSQL(cs);

		cs.Format(_T("insert into 库存量 values('%s', '%d')"),
			m_search, m_counts);
		db.ExecuteSQL(cs);
		
		db.Close();
	}
	//if (m_counts != m_tmpCounts || m_ifUpdate)
	//{
	// 上面已经判定是否真的更新，这里加上反而会出现提示不符
	AddUpdateRecord();
	MessageBox(_T("更新成功"), _T("提示"), MB_OK);
	// 更新完后用户有可能继续更新为了用户方便重新初始化
	m_search = _T("");
	m_code = _T("");
	m_name = _T("");
	m_specification = _T("");
	m_efficacy = _T("");
	m_ingredient = _T("");
	m_dosage = _T("");
	m_selPrice = 0;
	m_tmpPrice = 0;
	m_counts = 0;
	m_tmpCounts = 0;
	m_num = _T("");
	m_newCode = _T("修改新文号");

	m_ifUpdate = FALSE;		// 数据库中无此文号
	UpdateData(FALSE);
	GetDlgItem(IDE_UPDATE_SEARCH)->SetFocus();
	SendDlgItemMessage(IDE_UPDATE_SEARCH, EM_SETSEL, 0, -1);
	/*}
	
	else
	{
		MessageBox(_T("无更新或库存为零"), _T("提示"), MB_OK);
		GetDlgItem(IDE_UPDATE_NUM)->SetFocus();
		SendDlgItemMessage(IDE_UPDATE_NUM, EM_SETSEL, 0, -1);
		OnEnUpdateUpdateSearch();
	}
	*/

	//OnOK();
}

extern CString login_ID;
void CUpdateDlg::AddUpdateRecord()
{
	CDatabase db;
	if (!db.Open(_T("医药进销存数据库")))
		MessageBox(_T("连接数据库时错误"), _T("提示"), MB_OK);
	COleDateTime date;
	date = COleDateTime::GetCurrentTime();

	CString time;
	time.Format(_T("%d-%d-%d %d:%d:%d"), 
		date.GetYear(), date.GetMonth(), date.GetDay(),
		date.GetHour(), date.GetMinute(), date.GetSecond());
	//MessageBox(time);
	CString cs;
	//UpdateData(TRUE);
	// 判断是修改还是新增药品
	if (m_ifUpdate)
	{
		cs.Format(_T("insert into 更新信息 values('%s', '%s', '%d', '%d', '%.2f', '%s', '修')"),
			time, m_code, m_tmpNum, m_counts, m_selPrice, login_ID);
	}
	else
	{
		cs.Format(_T("insert into 更新信息 values('%s', '%s', '%d', '%d', '%.2f', '%s', '新')"),
			time, m_search, m_tmpNum, m_counts, m_selPrice, login_ID);
	}
	
	db.ExecuteSQL(cs);
	db.Close();
}


void CUpdateDlg::OnEnUpdateUpdateNum()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数，将 EM_SETEVENTMASK 消息发送到控件，
	// 同时将 ENM_UPDATE 标志“或”运算到 lParam 掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_tmpNum = 0;
	m_tmpNum = _wtoi(m_num);	// 使用的UNICODE字符

	// 库存永远不能为负,所以下面一段防止库存出现负数情况
	if (m_tmpNum+m_tmpCounts < 0) 
	{
		m_num = _T("");
		m_counts = m_tmpCounts;
		UpdateData(FALSE);
		return;
	}
	m_counts = m_tmpCounts;
	m_counts += m_tmpNum;
	UpdateData(FALSE);
}

// 为实现单击全选编辑框内容专门调用的截取消息函数
BOOL CUpdateDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	// 这里面只能用PostMessage 发送消息，放到消息队列中
	if (pMsg->message==WM_LBUTTONDOWN)
	{
		if(pMsg->hwnd == m_CNewCode.m_hWnd)
		{
			GetDlgItem(IDE_UPDATE_NEWCODE)->PostMessage(EM_SETSEL, 0, -1);
		}
		if (pMsg->hwnd == m_CSearch.m_hWnd)
		{
			GetDlgItem(IDE_UPDATE_SEARCH)->PostMessage(EM_SETSEL, 0, -1);

		}
		if (pMsg->hwnd == m_CSelPrice.m_hWnd)
		{
			GetDlgItem(IDE_UPDATE_SPRICE)->PostMessage(EM_SETSEL, 0, -1);
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
