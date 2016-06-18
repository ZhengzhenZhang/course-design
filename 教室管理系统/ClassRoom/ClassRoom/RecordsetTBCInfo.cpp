// RecordsetTBCInfo.h : CRecordsetTBCInfo ���ʵ��



// CRecordsetTBCInfo ʵ��

// ���������� 2013��1��7��, 21:25

#include "stdafx.h"
#include "RecordsetTBCInfo.h"
IMPLEMENT_DYNAMIC(CRecordsetTBCInfo, CRecordset)

CRecordsetTBCInfo::CRecordsetTBCInfo(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_cRoomNum = L"";
	m_tBuildNum = L"";
	m_cRoomVolume = 0;
	m_cRoomIsProjector = FALSE;
	m_cRoomIsDamage = FALSE;
	m_cRoomRemark = L"";
	m_tBuildAddress = L"";
	m_tBuildManager = L"";
	m_tBuildRemark = L"";
	m_tBuildPhone = L"";
	m_nFields = 10;
	m_nDefaultType = dynaset;
}
// #error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CRecordsetTBCInfo::GetDefaultConnect()
{
	return _T("DSN=\x6559\x5ba4\x4fe1\x606f\x7ba1\x7406\x7cfb\x7edf;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x6559\x5ba4\x7ba1\x7406\x7cfb\x7edf;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CRecordsetTBCInfo::GetDefaultSQL()
{
	return _T("[dbo].[��ѧ¥������Ϣ��ͼ]");
}

void CRecordsetTBCInfo::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[cRoomNum]"), m_cRoomNum);
	RFX_Text(pFX, _T("[tBuildNum]"), m_tBuildNum);
	RFX_Long(pFX, _T("[cRoomVolume]"), m_cRoomVolume);
	RFX_Bool(pFX, _T("[cRoomIsProjector]"), m_cRoomIsProjector);
	RFX_Bool(pFX, _T("[cRoomIsDamage]"), m_cRoomIsDamage);
	RFX_Text(pFX, _T("[cRoomRemark]"), m_cRoomRemark);
	RFX_Text(pFX, _T("[tBuildAddress]"), m_tBuildAddress);
	RFX_Text(pFX, _T("[tBuildManager]"), m_tBuildManager);
	RFX_Text(pFX, _T("[tBuildRemark]"), m_tBuildRemark);
	RFX_Text(pFX, _T("[tBuildPhone]"), m_tBuildPhone);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetTBCInfo ���

#ifdef _DEBUG
void CRecordsetTBCInfo::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetTBCInfo::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


