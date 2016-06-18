// DoctorClientView.h : CDoctorClientView ��Ľӿ�
//


#pragma once


class CDoctorClientView : public CListView
{
protected: // �������л�����
	CDoctorClientView();
	DECLARE_DYNCREATE(CDoctorClientView)

// ����
public:
	CDoctorClientDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CDoctorClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DoctorClientView.cpp �еĵ��԰汾
inline CDoctorClientDoc* CDoctorClientView::GetDocument() const
   { return reinterpret_cast<CDoctorClientDoc*>(m_pDocument); }
#endif

