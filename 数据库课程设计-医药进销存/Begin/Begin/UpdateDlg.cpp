// UpdateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Begin.h"
#include "UpdateDlg.h"
#include "DtlDrugSet.h"
#include "LoginDlg.h"


// CUpdateDlg �Ի���

IMPLEMENT_DYNAMIC(CUpdateDlg, CDialog)

CUpdateDlg::CUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpdateDlg::IDD, pParent)
	, m_search(_T("��׼�ĺ�"))
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
	, m_newCode(_T("�޸����ĺ�"))
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


// CUpdateDlg ��Ϣ�������

BOOL CUpdateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (m_ifStore)
	{
		//MessageBox(m_code);
		UpdateData(FALSE);
		OnEnUpdateUpdateSearch();
	}
	
	GetDlgItem(IDE_UPDATE_SEARCH)->SetFocus();
	SendDlgItemMessage(IDE_UPDATE_SEARCH, EM_SETSEL, 0, -1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CUpdateDlg::OnEnUpdateUpdateSearch()
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
		m_tmpCounts = m_counts;	// ����ԭ�е���Ϣ
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

		m_ifUpdate = FALSE;		// ���ݿ����޴��ĺ�
		UpdateData(FALSE);
	}
	setDtl.Close();
	UpdateData(FALSE);
}

void CUpdateDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ʾ����ĺſ�Ϊ�գ����ж�Ϊ�޸��£�ѯ���Ƿ�������£����ȷ�����˳�
	if (m_search == _T("") || m_search == _T("��׼�ĺ�"))
	{
		if (IDOK != MessageBox(_T("\n        �޸��£�\n"), _T("��ʾ"),MB_OKCANCEL))
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
	
	if (m_ifUpdate)	// ����Ǹ��µ���Ϣ����ɾ���������ݿ��ټ���
	{
		cs.Format(_T("ԭ�ĺš�%s�� ���ĺš�%s��\n\n��%s���������� %s ���º��� %d\n\nԭ�� %.2f  �ּ� %.2f"), 
			m_code, m_newCode, m_name, m_num, m_counts, m_tmpPrice, m_selPrice);
		if (IDOK != MessageBox(cs, _T("��ʾ"),MB_OKCANCEL))
		{
			GetDlgItem(IDE_UPDATE_NUM)->SetFocus();
			SendDlgItemMessage(IDE_UPDATE_NUM, EM_SETSEL, 0, -1);
			return;
		}
		CDatabase db;
		if (!db.Open(_T("ҽҩ���������ݿ�")))
			MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
		cs.Format(_T("delete from ����� where code = '%s'"),
			m_code);
		db.ExecuteSQL(cs);
		CString m_tmpCs = m_code;	// ��ʱ����m_code ��Ϣ�������޸�ҩƷ��Ϣ�����õ�
		if (m_newCode!=_T("�޸����ĺ�") && m_newCode!=_T(""))
		{
			m_code = m_newCode;
		}
		cs.Format(_T("insert into ����� values('%s', '%d')"),
			m_code, m_counts);
		db.ExecuteSQL(cs);

		m_code = m_tmpCs;
		cs.Format(_T("delete from ҩƷ��Ϣ where code = '%s'"),
			m_code);
		db.ExecuteSQL(cs);

		if (m_newCode!=_T("�޸����ĺ�") && m_newCode!=_T(""))
			m_code = m_newCode;
		cs.Format(_T("insert into ҩƷ��Ϣ values('%s', '%s', '%s', '%s', '%s', '%s', '%.2f')"),
			m_code, m_name, m_specification, m_efficacy, m_ingredient, m_dosage, m_selPrice);
		db.ExecuteSQL(cs);
		// m_code = m_tmpCs; // ���ﲻ�ܻظ�m_code ����Ѿ����������±�ż�����¼�¼��������
		db.Close();
	}
	else 
	{
		cs.Format(_T("�����ҩƷ��%s��%s �� ���º��� %d\n\n���� %.2f Ԫ"), 
			m_name, m_num, m_counts, m_selPrice);
		if (IDOK != MessageBox(cs, _T("��ȷ���ĺ���ȷ"),MB_OKCANCEL))
		{
			GetDlgItem(IDE_UPDATE_NUM)->SetFocus();
			SendDlgItemMessage(IDE_UPDATE_NUM, EM_SETSEL, 0, -1);
			return;
		}
		CDatabase db;
		if (!db.Open(_T("ҽҩ���������ݿ�")))
			MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
		
		// Ҫע������m_search Ϊ��������ĺţ�codeΪ�����������ĺţ������ҩƷ����Ϊ����������
		cs.Format(_T("insert into ҩƷ��Ϣ values('%s', '%s', '%s', '%s', '%s', '%s', '%.2f')"),
			m_search, m_name, m_specification, m_efficacy, m_ingredient, m_dosage, m_selPrice);
		db.ExecuteSQL(cs);

		cs.Format(_T("insert into ����� values('%s', '%d')"),
			m_search, m_counts);
		db.ExecuteSQL(cs);
		
		db.Close();
	}
	//if (m_counts != m_tmpCounts || m_ifUpdate)
	//{
	// �����Ѿ��ж��Ƿ���ĸ��£�������Ϸ����������ʾ����
	AddUpdateRecord();
	MessageBox(_T("���³ɹ�"), _T("��ʾ"), MB_OK);
	// ��������û��п��ܼ�������Ϊ���û��������³�ʼ��
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
	m_newCode = _T("�޸����ĺ�");

	m_ifUpdate = FALSE;		// ���ݿ����޴��ĺ�
	UpdateData(FALSE);
	GetDlgItem(IDE_UPDATE_SEARCH)->SetFocus();
	SendDlgItemMessage(IDE_UPDATE_SEARCH, EM_SETSEL, 0, -1);
	/*}
	
	else
	{
		MessageBox(_T("�޸��»���Ϊ��"), _T("��ʾ"), MB_OK);
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
	//UpdateData(TRUE);
	// �ж����޸Ļ�������ҩƷ
	if (m_ifUpdate)
	{
		cs.Format(_T("insert into ������Ϣ values('%s', '%s', '%d', '%d', '%.2f', '%s', '��')"),
			time, m_code, m_tmpNum, m_counts, m_selPrice, login_ID);
	}
	else
	{
		cs.Format(_T("insert into ������Ϣ values('%s', '%s', '%d', '%d', '%.2f', '%s', '��')"),
			time, m_search, m_tmpNum, m_counts, m_selPrice, login_ID);
	}
	
	db.ExecuteSQL(cs);
	db.Close();
}


void CUpdateDlg::OnEnUpdateUpdateNum()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// �������� EM_SETEVENTMASK ��Ϣ���͵��ؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_tmpNum = 0;
	m_tmpNum = _wtoi(m_num);	// ʹ�õ�UNICODE�ַ�

	// �����Զ����Ϊ��,��������һ�η�ֹ�����ָ������
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

// Ϊʵ�ֵ���ȫѡ�༭������ר�ŵ��õĽ�ȡ��Ϣ����
BOOL CUpdateDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	// ������ֻ����PostMessage ������Ϣ���ŵ���Ϣ������
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
