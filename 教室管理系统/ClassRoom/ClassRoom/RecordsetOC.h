// RecordsetOC.h : CRecordsetOC ������

#pragma once

// ���������� 2013��1��8��, 1:35

class CRecordsetOC : public CRecordset
{
public:
	CRecordsetOC(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRecordsetOC)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	CStringW	m_ocTime;
	CStringW	m_cRoomNum;
	CStringW	m_ocFirst;
	CStringW	m_ocSecond;
	CStringW	m_ocThird;
	CStringW	m_ocFourth;
	CStringW	m_ocFifth;
	CStringW	m_ocOther;

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


