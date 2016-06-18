// RecordPastDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Begin.h"
#include "RecordPastDlg.h"


// CRecordPastDlg �Ի���

IMPLEMENT_DYNAMIC(CRecordPastDlg, CDialog)

CRecordPastDlg::CRecordPastDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecordPastDlg::IDD, pParent)
	, m_ftime(COleDateTime::GetCurrentTime())
	, m_totime(COleDateTime::GetCurrentTime())
	, m_edit(_T("������׼�ĺ�"))
	, m_sumNum(0)
	, m_sumMny(0)
	, m_radio(0)
{

}

CRecordPastDlg::~CRecordPastDlg()
{
}

void CRecordPastDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDT_PAST_FROM, m_ftime);
	DDX_DateTimeCtrl(pDX, IDT_PAST_TO, m_totime);
	DDX_Text(pDX, IDE_PAST, m_edit);
	DDX_Text(pDX, IDE_PAST_SUMNUM, m_sumNum);
	DDX_Text(pDX, IDE_PAST_SUMMNY, m_sumMny);
	DDX_Radio(pDX, IDR_PAST_ALL, m_radio);
	DDX_Control(pDX, IDL_RECORD_PAST, m_list);
	DDX_Control(pDX, IDE_PAST, m_CPast);
}


BEGIN_MESSAGE_MAP(CRecordPastDlg, CDialog)
	ON_BN_CLICKED(IDR_PAST_ALL, &CRecordPastDlg::OnBnClickedPastAll)
	ON_BN_CLICKED(IDR_PAST_LMON, &CRecordPastDlg::OnBnClickedPastLmon)
	ON_BN_CLICKED(IDR_PAST_LWEEK, &CRecordPastDlg::OnBnClickedPastLweek)
	ON_BN_CLICKED(IDR_PAST_LYEST, &CRecordPastDlg::OnBnClickedPastLyest)
	ON_BN_CLICKED(IDB_PAST_SEARCH, &CRecordPastDlg::OnBnClickedPastSearch)
END_MESSAGE_MAP()

BOOL CRecordPastDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_list.InsertColumn(0, _T("����ʱ��"), LVCFMT_CENTER, 105);
	m_list.InsertColumn(1, _T("��׼�ĺ�"), LVCFMT_CENTER, 80);
	m_list.InsertColumn(2, _T("ҩƷ����"), LVCFMT_CENTER, 110);
	m_list.InsertColumn(3, _T("ҩƷ���"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(4, _T("����ʱ��"), LVCFMT_CENTER, 65);
	m_list.InsertColumn(5, _T("��������"), LVCFMT_CENTER, 65);
	m_list.InsertColumn(6, _T("�ܼ�ֵ"), LVCFMT_CENTER, 65);
	m_list.InsertColumn(7, _T("�ֿ����"), LVCFMT_CENTER, 65);
	m_list.InsertColumn(8, _T("�Ǽ�ԱID"), LVCFMT_CENTER, 65);
	m_list.InsertColumn(9, _T("��ע"), LVCFMT_CENTER, 180);

	//m_list.SetBkColor(RGB(26, 231, 151));
	//m_list.SetTextBkColor(RGB(26, 231, 151));
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES);

	OnBnClickedPastAll();

	GetDlgItem(IDE_PAST)->SetFocus();
	SendDlgItemMessage(IDE_PAST, EM_SETSEL, 0, -1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CRecordPastDlg::ListTheInfo()
{
	// ����ʱ�併�����У�������
	set.m_strSort.Format(_T("dealTime desc"));
	if (!set.Open())
		MessageBox(_T("�������ݿ�ʱ����"), _T("��ʾ"), MB_OK);
	m_list.DeleteAllItems();
	if(set.IsEOF())
	{
		m_sumMny = 0;
		m_sumNum = 0;
		//MessageBox(_T("�����ۼ�¼"));
	}
	else
	{
		m_sumMny = 0;
		m_sumNum = 0;
		for(int i=0; !set.IsEOF(); i++,set.MoveNext())
		{
			CString cs;
			cs.Format(_T("%d-%d-%d %d:%d:%d"),
				set.m_dealTime.GetYear(), set.m_dealTime.GetMonth(), set.m_dealTime.GetDay(),
				set.m_dealTime.GetHour(), set.m_dealTime.GetMinute(), set.m_dealTime.GetSecond());
			m_list.InsertItem(i, cs);

			set.m_code.TrimRight();
			m_list.SetItemText(i, 1, set.m_code);

			set.m_name.TrimRight();
			m_list.SetItemText(i, 2, set.m_name);

			set.m_specification.TrimRight();
			m_list.SetItemText(i, 3, set.m_specification);

			cs.Format(_T("%d-%d-%d"),
				set.m_pastTime.GetYear(), set.m_pastTime.GetMonth(), set.m_pastTime.GetDay());
			m_list.SetItemText(i, 4, cs);
			
			cs.Format(_T("%d"), set.m_dealNum);
			cs.TrimRight();
			m_list.SetItemText(i, 5, cs);
			
			cs.Format(_T("%.2f"), set.m_totalValue);
			cs.TrimRight();
			m_list.SetItemText(i, 6, cs);

			cs.Format(_T("%d"), set.m_counts);
			cs.TrimRight();
			m_list.SetItemText(i, 7, cs);

			set.m_ID.TrimRight();
			m_list.SetItemText(i, 8, set.m_ID);

			set.m_dealMark.TrimRight();
			m_list.SetItemText(i, 9, set.m_dealMark);

			m_sumMny += set.m_totalValue;
			m_sumNum ++;
		}	
	}
	UpdateData(FALSE);
	set.Close();
}


// CRecordPastDlg ��Ϣ�������

void CRecordPastDlg::OnBnClickedPastAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_radio = 0;
	set.m_strFilter.Format(_T(""));
	ListTheInfo();
}

void CRecordPastDlg::OnBnClickedPastLmon()
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

	cs = _T("dealTime between ");
	cs += ft;
	cs += _T(" and ");
	cs += nt;

	//MessageBox(cs);

	set.m_strFilter = cs;
	ListTheInfo();
}

void CRecordPastDlg::OnBnClickedPastLweek()
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

	cs = _T("dealTime between ");
	cs += ft;
	cs += _T(" and ");
	cs += nt;
	//MessageBox(cs);
	set.m_strFilter = cs;
	ListTheInfo();
}

void CRecordPastDlg::OnBnClickedPastLyest()
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

	cs = _T("dealTime between ");
	cs += ft;
	cs += _T(" and ");
	cs += nt;
	//MessageBox(cs);
	set.m_strFilter = cs;
	ListTheInfo();
}

void CRecordPastDlg::OnBnClickedPastSearch()
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

	cs = _T("dealTime between ");
	cs += ft;
	cs += _T(" and ");
	cs += nt;
	cs += _T(" and code like '%");
	cs += m_edit;
	cs += _T("%'");

	set.m_strFilter = cs;
	ListTheInfo();

	GetDlgItem(IDE_PAST)->SetFocus();
	SendDlgItemMessage(IDE_PAST, EM_SETSEL, 0, -1);
}


BOOL CRecordPastDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message==WM_LBUTTONDOWN)
	{
		if(pMsg->hwnd == m_CPast.m_hWnd)
		{
			GetDlgItem(IDE_PAST)->PostMessage(EM_SETSEL, 0, -1);
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
