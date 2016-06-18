// RecordsetOC.h : CRecordsetOC ���ʵ��



// CRecordsetOC ʵ��

// ���������� 2013��1��8��, 1:35

#include "stdafx.h"
#include "RecordsetOC.h"
IMPLEMENT_DYNAMIC(CRecordsetOC, CRecordset)

CRecordsetOC::CRecordsetOC(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ocTime = L"";
	m_cRoomNum = L"";
	m_ocFirst = L"";
	m_ocSecond = L"";
	m_ocThird = L"";
	m_ocFourth = L"";
	m_ocFifth = L"";
	m_ocOther = L"";
	m_nFields = 8;
	m_nDefaultType = dynaset;
}
// #error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CRecordsetOC::GetDefaultConnect()
{
	return _T("DSN=\x6559\x5ba4\x4fe1\x606f\x7ba1\x7406\x7cfb\x7edf;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x6559\x5ba4\x7ba1\x7406\x7cfb\x7edf;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CRecordsetOC::GetDefaultSQL()
{
	return _T("[dbo].[����ռ����Ϣ��]");
}

void CRecordsetOC::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[ocTime]"), m_ocTime);
	RFX_Text(pFX, _T("[cRoomNum]"), m_cRoomNum);
	RFX_Text(pFX, _T("[ocFirst]"), m_ocFirst);
	RFX_Text(pFX, _T("[ocSecond]"), m_ocSecond);
	RFX_Text(pFX, _T("[ocThird]"), m_ocThird);
	RFX_Text(pFX, _T("[ocFourth]"), m_ocFourth);
	RFX_Text(pFX, _T("[ocFifth]"), m_ocFifth);
	RFX_Text(pFX, _T("[ocOther]"), m_ocOther);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetOC ���

#ifdef _DEBUG
void CRecordsetOC::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetOC::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


