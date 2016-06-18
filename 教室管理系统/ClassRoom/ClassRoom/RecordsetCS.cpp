// RecordsetCS.h : CRecordsetCS 类的实现



// CRecordsetCS 实现

// 代码生成在 2013年1月6日, 23:38

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
// #error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CRecordsetCS::GetDefaultConnect()
{
	return _T("DSN=\x6559\x5ba4\x4fe1\x606f\x7ba1\x7406\x7cfb\x7edf;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x6559\x5ba4\x7ba1\x7406\x7cfb\x7edf;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CRecordsetCS::GetDefaultSQL()
{
	return _T("[dbo].[教学楼排课信息视图]");
}

void CRecordsetCS::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
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
// CRecordsetCS 诊断

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


