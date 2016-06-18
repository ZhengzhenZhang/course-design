// RecordsetWorkerId.h : CRecordsetWorkerId ���ʵ��



// CRecordsetWorkerId ʵ��

// ���������� 2012��12��28��, 10:11

#include "stdafx.h"
#include "RecordsetWorkerId.h"
IMPLEMENT_DYNAMIC(CRecordsetWorkerId, CRecordset)

CRecordsetWorkerId::CRecordsetWorkerId(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_workerID = L"";
	m_workerPas = L"";
	m_workerStyle = 0;
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
// #error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CRecordsetWorkerId::GetDefaultConnect()
{
	return _T("DSN=\x60a3\x8005\x5c31\x8bca\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x60a3\x8005\x5c31\x8bca\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CRecordsetWorkerId::GetDefaultSQL()
{
	return _T("[dbo].[ְ����Ϣ]");
}

void CRecordsetWorkerId::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[workerID]"), m_workerID);
	RFX_Text(pFX, _T("[workerPas]"), m_workerPas);
	RFX_Long(pFX, _T("[workerStyle]"), m_workerStyle);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetWorkerId ���

#ifdef _DEBUG
void CRecordsetWorkerId::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetWorkerId::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


