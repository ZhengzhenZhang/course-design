// FeeClientView.h : CFeeClientView 类的接口
//


#pragma once


class CFeeClientView : public CListView
{
protected: // 仅从序列化创建
	CFeeClientView();
	DECLARE_DYNCREATE(CFeeClientView)

// 属性
public:
	CFeeClientDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CFeeClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // FeeClientView.cpp 中的调试版本
inline CFeeClientDoc* CFeeClientView::GetDocument() const
   { return reinterpret_cast<CFeeClientDoc*>(m_pDocument); }
#endif

