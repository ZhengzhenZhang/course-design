// DtlUpdateSet.h : CDtlUpdateSet ���ʵ��



// CDtlUpdateSet ʵ��

// ���������� 2012��6��17��, 20:31

#include "stdafx.h"
#include "DtlUpdateSet.h"
IMPLEMENT_DYNAMIC(CDtlUpdateSet, CRecordset)

CDtlUpdateSet::CDtlUpdateSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_upTime;
	m_code = L"";
	m_name = L"";
	m_specification = L"";
	m_upPrice = 0.0;
	m_upNum = 0;
	m_upCounts = 0;
	m_ID = L"";
	m_upMark = L"";
	m_nFields = 9;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CDtlUpdateSet::GetDefaultConnect()
{
	return _T("DSN=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CDtlUpdateSet::GetDefaultSQL()
{
	return _T("[dbo].[��������]");
}

void CDtlUpdateSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Date(pFX, _T("[upTime]"), m_upTime);
	RFX_Text(pFX, _T("[code]"), m_code);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[specification]"), m_specification);
	RFX_Single(pFX, _T("[upPrice]"), m_upPrice);
	RFX_Long(pFX, _T("[upNum]"), m_upNum);
	RFX_Long(pFX, _T("[upCounts]"), m_upCounts);
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[upMark]"), m_upMark);

}
/////////////////////////////////////////////////////////////////////////////
// CDtlUpdateSet ���

#ifdef _DEBUG
void CDtlUpdateSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDtlUpdateSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


