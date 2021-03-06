// RecordsetAdminId.h : CRecordsetAdminId 类的实现



// CRecordsetAdminId 实现

// 代码生成在 2013年1月8日, 9:39

#include "stdafx.h"
#include "RecordsetAdminId.h"
IMPLEMENT_DYNAMIC(CRecordsetAdminId, CRecordset)

CRecordsetAdminId::CRecordsetAdminId(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_adminID = L"";
	m_adminPassword = L"";
	m_nFields = 2;
	m_nDefaultType = dynaset;
}
// #error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CRecordsetAdminId::GetDefaultConnect()
{
	return _T("DSN=\x6559\x5ba4\x4fe1\x606f\x7ba1\x7406\x7cfb\x7edf;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x6559\x5ba4\x7ba1\x7406\x7cfb\x7edf;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CRecordsetAdminId::GetDefaultSQL()
{
	return _T("[dbo].[管理员账号]");
}

void CRecordsetAdminId::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[adminID]"), m_adminID);
	RFX_Text(pFX, _T("[adminPassword]"), m_adminPassword);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetAdminId 诊断

#ifdef _DEBUG
void CRecordsetAdminId::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetAdminId::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


