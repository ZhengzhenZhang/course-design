// RegisterClientDoc.cpp : CRegisterClientDoc ���ʵ��
//

#include "stdafx.h"
#include "RegisterClient.h"

#include "RegisterClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRegisterClientDoc

IMPLEMENT_DYNCREATE(CRegisterClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CRegisterClientDoc, CDocument)
END_MESSAGE_MAP()


// CRegisterClientDoc ����/����

CRegisterClientDoc::CRegisterClientDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CRegisterClientDoc::~CRegisterClientDoc()
{
}

BOOL CRegisterClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CRegisterClientDoc ���л�

void CRegisterClientDoc::Serialize(CArchive& ar)
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


// CRegisterClientDoc ���

#ifdef _DEBUG
void CRegisterClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRegisterClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CRegisterClientDoc ����
