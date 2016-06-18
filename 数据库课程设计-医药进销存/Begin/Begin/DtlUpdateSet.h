// DtlUpdateSet.h : CDtlUpdateSet ������

#pragma once

// ���������� 2012��6��17��, 20:31

class CDtlUpdateSet : public CRecordset
{
public:
	CDtlUpdateSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDtlUpdateSet)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	CTime	m_upTime;
	CStringW	m_code;
	CStringW	m_name;
	CStringW	m_specification;
	float	m_upPrice;
	long	m_upNum;
	long	m_upCounts;
	CStringW	m_ID;
	CStringW	m_upMark;

// ��д
	// �����ɵ��麯����д
	public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


