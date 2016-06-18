// RegisterClientView.h : CRegisterClientView 类的接口
//


#pragma once

class CRegisterClientView : public CListView
{
protected: // 仅从序列化创建
	CRegisterClientView();
	DECLARE_DYNCREATE(CRegisterClientView)

// 属性
public:
	CRegisterClientDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CRegisterClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMymenuPatientinfo();
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // RegisterClientView.cpp 中的调试版本
inline CRegisterClientDoc* CRegisterClientView::GetDocument() const
   { return reinterpret_cast<CRegisterClientDoc*>(m_pDocument); }
#endif

