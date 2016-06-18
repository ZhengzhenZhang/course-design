// RecordsetCS.h : CRecordsetCS ������

#pragma once

// ���������� 2013��1��6��, 23:38

class CRecordsetCS : public CRecordset
{
public:
	CRecordsetCS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRecordsetCS)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	CStringW	m_tBuildNum;
	CStringW	m_cRoomNum;
	long	m_csWeek;
	CStringW	m_csFirst;
	CStringW	m_csSecond;
	CStringW	m_csThird;
	CStringW	m_csFourth;
	CStringW	m_csFifth;

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


