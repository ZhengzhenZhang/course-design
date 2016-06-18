// RecordsetFee.h : CRecordsetFee ���ʵ��



// CRecordsetFee ʵ��

// ���������� 2012��12��26��, 23:45

#include "stdafx.h"
#include "RecordsetFee.h"
IMPLEMENT_DYNAMIC(CRecordsetFee, CRecordset)

CRecordsetFee::CRecordsetFee(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_diagNum;
	m_feeDrug = 0.0;
	m_feeDiag = 0.0;
	m_feeTransfusion = 0.0;
	m_feeCheck = 0.0;
	m_feeConsumable = 0.0;
	m_feeRadiate = 0.0;
	m_feeTotal = 0.0;
	m_feedback = L"";
	m_nFields = 9;
	m_nDefaultType = dynaset;
}
// #error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CRecordsetFee::GetDefaultConnect()
{
	return _T("DSN=\x60a3\x8005\x5c31\x8bca\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x60a3\x8005\x5c31\x8bca\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CRecordsetFee::GetDefaultSQL()
{
	return _T("[dbo].[���ü��ָ����]");
}

void CRecordsetFee::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Date(pFX, _T("[diagNum]"), m_diagNum);
	RFX_Single(pFX, _T("[feeDrug]"), m_feeDrug);
	RFX_Single(pFX, _T("[feeDiag]"), m_feeDiag);
	RFX_Single(pFX, _T("[feeTransfusion]"), m_feeTransfusion);
	RFX_Single(pFX, _T("[feeCheck]"), m_feeCheck);
	RFX_Single(pFX, _T("[feeConsumable]"), m_feeConsumable);
	RFX_Single(pFX, _T("[feeRadiate]"), m_feeRadiate);
	RFX_Single(pFX, _T("[feeTotal]"), m_feeTotal);
	RFX_Text(pFX, _T("[feedback]"), m_feedback);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetFee ���

#ifdef _DEBUG
void CRecordsetFee::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetFee::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


