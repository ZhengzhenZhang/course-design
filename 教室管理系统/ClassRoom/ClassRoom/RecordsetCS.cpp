// RecordsetCS.h : CRecordsetCS ���ʵ��



// CRecordsetCS ʵ��

// ���������� 2013��1��6��, 23:38

#include "stdafx.h"
#include "RecordsetCS.h"
IMPLEMENT_DYNAMIC(CRecordsetCS, CRecordset)

CRecordsetCS::CRecordsetCS(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_tBuildNum = L"";
	m_cRoomNum = L"";
	m_csWeek = 0;
	m_csFirst = L"";
	m_csSecond = L"";
	m_csThird = L"";
	m_csFourth = L"";
	m_csFifth = L"";
	m_nFields = 8;
	m_nDefaultType = dynaset;
}
// #error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CRecordsetCS::GetDefaultConnect()
{
	return _T("DSN=\x6559\x5ba4\x4fe1\x606f\x7ba1\x7406\x7cfb\x7edf;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x6559\x5ba4\x7ba1\x7406\x7cfb\x7edf;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CRecordsetCS::GetDefaultSQL()
{
	return _T("[dbo].[��ѧ¥�ſ���Ϣ��ͼ]");
}

void CRecordsetCS::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[tBuildNum]"), m_tBuildNum);
	RFX_Text(pFX, _T("[cRoomNum]"), m_cRoomNum);
	RFX_Long(pFX, _T("[csWeek]"), m_csWeek);
	RFX_Text(pFX, _T("[csFirst]"), m_csFirst);
	RFX_Text(pFX, _T("[csSecond]"), m_csSecond);
	RFX_Text(pFX, _T("[csThird]"), m_csThird);
	RFX_Text(pFX, _T("[csFourth]"), m_csFourth);
	RFX_Text(pFX, _T("[csFifth]"), m_csFifth);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetCS ���

#ifdef _DEBUG
void CRecordsetCS::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetCS::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


