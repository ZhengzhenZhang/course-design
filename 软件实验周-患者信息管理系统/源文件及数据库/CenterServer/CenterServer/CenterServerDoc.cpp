// CenterServerDoc.cpp : CCenterServerDoc 类的实现
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


// CCenterServerDoc 构造/析构

CCenterServerDoc::CCenterServerDoc()
{
	// TODO: 在此添加一次性构造代码
}

CCenterServerDoc::~CCenterServerDoc()
{
}

BOOL CCenterServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	SetTitle(_T("患者信息管理系统"));
	return TRUE;
}


// CCenterServerDoc 序列化

void CCenterServerDoc::Serialize(CArchive& ar)
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


// CCenterServerDoc 诊断

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


// CCenterServerDoc 命令
