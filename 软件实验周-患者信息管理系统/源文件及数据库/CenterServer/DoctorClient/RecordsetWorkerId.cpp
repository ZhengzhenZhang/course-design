// RecordsetWorkerId.h : CRecordsetWorkerId 类的实现



// CRecordsetWorkerId 实现

// 代码生成在 2012年12月28日, 10:11

#include "stdafx.h"
#include "RecordsetWorkerId.h"
IMPLEMENT_DYNAMIC(CRecordsetWorkerId, CRecordset)

CRecordsetWorkerId::CRecordsetWorkerId(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_workerID = L"";
	m_workerPas = L"";
	m_workerStyle = 0;
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
// #error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CRecordsetWorkerId::GetDefaultConnect()
{
	return _T("DSN=\x60a3\x8005\x5c31\x8bca\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x60a3\x8005\x5c31\x8bca\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CRecordsetWorkerId::GetDefaultSQL()
{
	return _T("[dbo].[职工信息]");
}

void CRecordsetWorkerId::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[workerID]"), m_workerID);
	RFX_Text(pFX, _T("[workerPas]"), m_workerPas);
	RFX_Long(pFX, _T("[workerStyle]"), m_workerStyle);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetWorkerId 诊断

#ifdef _DEBUG
void CRecordsetWorkerId::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetWorkerId::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


