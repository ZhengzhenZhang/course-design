// FeeClientView.h : CFeeClientView ��Ľӿ�
//


#pragma once


class CFeeClientView : public CListView
{
protected: // �������л�����
	CFeeClientView();
	DECLARE_DYNCREATE(CFeeClientView)

// ����
public:
	CFeeClientDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CFeeClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // FeeClientView.cpp �еĵ��԰汾
inline CFeeClientDoc* CFeeClientView::GetDocument() const
   { return reinterpret_cast<CFeeClientDoc*>(m_pDocument); }
#endif

