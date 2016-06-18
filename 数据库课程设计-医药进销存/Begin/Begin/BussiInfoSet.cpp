// BussiInfoSet.h : CBussiInfoSet 类的实现



// CBussiInfoSet 实现

// 代码生成在 2012年6月15日, 15:29

#include "stdafx.h"
#include "BussiInfoSet.h"
IMPLEMENT_DYNAMIC(CBussiInfoSet, CRecordset)

CBussiInfoSet::CBussiInfoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_code = L"";
	m_name = L"";
	m_address = L"";
	m_phone = L"";
	m_remark = L"";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CBussiInfoSet::GetDefaultConnect()
{
	return _T("DSN=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CBussiInfoSet::GetDefaultSQL()
{
	return _T("[dbo].[供货商信息]");
}

void CBussiInfoSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[code]"), m_code);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[address]"), m_address);
	RFX_Text(pFX, _T("[phone]"), m_phone);
	RFX_Text(pFX, _T("[remark]"), m_remark);

}
/////////////////////////////////////////////////////////////////////////////
// CBussiInfoSet 诊断

#ifdef _DEBUG
void CBussiInfoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBussiInfoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


