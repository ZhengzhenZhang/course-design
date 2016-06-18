// RecordsetFee.h : CRecordsetFee ������

#pragma once

// ���������� 2012��12��26��, 23:45

class CRecordsetFee : public CRecordset
{
public:
	CRecordsetFee(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRecordsetFee)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	CTime	m_diagNum;
	float	m_feeDrug;
	float	m_feeDiag;
	float	m_feeTransfusion;
	float	m_feeCheck;
	float	m_feeConsumable;
	float	m_feeRadiate;
	float	m_feeTotal;
	CStringW	m_feedback;

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


