// DoctorClientDoc.cpp : CDoctorClientDoc 类的实现
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


// CDoctorClientDoc 构造/析构

CDoctorClientDoc::CDoctorClientDoc()
{
	// TODO: 在此添加一次性构造代码

}

CDoctorClientDoc::~CDoctorClientDoc()
{
}

BOOL CDoctorClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CDoctorClientDoc 序列化

void CDoctorClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CDoctorClientDoc 诊断

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


// CDoctorClientDoc 命令
