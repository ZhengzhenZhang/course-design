// FeeClientDoc.cpp : CFeeClientDoc 类的实现
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


// CFeeClientDoc 构造/析构

CFeeClientDoc::CFeeClientDoc()
{
	// TODO: 在此添加一次性构造代码

}

CFeeClientDoc::~CFeeClientDoc()
{
}

BOOL CFeeClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CFeeClientDoc 序列化

void CFeeClientDoc::Serialize(CArchive& ar)
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


// CFeeClientDoc 诊断

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


// CFeeClientDoc 命令
