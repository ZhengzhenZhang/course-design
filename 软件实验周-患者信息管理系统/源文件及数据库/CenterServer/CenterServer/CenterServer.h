// CenterServer.h : CenterServer Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CCenterServerApp:
// �йش����ʵ�֣������ CenterServer.cpp
//

class CCenterServerApp : public CWinApp
{
public:
	CCenterServerApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCenterServerApp theApp;