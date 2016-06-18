// RecordsetPatient.h : CRecordsetPatient ���ʵ��



// CRecordsetPatient ʵ��

// ���������� 2012��12��25��, 16:58

#include "stdafx.h"
#include "RecordsetPatient.h"
IMPLEMENT_DYNAMIC(CRecordsetPatient, CRecordset)

CRecordsetPatient::CRecordsetPatient(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_idNumber = L"";
	m_patientName = L"";
	m_patientSex = L"";
	m_patientAge = 0;
	m_patientPhone = L"";
	m_patientAddress = L"";
	m_patientNum = L"";
	m_patientAllergy = L"";
	m_patientRemark = L"";
	m_nFields = 9;
	m_nDefaultType = dynaset;
}
// #error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CRecordsetPatient::GetDefaultConnect()
{
	return _T("DSN=\x60a3\x8005\x5c31\x8bca\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x60a3\x8005\x5c31\x8bca\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CRecordsetPatient::GetDefaultSQL()
{
	return _T("[dbo].[������Ϣ]");
}

void CRecordsetPatient::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[idNumber]"), m_idNumber);
	RFX_Text(pFX, _T("[patientName]"), m_patientName);
	RFX_Text(pFX, _T("[patientSex]"), m_patientSex);
	RFX_Long(pFX, _T("[patientAge]"), m_patientAge);
	RFX_Text(pFX, _T("[patientPhone]"), m_patientPhone);
	RFX_Text(pFX, _T("[patientAddress]"), m_patientAddress);
	RFX_Text(pFX, _T("[patientNum]"), m_patientNum);
	RFX_Text(pFX, _T("[patientAllergy]"), m_patientAllergy);
	RFX_Text(pFX, _T("[patientRemark]"), m_patientRemark);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetPatient ���

#ifdef _DEBUG
void CRecordsetPatient::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetPatient::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


