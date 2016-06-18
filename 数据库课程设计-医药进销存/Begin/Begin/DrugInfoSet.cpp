// DrugInfoSet.h : CDrugInfoSet ���ʵ��



// CDrugInfoSet ʵ��

// ���������� 2012��6��14��, 23:00

#include "stdafx.h"
#include "DrugInfoSet.h"
IMPLEMENT_DYNAMIC(CDrugInfoSet, CRecordset)

CDrugInfoSet::CDrugInfoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_code = L"";
	m_name = L"";
	m_specification = L"";
	m_efficacy = L"";
	m_ingredient = L"";
	m_dosage = L"";
	m_selPrice = 0.0;
	m_nFields = 7;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CDrugInfoSet::GetDefaultConnect()
{
	return _T("DSN=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CDrugInfoSet::GetDefaultSQL()
{
	return _T("[dbo].[ҩƷ��Ϣ]");
}

void CDrugInfoSet::DoFieldExchange(CFieldExchange* pFX)
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

}
/////////////////////////////////////////////////////////////////////////////
// CDrugInfoSet ���

#ifdef _DEBUG
void CDrugInfoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDrugInfoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


