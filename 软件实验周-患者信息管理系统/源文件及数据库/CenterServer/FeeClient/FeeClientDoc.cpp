// FeeClientDoc.cpp : CFeeClientDoc ���ʵ��
//

#include "stdafx.h"
#include "FeeClient.h"

#include "FeeClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFeeClientDoc

IMPLEMENT_DYNCREATE(CFeeClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CFeeClientDoc, CDocument)
END_MESSAGE_MAP()


// CFeeClientDoc ����/����

CFeeClientDoc::CFeeClientDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CFeeClientDoc::~CFeeClientDoc()
{
}

BOOL CFeeClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CFeeClientDoc ���л�

void CFeeClientDoc::Serialize(CArchive& ar)
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


// CFeeClientDoc ���

#ifdef _DEBUG
void CFeeClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFeeClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFeeClientDoc ����
