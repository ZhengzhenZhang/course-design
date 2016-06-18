// RecordsetOC.h : CRecordsetOC 类的实现



// CRecordsetOC 实现

// 代码生成在 2013年1月8日, 1:35

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
// #error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CRecordsetOC::GetDefaultConnect()
{
	return _T("DSN=\x6559\x5ba4\x4fe1\x606f\x7ba1\x7406\x7cfb\x7edf;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x6559\x5ba4\x7ba1\x7406\x7cfb\x7edf;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CRecordsetOC::GetDefaultSQL()
{
	return _T("[dbo].[教室占用信息表]");
}

void CRecordsetOC::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
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
// CRecordsetOC 诊断

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


