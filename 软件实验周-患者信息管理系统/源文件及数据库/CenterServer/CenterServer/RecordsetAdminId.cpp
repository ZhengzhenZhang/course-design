// CRecordsetAdminId.h : CRecordsetAdminId ���ʵ��



// CRecordsetAdminId ʵ��

// ���������� 2012��12��28��, 8:35

#include "stdafx.h"
#include "RecordsetAdminId.h"
IMPLEMENT_DYNAMIC(CRecordsetAdminId, CRecordset)

CRecordsetAdminId::CRecordsetAdminId(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_adminID = L"";
	m_adminPas = L"";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}
// #error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CRecordsetAdminId::GetDefaultConnect()
{
	return _T("DSN=\x60a3\x8005\x5c31\x8bca\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x60a3\x8005\x5c31\x8bca\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CRecordsetAdminId::GetDefaultSQL()
{
	return _T("[dbo].[����Ա�˺�]");
}

void CRecordsetAdminId::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[adminID]"), m_adminID);
	RFX_Text(pFX, _T("[adminPas]"), m_adminPas);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetAdminId ���

#ifdef _DEBUG
void CRecordsetAdminId::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetAdminId::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


