// FeeClientDoc.h : CFeeClientDoc ��Ľӿ�
//


#pragma once


class CFeeClientDoc : public CDocument
{
protected: // �������л�����
	CFeeClientDoc();
	DECLARE_DYNCREATE(CFeeClientDoc)

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
	virtual ~CFeeClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


