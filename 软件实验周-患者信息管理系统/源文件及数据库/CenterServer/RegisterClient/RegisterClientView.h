// RegisterClientView.h : CRegisterClientView ��Ľӿ�
//


#pragma once

class CRegisterClientView : public CListView
{
protected: // �������л�����
	CRegisterClientView();
	DECLARE_DYNCREATE(CRegisterClientView)

// ����
public:
	CRegisterClientDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CRegisterClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMymenuPatientinfo();
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // RegisterClientView.cpp �еĵ��԰汾
inline CRegisterClientDoc* CRegisterClientView::GetDocument() const
   { return reinterpret_cast<CRegisterClientDoc*>(m_pDocument); }
#endif

