// RegisterClientDoc.cpp : CRegisterClientDoc 类的实现
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


// CRegisterClientDoc 构造/析构

CRegisterClientDoc::CRegisterClientDoc()
{
	// TODO: 在此添加一次性构造代码

}

CRegisterClientDoc::~CRegisterClientDoc()
{
}

BOOL CRegisterClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CRegisterClientDoc 序列化

void CRegisterClientDoc::Serialize(CArchive& ar)
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


// CRegisterClientDoc 诊断

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


// CRegisterClientDoc 命令
