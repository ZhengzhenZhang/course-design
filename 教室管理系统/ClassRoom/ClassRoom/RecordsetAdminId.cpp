// RecordsetAdminId.h : CRecordsetAdminId ���ʵ��



// CRecordsetAdminId ʵ��

// ���������� 2013��1��8��, 9:39

#include "stdafx.h"
#include "RecordsetAdminId.h"
IMPLEMENT_DYNAMIC(CRecordsetAdminId, CRecordset)

CRecordsetAdminId::CRecordsetAdminId(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_adminID = L"";
	m_adminPassword = L"";
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
	return _T("DSN=\x6559\x5ba4\x4fe1\x606f\x7ba1\x7406\x7cfb\x7edf;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x6559\x5ba4\x7ba1\x7406\x7cfb\x7edf;Network=DBMSSOCN;Trusted_Connection=Yes");
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
	RFX_Text(pFX, _T("[adminPassword]"), m_adminPassword);

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


