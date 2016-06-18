// SellDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Begin.h"
#include "SellDlg.h"
#include "DtlDrugSet.h"
#include "LoginDlg.h"


// CSellDlg �Ի���

IMPLEMENT_DYNAMIC(CSellDlg, CDialog)

CSellDlg::CSellDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSellDlg::IDD, pParent)
	, m_code(_T(""))
	, m_name(_T(""))
	, m_specification(_T(""))
	, m_efficacy(_T(""))
	, m_ingredient(_T(""))
	, m_dosage(_T(""))
	, m_selPrice(0)
	, m_counts(0)
	, m_num(0)
	, m_totalPrice(0)
	, m_csOp(_T(""))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDE_SELL_CODE, m_code);
	DDX_Text(pDX, IDE_SELL_NAME, m_name);
	DDX_Text(pDX, IDE_SELL_SPEC, m_specification);
	DDX_Text(pDX, IDE_SELL_EFF, m_efficacy);
	DDX_Text(pDX, IDE_SELL_INGDNT, m_ingredient);
	DDX_Text(pDX, IDE_SELL_DOSAGE, m_dosage);
	DDX_Text(pDX, IDE_SELL_SPRICE, m_selPrice);
	DDX_Text(pDX, IDE_SELL_COUNTS, m_counts);
	DDX_Text(pDX, IDE_SELL_NUM, m_num);
	DDX_Text(pDX, IDE_SELL_TOTALP, m_totalPrice);
}


BEGIN_MESSAGE_MAP(CSellDlg, CDialog)
	ON_EN_UPDATE(IDE_SELL_NUM, &CSellDlg::OnEnUpdateSellNum)
	ON_BN_CLICKED(IDOK, &CSellDlg::OnBnClickedOk)
//	ON_EN_ERRSPACE(IDE_SELL_NUM, &CSellDlg::OnEnErrspaceSellNum)
END_MESSAGE_MAP()


// CSellDlg ��Ϣ�������

BOOL CSellDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CDtlDrugSet setDtl;
	setDtl.m_strFilter = m_csOp;
	if (!setDtl.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
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
	
	setDtl.Close();
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSellDlg::OnEnUpdateSellNum()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// �������� EM_SETEVENTMASK ��Ϣ���͵��ؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_num > (UINT)m_counts)
	{
		MessageBox(_T("��治��"), _T("��ʾ"), MB_OK);
		m_num = 0;
		m_totalPrice = m_selPrice * m_num;
		UpdateData(FALSE);
		SendDlgItemMessage(IDE_SELL_NUM, EM_SETSEL, 0, -1);
		return;
	}
	m_totalPrice = m_selPrice * m_num;
	CString tcs;
	GetDlgItem(IDE_SELL_NUM)->GetWindowText(tcs);
	if (tcs == _T(""))		// ����һ���ֻΪʵ�ְѱ༭������ȫѡ���Ա����Աʹ��
	{
		m_num = 0;
		UpdateData(FALSE);
		GetDlgItem(IDE_SELL_NUM)->SetFocus();
		SendDlgItemMessage(IDE_SELL_NUM, EM_SETSEL, 0, -1);
		return;
	}
	
	UpdateData(FALSE);
}

void CSellDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString cs;
	
	cs.Format(_T("��%s�� �۳� %d ʣ�� %d"), m_name, m_num, m_counts-m_num);
	if (IDOK != MessageBox(cs, _T("��ʾ"),MB_OKCANCEL))
	{
		GetDlgItem(IDE_SELL_NUM)->SetFocus();
		SendDlgItemMessage(IDE_SELL_NUM, EM_SETSEL, 0, -1);
		return;
	}
	CDatabase db;
	if (!db.Open(_T("ҽҩ���������ݿ�")))
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
	
	UpdateData(TRUE);
	cs.Format(_T("update ����� set counts='%d' where code='%s'"),
		m_counts-m_num, m_code);
	db.ExecuteSQL(cs);
	db.Close();
	if (m_num > 0)
		AddSellRecord();
	OnOK();
}

// ������ۼ�¼
extern CString login_ID;
void CSellDlg::AddSellRecord()
{
	CDatabase db;
	if (!db.Open(_T("ҽҩ���������ݿ�")))
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
	COleDateTime date;
	date = COleDateTime::GetCurrentTime();

	CString time;
	time.Format(_T("%d-%d-%d %d:%d:%d"), 
		date.GetYear(), date.GetMonth(), date.GetDay(),
		date.GetHour(), date.GetMinute(), date.GetSecond());
	//MessageBox(time);
	CString cs;
	UpdateData(TRUE);
	//MessageBox(login_ID);
	cs.Format(_T("insert into ���ۼ�¼ values('%s', '%s', '%d', '%.2f', '%s')"),
		time, m_code, m_num, m_totalPrice, login_ID);
	db.ExecuteSQL(cs);
	db.Close();
}

