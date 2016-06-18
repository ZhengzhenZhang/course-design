// DtlPastSet.h : CDtlPastSet ���ʵ��



// CDtlPastSet ʵ��

// ���������� 2012��6��18��, 10:48

#include "stdafx.h"
#include "DtlPastSet.h"
IMPLEMENT_DYNAMIC(CDtlPastSet, CRecordset)

CDtlPastSet::CDtlPastSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_dealTime;
	m_code = L"";
	m_name = L"";
	m_specification = L"";
	m_pastTime;
	m_dealNum = 0;
	m_totalValue = 0.0;
	m_counts = 0;
	m_ID = L"";
	m_dealMark = L"";
	m_nFields = 10;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CDtlPastSet::GetDefaultConnect()
{
	return _T("DSN=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CDtlPastSet::GetDefaultSQL()
{
	return _T("[dbo].[����ҩƷ��������]");
}

void CDtlPastSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Date(pFX, _T("[dealTime]"), m_dealTime);
	RFX_Text(pFX, _T("[code]"), m_code);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[specification]"), m_specification);
	RFX_Date(pFX, _T("[pastTime]"), m_pastTime);
	RFX_Long(pFX, _T("[dealNum]"), m_dealNum);
	RFX_Single(pFX, _T("[totalValue]"), m_totalValue);
	RFX_Long(pFX, _T("[counts]"), m_counts);
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[dealMark]"), m_dealMark);

}
/////////////////////////////////////////////////////////////////////////////
// CDtlPastSet ���

#ifdef _DEBUG
void CDtlPastSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDtlPastSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


