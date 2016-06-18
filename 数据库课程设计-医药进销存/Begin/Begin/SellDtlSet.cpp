// SellDtlSet.h : CSellDtlSet ���ʵ��



// CSellDtlSet ʵ��

// ���������� 2012��6��16��, 10:51

#include "stdafx.h"
#include "SellDtlSet.h"
IMPLEMENT_DYNAMIC(CSellDtlSet, CRecordset)

CSellDtlSet::CSellDtlSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_sellTime;
	m_code = L"";
	m_name = L"";
	m_specification = L"";
	m_sellNum = 0;
	m_sellSumMny = 0.0;
	m_ID = L"";
	m_nFields = 7;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CSellDtlSet::GetDefaultConnect()
{
	return _T("DSN=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CSellDtlSet::GetDefaultSQL()
{
	return _T("[dbo].[��������]");
}

void CSellDtlSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Date(pFX, _T("[sellTime]"), m_sellTime);
	RFX_Text(pFX, _T("[code]"), m_code);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[specification]"), m_specification);
	RFX_Long(pFX, _T("[sellNum]"), m_sellNum);
	RFX_Single(pFX, _T("[sellSumMny]"), m_sellSumMny);
	RFX_Text(pFX, _T("[ID]"), m_ID);

}
/////////////////////////////////////////////////////////////////////////////
// CSellDtlSet ���

#ifdef _DEBUG
void CSellDtlSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSellDtlSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


