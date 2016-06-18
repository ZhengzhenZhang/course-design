// CenterServerView.h : CCenterServerView ��Ľӿ�
//


#pragma once


class CCenterServerView : public CListView
{
protected: // �������л�����
	CCenterServerView();
	DECLARE_DYNCREATE(CCenterServerView)

// ����
public:
	CCenterServerDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CCenterServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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
	int m_whichList;	// 1��������Ϣ��2���������Ϣ��3����������Ϣ
	int m_ifSearch;		// 0����û��������1����Ϊ�������
	
	// ���ͻ��˶˿ں� ��ʼ����5001��ʼ(�ѷ���)
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

#ifndef _DEBUG  // CenterServerView.cpp �еĵ��԰汾
inline CCenterServerDoc* CCenterServerView::GetDocument() const
   { return reinterpret_cast<CCenterServerDoc*>(m_pDocument); }
#endif

