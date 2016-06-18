// WorkerInfoSet.h : CWorkerInfoSet ���ʵ��



// CWorkerInfoSet ʵ��

// ���������� 2012��6��17��, 16:17

#include "stdafx.h"
#include "WorkerInfoSet.h"
IMPLEMENT_DYNAMIC(CWorkerInfoSet, CRecordset)

CWorkerInfoSet::CWorkerInfoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = L"";
	m_name = L"";
	m_position = L"";
	m_phone = L"";
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CWorkerInfoSet::GetDefaultConnect()
{
	return _T("DSN=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CWorkerInfoSet::GetDefaultSQL()
{
	return _T("[dbo].[ְ����Ϣ]");
}

void CWorkerInfoSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[position]"), m_position);
	RFX_Text(pFX, _T("[phone]"), m_phone);

}
/////////////////////////////////////////////////////////////////////////////
// CWorkerInfoSet ���

#ifdef _DEBUG
void CWorkerInfoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CWorkerInfoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


