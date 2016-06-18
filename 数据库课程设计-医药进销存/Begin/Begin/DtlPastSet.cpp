// DtlPastSet.h : CDtlPastSet 类的实现



// CDtlPastSet 实现

// 代码生成在 2012年6月18日, 10:48

#include "stdafx.h"
#include "DtlPastSet.h"
IMPLEMENT_DYNAMIC(CDtlPastSet, CRecordset)

CDtlPastSet::CDtlPastSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_dealTime;
	m_code = L"";
	m_name = L"";
	m_specification = L"";
	m_pastTime;
	m_dealNum = 0;
	m_totalValue = 0.0;
	m_counts = 0;
	m_ID = L"";
	m_dealMark = L"";
	m_nFields = 10;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CDtlPastSet::GetDefaultConnect()
{
	return _T("DSN=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x533b\x836f\x8fdb\x9500\x5b58\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CDtlPastSet::GetDefaultSQL()
{
	return _T("[dbo].[过期药品处理详情]");
}

void CDtlPastSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Date(pFX, _T("[dealTime]"), m_dealTime);
	RFX_Text(pFX, _T("[code]"), m_code);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[specification]"), m_specification);
	RFX_Date(pFX, _T("[pastTime]"), m_pastTime);
	RFX_Long(pFX, _T("[dealNum]"), m_dealNum);
	RFX_Single(pFX, _T("[totalValue]"), m_totalValue);
	RFX_Long(pFX, _T("[counts]"), m_counts);
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[dealMark]"), m_dealMark);

}
/////////////////////////////////////////////////////////////////////////////
// CDtlPastSet 诊断

#ifdef _DEBUG
void CDtlPastSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDtlPastSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


