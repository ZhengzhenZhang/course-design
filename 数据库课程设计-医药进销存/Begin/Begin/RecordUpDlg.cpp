// RecordUpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Begin.h"
#include "RecordUpDlg.h"


// CRecordUpDlg �Ի���

IMPLEMENT_DYNAMIC(CRecordUpDlg, CDialog)

CRecordUpDlg::CRecordUpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecordUpDlg::IDD, pParent)
	, m_radio(0)
	, m_ftime(COleDateTime::GetCurrentTime())
	, m_totime(COleDateTime::GetCurrentTime())
	, m_edit(_T("������׼�ĺ�"))
	, m_sumNum(0)
{

}

CRecordUpDlg::~CRecordUpDlg()
{
}

void CRecordUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDL_RECODE_UPDATE, m_list);
	DDX_Radio(pDX, IDR_UPDATE_ALL, m_radio);
	DDX_DateTimeCtrl(pDX, IDT_UPDATE_FROM, m_ftime);
	DDX_DateTimeCtrl(pDX, IDT_UPDATE_TO, m_totime);
	DDX_Text(pDX, IDE_UPDATE_SEARCH, m_edit);
	DDX_Text(pDX, IDE_UPDATE_SUMNUM, m_sumNum);
	DDX_Control(pDX, IDE_UPDATE_SEARCH, m_CSearch);
}


BEGIN_MESSAGE_MAP(CRecordUpDlg, CDialog)
	ON_BN_CLICKED(IDR_UPDATE_ALL, &CRecordUpDlg::OnBnClickedUpdateAll)
	ON_BN_CLICKED(IDR_UPDATE_LMON, &CRecordUpDlg::OnBnClickedUpdateLmon)
	ON_BN_CLICKED(IDR_UPDATE_LWEEK, &CRecordUpDlg::OnBnClickedUpdateLweek)
	ON_BN_CLICKED(IDR_UPDATE_LYEST, &CRecordUpDlg::OnBnClickedUpdateLyest)
	ON_BN_CLICKED(IDB_UPDATE_SEARCH, &CRecordUpDlg::OnBnClickedUpdateSearch)
END_MESSAGE_MAP()


