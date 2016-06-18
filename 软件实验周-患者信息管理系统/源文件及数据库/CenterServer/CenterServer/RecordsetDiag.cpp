// RecordsetDiag.h : CRecordsetDiag ���ʵ��



// CRecordsetDiag ʵ��

// ���������� 2012��12��26��, 10:42

#include "stdafx.h"
#include "RecordsetDiag.h"
IMPLEMENT_DYNAMIC(CRecordsetDiag, CRecordset)

CRecordsetDiag::CRecordsetDiag(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_diagNum;
	m_idNumber = L"";
	m_patientName = L"";
	m_patientSex = L"";
	m_patientAge = 0;
	m_patientPhone = L"";
	m_patientAddress = L"";
	m_patientNum = L"";
	m_patientAllergy = L"";
	m_patientRemark = L"";
	m_diagTime;
	m_diagDoctorID = L"";
	m_diagDeclare = L"";
	m_diagInitCheck = L"";
	m_diagInstruCheck = L"";
	m_diagResult = L"";
	m_diagScheme = L"";
	m_diagRemark = L"";
	m_nFields = 18;
	m_nDefaultType = dynaset;
}
// #error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CRecordsetDiag::GetDefaultConnect()
{
	return _T("DSN=\x60a3\x8005\x5c31\x8bca\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x60a3\x8005\x5c31\x8bca\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CRecordsetDiag::GetDefaultSQL()
{
	return _T("[dbo].[���߾�����Ϣ]");
}

void CRecordsetDiag::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Date(pFX, _T("[diagNum]"), m_diagNum);
	RFX_Text(pFX, _T("[idNumber]"), m_idNumber);
	RFX_Text(pFX, _T("[patientName]"), m_patientName);
	RFX_Text(pFX, _T("[patientSex]"), m_patientSex);
	RFX_Long(pFX, _T("[patientAge]"), m_patientAge);
	RFX_Text(pFX, _T("[patientPhone]"), m_patientPhone);
	RFX_Text(pFX, _T("[patientAddress]"), m_patientAddress);
	RFX_Text(pFX, _T("[patientNum]"), m_patientNum);
	RFX_Text(pFX, _T("[patientAllergy]"), m_patientAllergy);
	RFX_Text(pFX, _T("[patientRemark]"), m_patientRemark);
	RFX_Date(pFX, _T("[diagTime]"), m_diagTime);
	RFX_Text(pFX, _T("[diagDoctorID]"), m_diagDoctorID);
	RFX_Text(pFX, _T("[diagDeclare]"), m_diagDeclare);
	RFX_Text(pFX, _T("[diagInitCheck]"), m_diagInitCheck);
	RFX_Text(pFX, _T("[diagInstruCheck]"), m_diagInstruCheck);
	RFX_Text(pFX, _T("[diagResult]"), m_diagResult);
	RFX_Text(pFX, _T("[diagScheme]"), m_diagScheme, 1000);
	RFX_Text(pFX, _T("[diagRemark]"), m_diagRemark);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetDiag ���

#ifdef _DEBUG
void CRecordsetDiag::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetDiag::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


