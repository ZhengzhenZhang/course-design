// DoctorClientDoc.cpp : CDoctorClientDoc ���ʵ��
//

#include "stdafx.h"
#include "DoctorClient.h"

#include "DoctorClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDoctorClientDoc

IMPLEMENT_DYNCREATE(CDoctorClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CDoctorClientDoc, CDocument)
END_MESSAGE_MAP()


// CDoctorClientDoc ����/����

CDoctorClientDoc::CDoctorClientDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CDoctorClientDoc::~CDoctorClientDoc()
{
}

BOOL CDoctorClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CDoctorClientDoc ���л�

void CDoctorClientDoc::Serialize(CArchive& ar)
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


// CDoctorClientDoc ���

#ifdef _DEBUG
void CDoctorClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDoctorClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDoctorClientDoc ����
