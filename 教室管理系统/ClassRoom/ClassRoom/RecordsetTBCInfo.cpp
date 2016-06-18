// RecordsetTBCInfo.h : CRecordsetTBCInfo 类的实现



// CRecordsetTBCInfo 实现

// 代码生成在 2013年1月7日, 21:25

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
// #error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CRecordsetTBCInfo::GetDefaultConnect()
{
	return _T("DSN=\x6559\x5ba4\x4fe1\x606f\x7ba1\x7406\x7cfb\x7edf;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x6559\x5ba4\x7ba1\x7406\x7cfb\x7edf;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CRecordsetTBCInfo::GetDefaultSQL()
{
	return _T("[dbo].[教学楼教室信息视图]");
}

void CRecordsetTBCInfo::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
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
// CRecordsetTBCInfo 诊断

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


