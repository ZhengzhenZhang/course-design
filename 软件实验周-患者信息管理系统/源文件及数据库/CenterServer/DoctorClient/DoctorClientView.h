// DoctorClientView.h : CDoctorClientView 类的接口
//


#pragma once


class CDoctorClientView : public CListView
{
protected: // 仅从序列化创建
	CDoctorClientView();
	DECLARE_DYNCREATE(CDoctorClientView)

// 属性
public:
	CDoctorClientDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CDoctorClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // DoctorClientView.cpp 中的调试版本
inline CDoctorClientDoc* CDoctorClientView::GetDocument() const
   { return reinterpret_cast<CDoctorClientDoc*>(m_pDocument); }
#endif

