// CenterServerDoc.h : CCenterServerDoc ��Ľӿ�
//


#pragma once


class CCenterServerDoc : public CDocument
{
protected: // �������л�����
	CCenterServerDoc();
	DECLARE_DYNCREATE(CCenterServerDoc)

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
	virtual ~CCenterServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

};


