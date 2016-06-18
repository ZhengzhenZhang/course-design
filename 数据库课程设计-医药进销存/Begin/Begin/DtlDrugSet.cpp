// DtlDrugSet.h : CDtlDrugSet ���ʵ��



// CDtlDrugSet ʵ��

// ���������� 2012��6��15��, 0:57

#include "stdafx.h"
#include "DtlDrugSet.h"
IMPLEMENT_DYNAMIC(CDtlDrugSet, CRecordset)

CDtlDrugSet::CDtlDrugSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_code = L"";
	m_name = L"";
	m_specification = L"";
	m_efficacy = L"";
	m_ingredient = L"";
	m_dosage = L"";
	m_selPrice = 0.0;
	m_counts = 0;
	m_nFields = 8;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CDtlDrugSet::GetDefaultConnect()
{
	return _T("DSN=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CDtlDrugSet::GetDefaultSQL()
{
	return _T("[dbo].[ҩƷ����]");
}

void CDtlDrugSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[code]"), m_code);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[specification]"), m_specification);
	RFX_Text(pFX, _T("[efficacy]"), m_efficacy);
	RFX_Text(pFX, _T("[ingredient]"), m_ingredient);
	RFX_Text(pFX, _T("[dosage]"), m_dosage);
	RFX_Single(pFX, _T("[selPrice]"), m_selPrice);
	RFX_Long(pFX, _T("[counts]"), m_counts);

}
/////////////////////////////////////////////////////////////////////////////
// CDtlDrugSet ���

#ifdef _DEBUG
void CDtlDrugSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDtlDrugSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


