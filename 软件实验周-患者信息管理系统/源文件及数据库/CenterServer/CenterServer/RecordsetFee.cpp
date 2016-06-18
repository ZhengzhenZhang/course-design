// RecordsetFee.h : CRecordsetFee 类的实现



// CRecordsetFee 实现

// 代码生成在 2012年12月26日, 23:45

#include "stdafx.h"
#include "RecordsetFee.h"
IMPLEMENT_DYNAMIC(CRecordsetFee, CRecordset)

CRecordsetFee::CRecordsetFee(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_diagNum;
	m_feeDrug = 0.0;
	m_feeDiag = 0.0;
	m_feeTransfusion = 0.0;
	m_feeCheck = 0.0;
	m_feeConsumable = 0.0;
	m_feeRadiate = 0.0;
	m_feeTotal = 0.0;
	m_feedback = L"";
	m_nFields = 9;
	m_nDefaultType = dynaset;
}
// #error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CRecordsetFee::GetDefaultConnect()
{
	return _T("DSN=\x60a3\x8005\x5c31\x8bca\x6570\x636e\x5e93;APP=Microsoft\x00ae Visual Studio\x00ae 2008;WSID=CHINA-D193224A2;DATABASE=\x60a3\x8005\x5c31\x8bca\x6570\x636e\x5e93;Network=DBMSSOCN;Trusted_Connection=Yes");
}

CString CRecordsetFee::GetDefaultSQL()
{
	return _T("[dbo].[费用及恢复情况]");
}

void CRecordsetFee::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Date(pFX, _T("[diagNum]"), m_diagNum);
	RFX_Single(pFX, _T("[feeDrug]"), m_feeDrug);
	RFX_Single(pFX, _T("[feeDiag]"), m_feeDiag);
	RFX_Single(pFX, _T("[feeTransfusion]"), m_feeTransfusion);
	RFX_Single(pFX, _T("[feeCheck]"), m_feeCheck);
	RFX_Single(pFX, _T("[feeConsumable]"), m_feeConsumable);
	RFX_Single(pFX, _T("[feeRadiate]"), m_feeRadiate);
	RFX_Single(pFX, _T("[feeTotal]"), m_feeTotal);
	RFX_Text(pFX, _T("[feedback]"), m_feedback);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetFee 诊断

#ifdef _DEBUG
void CRecordsetFee::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetFee::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


