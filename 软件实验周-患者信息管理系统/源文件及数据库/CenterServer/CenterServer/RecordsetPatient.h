// RecordsetPatient.h : CRecordsetPatient ������

#pragma once

// ���������� 2012��12��25��, 16:58

class CRecordsetPatient : public CRecordset
{
public:
	CRecordsetPatient(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRecordsetPatient)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	CStringW	m_idNumber;
	CStringW	m_patientName;
	CStringW	m_patientSex;
	long	m_patientAge;
	CStringW	m_patientPhone;
	CStringW	m_patientAddress;
	CStringW	m_patientNum;
	CStringW	m_patientAllergy;
	CStringW	m_patientRemark;

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


