// RecordsetFee.h : CRecordsetFee 的声明

#pragma once

// 代码生成在 2012年12月26日, 23:45

class CRecordsetFee : public CRecordset
{
public:
	CRecordsetFee(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRecordsetFee)

// 字段/参数数据

// 以下字符串类型(如果存在)反映数据库字段(ANSI 数据类型的 CStringA 和 Unicode
// 数据类型的 CStringW)的实际数据类型。
//  这是为防止 ODBC 驱动程序执行可能
// 不必要的转换。如果希望，可以将这些成员更改为
// CString 类型，ODBC 驱动程序将执行所有必要的转换。
// (注意: 必须使用 3.5 版或更高版本的 ODBC 驱动程序
// 以同时支持 Unicode 和这些转换)。

	CTime	m_diagNum;
	float	m_feeDrug;
	float	m_feeDiag;
	float	m_feeTransfusion;
	float	m_feeCheck;
	float	m_feeConsumable;
	float	m_feeRadiate;
	float	m_feeTotal;
	CStringW	m_feedback;

// 重写
	// 向导生成的虚函数重写
	public:
	virtual CString GetDefaultConnect();	// 默认连接字符串

	virtual CString GetDefaultSQL(); 	// 记录集的默认 SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX 支持

// 实现
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


