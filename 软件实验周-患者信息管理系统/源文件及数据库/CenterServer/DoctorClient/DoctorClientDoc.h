// DoctorClientDoc.h : CDoctorClientDoc ��Ľӿ�
//


#pragma once


class CDoctorClientDoc : public CDocument
{
protected: // �������л�����
	CDoctorClientDoc();
	DECLARE_DYNCREATE(CDoctorClientDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CDoctorClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


