// RecordsetTBuild.h : CRecordsetTBuild ���ʵ��



// CRecordsetTBuild ʵ��

// ���������� 2013��1��7��, 22:18

#include "stdafx.h"
#include "RecordsetTBuild.h"
IMPLEMENT_DYNAMIC(CRecordsetTBuild, CRecordset)

CRecordsetTBuild::CRecordsetTBuild(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_tBuildNum = L"";
	m_tBuildAddress = L"";
	m_tBuildManager = L"";
	m_tBuildRemark = L"";
	m_tBuildPhone = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
// #error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CRecordsetTBuild::GetDefaultConnect()
{
	return _T("DSN=\x6559\x5ba4\x4fe1\x606f\x7ba1\x7406\x7cfb\x7edf;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x6559\x5ba4\x7ba1\x7406\x7cfb\x7edf;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CRecordsetTBuild::GetDefaultSQL()
{
	return _T("[dbo].[��ѧ¥��Ϣ��]");
}

void CRecordsetTBuild::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[tBuildNum]"), m_tBuildNum);
	RFX_Text(pFX, _T("[tBuildAddress]"), m_tBuildAddress);
	RFX_Text(pFX, _T("[tBuildManager]"), m_tBuildManager);
	RFX_Text(pFX, _T("[tBuildRemark]"), m_tBuildRemark);
	RFX_Text(pFX, _T("[tBuildPhone]"), m_tBuildPhone);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetTBuild ���

#ifdef _DEBUG
void CRecordsetTBuild::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetTBuild::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


