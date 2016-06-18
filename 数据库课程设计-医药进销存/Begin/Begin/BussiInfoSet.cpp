// BussiInfoSet.h : CBussiInfoSet ���ʵ��



// CBussiInfoSet ʵ��

// ���������� 2012��6��15��, 15:29

#include "stdafx.h"
#include "BussiInfoSet.h"
IMPLEMENT_DYNAMIC(CBussiInfoSet, CRecordset)

CBussiInfoSet::CBussiInfoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_code = L"";
	m_name = L"";
	m_address = L"";
	m_phone = L"";
	m_remark = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CBussiInfoSet::GetDefaultConnect()
{
	return _T("DSN=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CBussiInfoSet::GetDefaultSQL()
{
	return _T("[dbo].[��������Ϣ]");
}

void CBussiInfoSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[code]"), m_code);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[address]"), m_address);
	RFX_Text(pFX, _T("[phone]"), m_phone);
	RFX_Text(pFX, _T("[remark]"), m_remark);

}
/////////////////////////////////////////////////////////////////////////////
// CBussiInfoSet ���

#ifdef _DEBUG
void CBussiInfoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBussiInfoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