BOOL CRecordUpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list.InsertColumn(0, _T("��"), LVCFMT_CENTER, 28);
	m_list.InsertColumn(1, _T("����ʱ��"), LVCFMT_CENTER, 105);
	m_list.InsertColumn(2, _T("��׼�ĺ�"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(3, _T("ҩƷ����"), LVCFMT_CENTER, 110);
	m_list.InsertColumn(4, _T("ҩƷ���"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(5, _T("���±���"), LVCFMT_CENTER, 65);
	m_list.InsertColumn(6, _T("��������"), LVCFMT_CENTER, 65);
	m_list.InsertColumn(7, _T("Ŀǰ���"), LVCFMT_CENTER, 65);
	m_list.InsertColumn(8, _T("��¼ԱID"), LVCFMT_CENTER, 65);
	
	//m_list.SetBkColor(RGB(26, 231, 151));
	//m_list.SetTextBkColor(RGB(26, 231, 151));
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES);

	OnBnClickedUpdateAll();

	GetDlgItem(IDE_UPDATE_SEARCH)->SetFocus();
	SendDlgItemMessage(IDE_UPDATE_SEARCH, EM_SETSEL, 0, -1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
// ��������Ϣ���Ӻ���
void CRecordUpDlg::ListTheInfo()
{
	// ����ʱ�併�����У�������
	set.m_strSort.Format(_T("upTime desc"));
	if (!set.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
	m_list.DeleteAllItems();
	if(set.IsEOF())
	{
		m_sumNum = 0;
	}
	else
	{
		m_sumNum = 0;
		for(int i=0; !set.IsEOF(); i++,set.MoveNext())
		{
			CString cs;
			set.m_upMark.TrimRight();
			m_list.InsertItem(i, set.m_upMark);

			cs.Format(_T("%d-%d-%d %d:%d:%d"),
				set.m_upTime.GetYear(), set.m_upTime.GetMonth(), set.m_upTime.GetDay(),
				set.m_upTime.GetHour(), set.m_upTime.GetMinute(), set.m_upTime.GetSecond());
			m_list.SetItemText(i, 1, cs);

			set.m_code.TrimRight();
			m_list.SetItemText(i, 2, set.m_code);

			set.m_name.TrimRight();
			m_list.SetItemText(i, 3, set.m_name);

			set.m_specification.TrimRight();
			m_list.SetItemText(i, 4, set.m_specification);

			cs.Format(_T("%.2f"), set.m_upPrice);
			cs.TrimRight();
			m_list.SetItemText(i, 5, cs);

			cs.Format(_T("%d"), set.m_upNum);
			cs.TrimRight();
			m_list.SetItemText(i, 6, cs);

			cs.Format(_T("%d"), set.m_upCounts);
			cs.TrimRight();
			m_list.SetItemText(i, 7, cs);

			set.m_ID.TrimRight();
			m_list.SetItemText(i, 8, set.m_ID);

			m_sumNum++;
		}	
	}
	UpdateData(FALSE);
	set.Close();
}

// CRecordUpDlg ��Ϣ�������

void CRecordUpDlg::OnBnClickedUpdateAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_radio = 0;
	set.m_strFilter.Format(_T(""));
	ListTheInfo();
}

void CRecordUpDlg::OnBnClickedUpdateLmon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	m_radio = 1;

	CTime ct = CTime::GetCurrentTime();
	// ��ʱ��         ��  Сʱ ���� ��
	//ct -= CTimeSpan(ct.GetDay(), 0, 0, 0);
	int m_ny = ct.GetYear();
	int m_nm = ct.GetMonth();
	int m_nd = 1;

	int m_fy, m_fm, m_fd;
	m_fy = m_ny;
	m_fm = m_nm;
	m_fd = 1;
	if (m_fm == 1)
	{
		m_fm = 12;
		m_fy--;
	}
	else
	{
		m_fm--;
	}


	CString ft, nt, cs;
	ft.Format(_T("'%d-%d-%d'"), m_fy, m_fm, m_fd);
	nt.Format(_T("'%d-%d-%d'"), m_ny, m_nm, m_nd);

	cs = _T("upTime between ");
	cs += ft;
	cs += _T(" and ");
	cs += nt;

	//MessageBox(cs);

	set.m_strFilter = cs;
	ListTheInfo();
}

void CRecordUpDlg::OnBnClickedUpdateLweek()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	m_radio = 2;

	CTime ct = CTime::GetCurrentTime();
	// ��ʱ��         ��  Сʱ ���� ��
	ct -= CTimeSpan(ct.GetDayOfWeek()-1, 0, 0, 0);
	int m_ny = ct.GetYear();
	int m_nm = ct.GetMonth();
	int m_nd = ct.GetDay();
	ct -= CTimeSpan(7, 0, 0, 0);
	int m_fy = ct.GetYear();
	int m_fm = ct.GetMonth();
	int m_fd = ct.GetDay();

	CString ft, nt, cs;
	ft.Format(_T("'%d-%d-%d'"), m_fy, m_fm, m_fd);
	nt.Format(_T("'%d-%d-%d'"), m_ny, m_nm, m_nd);

	cs = _T("upTime between ");
	cs += ft;
	cs += _T(" and ");
	cs += nt;
	//MessageBox(cs);
	set.m_strFilter = cs;
	ListTheInfo();
}

void CRecordUpDlg::OnBnClickedUpdateLyest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	m_radio = 3;

	CTime ct = CTime::GetCurrentTime();
	// ��ʱ��         ��  Сʱ ���� ��
	//ct -= CTimeSpan(ct.GetDayOfWeek()-1, 0, 0, 0);
	int m_ny = ct.GetYear();
	int m_nm = ct.GetMonth();
	int m_nd = ct.GetDay();
	ct -= CTimeSpan(1, 0, 0, 0);
	int m_fy = ct.GetYear();
	int m_fm = ct.GetMonth();
	int m_fd = ct.GetDay();

	CString ft, nt, cs;
	ft.Format(_T("'%d-%d-%d'"), m_fy, m_fm, m_fd);
	nt.Format(_T("'%d-%d-%d'"), m_ny, m_nm, m_nd);

	cs = _T("upTime between ");
	cs += ft;
	cs += _T(" and ");
	cs += nt;
	//MessageBox(cs);
	set.m_strFilter = cs;
	ListTheInfo();
}


void CRecordUpDlg::OnBnClickedUpdateSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int m_ny = m_totime.GetYear();
	int m_nm = m_totime.GetMonth();
	int m_nd = m_totime.GetDay()+1;

	int m_fy = m_ftime.GetYear();
	int m_fm = m_ftime.GetMonth();
	int m_fd = m_ftime.GetDay();
	CString ft, nt, cs;
	ft.Format(_T("'%d-%d-%d'"), m_fy, m_fm, m_fd);
	nt.Format(_T("'%d-%d-%d'"), m_ny, m_nm, m_nd);

	cs = _T("upTime between ");
	cs += ft;
	cs += _T(" and ");
	cs += nt;
	cs += _T(" and code like '%");
	cs += m_edit;
	cs += _T("%'");

	set.m_strFilter = cs;
	ListTheInfo();

	GetDlgItem(IDE_UPDATE_SEARCH)->SetFocus();
	SendDlgItemMessage(IDE_UPDATE_SEARCH, EM_SETSEL, 0, -1);

}

BOOL CRecordUpDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message==WM_LBUTTONDOWN)
	{
		if(pMsg->hwnd == m_CSearch.m_hWnd)
		{
			GetDlgItem(IDE_UPDATE_SEARCH)->PostMessage(EM_SETSEL, 0, -1);
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
