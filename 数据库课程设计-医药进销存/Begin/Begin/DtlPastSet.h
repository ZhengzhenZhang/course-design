// DtlPastSet.h : CDtlPastSet ������

#pragma once

// ���������� 2012��6��18��, 10:48

class CDtlPastSet : public CRecordset
{
public:
	CDtlPastSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDtlPastSet)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	CTime	m_dealTime;
	CStringW	m_code;
	CStringW	m_name;
	CStringW	m_specification;
	CTime	m_pastTime;
	long	m_dealNum;
	float	m_totalValue;
	long	m_counts;
	CStringW	m_ID;
	CStringW	m_dealMark;

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


