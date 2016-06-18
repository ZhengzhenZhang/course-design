// IDkeySet.h : CIDkeySet ���ʵ��



// CIDkeySet ʵ��

// ���������� 2012��6��14��, 17:27

#include "stdafx.h"
#include "IDkeySet.h"
IMPLEMENT_DYNAMIC(CIDkeySet, CRecordset)

CIDkeySet::CIDkeySet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = L"";
	m_PASSWORD = L"";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CIDkeySet::GetDefaultConnect()
{
	return _T("DSN=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CIDkeySet::GetDefaultSQL()
{
	return _T("[dbo].[�˺�����]");
}

void CIDkeySet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[PASSWORD]"), m_PASSWORD);

}
/////////////////////////////////////////////////////////////////////////////
// CIDkeySet ���

#ifdef _DEBUG
void CIDkeySet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CIDkeySet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


