// PastDrugDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Begin.h"
#include "PastDrugDlg.h"
#include "DtlDrugSet.h"
#include "LoginDlg.h"


// CPastDrugDlg �Ի���

IMPLEMENT_DYNAMIC(CPastDrugDlg, CDialog)

CPastDrugDlg::CPastDrugDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPastDrugDlg::IDD, pParent)
	, m_search(_T("��׼�ĺ�"))
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


// CPastDrugDlg ��Ϣ�������

void CPastDrugDlg::OnEnUpdatePastSearch()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// �������� EM_SETEVENTMASK ��Ϣ���͵��ؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�
	
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	CDtlDrugSet setDtl;
	setDtl.m_strFilter = _T("code like '%");
	setDtl.m_strFilter += m_search;
	setDtl.m_strFilter += _T("%'");
	if (!setDtl.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);

	if (!setDtl.IsEOF() && m_search != _T(""))	// ��Ϊ��ģ������������������Ϊ��
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

		m_ifUpdate = TRUE;		// ���ݿ���������
		//m_tmpCounts = m_counts;	// ����ԭ�е���Ϣ
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
		
		m_ifUpdate = FALSE;		// ���ݿ����޴��ĺ�
		
		//m_tmpPrice = 0;
		//m_tmpCounts = 0;

		UpdateData(FALSE);
	}
	setDtl.Close();
	UpdateData(FALSE);
}

void CPastDrugDlg::OnEnUpdatePastNum()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// �������� EM_SETEVENTMASK ��Ϣ���͵��ؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_num > (UINT)m_counts)
	{
		MessageBox(_T("�޸�����"), _T("��ʾ"), MB_OK);
		m_num = 0;
		m_totalPrice = m_selPrice * m_num;
		UpdateData(FALSE);
		SendDlgItemMessage(IDE_PAST_NUM, EM_SETSEL, 0, -1);
		return;
	}
	m_totalPrice = m_selPrice * m_num;
	CString tcs;
	GetDlgItem(IDE_PAST_NUM)->GetWindowText(tcs);
	if (tcs == "")		// ����һ���ֻΪʵ�ְѱ༭������ȫѡ���Ա����Աʹ��
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
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString cs;

	cs.Format(_T("����%s��%d�� ʣ�� %d"), m_name, m_num, m_counts-m_num);
	if (IDOK != MessageBox(cs, _T("��ʾ"),MB_OKCANCEL))
	{
		GetDlgItem(IDE_PAST_NUM)->SetFocus();
		SendDlgItemMessage(IDE_PAST_NUM, EM_SETSEL, 0, -1);
		return;
	}
	CDatabase db;
	if (!db.Open(_T("ҽҩ���������ݿ�")))

	UpdateData(TRUE);
	cs.Format(_T("update ����� set counts='%d' where code='%s'"),
		m_counts-m_num, m_code);
	db.ExecuteSQL(cs);
	db.Close();

	if (m_num > 0)
	{
		AddSellRecord();
		MessageBox(_T("����ɹ�"), _T("��ʾ"), MB_OK);
		// ��������û��п��ܼ�������Ϊ���û��������³�ʼ��
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
		m_ifUpdate = FALSE;		// ���ݿ����޴��ĺ�
		m_pastTime = COleDateTime::GetCurrentTime();
		UpdateData(FALSE);
		GetDlgItem(IDE_PAST_SEARCH)->SetFocus();
		SendDlgItemMessage(IDE_PAST_SEARCH, EM_SETSEL, 0, -1);
	}
	else
	{
		MessageBox(_T("�޴���"), _T("��ʾ"), MB_OK);
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
	if (!db.Open(_T("ҽҩ���������ݿ�")))
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
	COleDateTime date;
	date = COleDateTime::GetCurrentTime();
	CString time, pTime;	// ����ʱ��͹���ʱ��
	time.Format(_T("%d-%d-%d %d:%d:%d"), 
		date.GetYear(), date.GetMonth(), date.GetDay(),
		date.GetHour(), date.GetMinute(), date.GetSecond());
	
	pTime.Format(_T("%d-%d-%d %d:%d:%d"), 
		m_pastTime.GetYear(), m_pastTime.GetMonth(), m_pastTime.GetDay(),
		m_pastTime.GetHour(), m_pastTime.GetMinute(), m_pastTime.GetSecond());

	CString cs;
	cs.Format(_T("insert into ����ҩƷ���� values('%s', '%s', '%s', '%d', '%.2f', '%s', '%s')"),
		time, m_code, pTime, m_num, m_totalPrice, m_mark, login_ID);
	db.ExecuteSQL(cs);
	db.Close();
}

