// CenterServerView.h : CCenterServerView 类的接口
//


#pragma once


class CCenterServerView : public CListView
{
protected: // 仅从序列化创建
	CCenterServerView();
	DECLARE_DYNCREATE(CCenterServerView)

// 属性
public:
	CCenterServerDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CCenterServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMyPatient();
	afx_msg void OnMyDiag();
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMySearch();
	afx_msg void OnMymenuAdd();
	afx_msg void OnMymenuDelete();
	afx_msg void OnMymenuModify();
	afx_msg void OnOK();
	afx_msg void OnMymenuAddnew();
	afx_msg void OnMymenuConfigport();
	// afx_msg void OnCbnSelendokSearch();

public:
	int m_whichList;	// 1代表患者信息，2代表就诊信息，3代表搜索信息
	int m_ifSearch;		// 0代表没有搜索，1代表为搜索结果
	
	// 各客户端端口号 初始化从5001开始(已废弃)
	UINT m_uintRegPort;
	UINT m_uintDocPort;
	UINT m_uintFeePort;

public:
	void ClearList();
	void CreateDiagLayout();
	void CreatePatientLayout();
	void ListPatientInfo(CString strSQL);
	void ListDiagInfo(CString strSQL);	
	void SuperSearch(CString strSearch);
	void DialogOprate(int m_whichOperate); 
	void DleteInfo();
	void DleteInfoItem(CString strDelete, BOOL bInfo = FALSE);
	
	
	afx_msg void OnPatientListen();
};

#ifndef _DEBUG  // CenterServerView.cpp 中的调试版本
inline CCenterServerDoc* CCenterServerView::GetDocument() const
   { return reinterpret_cast<CCenterServerDoc*>(m_pDocument); }
#endif

