// RegisterClientDoc.h : CRegisterClientDoc ��Ľӿ�
//


#pragma once


class CRegisterClientDoc : public CDocument
{
protected: // �������л�����
	CRegisterClientDoc();
	DECLARE_DYNCREATE(CRegisterClientDoc)

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
	virtual ~CRegisterClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


