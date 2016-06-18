// DtlDrugSet.h : CDtlDrugSet ������

#pragma once

// ���������� 2012��6��15��, 0:57

class CDtlDrugSet : public CRecordset
{
public:
	CDtlDrugSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDtlDrugSet)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	CStringW	m_code;
	CStringW	m_name;
	CStringW	m_specification;
	CStringW	m_efficacy;
	CStringW	m_ingredient;
	CStringW	m_dosage;
	float	m_selPrice;
	long	m_counts;

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


