// CenterServerDoc.cpp : CCenterServerDoc ���ʵ��
//

#include "stdafx.h"
#include "CenterServer.h"

#include "CenterServerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCenterServerDoc

IMPLEMENT_DYNCREATE(CCenterServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CCenterServerDoc, CDocument)
END_MESSAGE_MAP()


// CCenterServerDoc ����/����

CCenterServerDoc::CCenterServerDoc()
{
	// TODO: �ڴ����һ���Թ������
}

CCenterServerDoc::~CCenterServerDoc()
{
}

BOOL CCenterServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	SetTitle(_T("������Ϣ����ϵͳ"));
	return TRUE;
}


// CCenterServerDoc ���л�

void CCenterServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
		
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���

	}
}


// CCenterServerDoc ���

#ifdef _DEBUG
void CCenterServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCenterServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCenterServerDoc ����
