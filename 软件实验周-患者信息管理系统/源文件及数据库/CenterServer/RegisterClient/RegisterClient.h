// RegisterClient.h : RegisterClient Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CRegisterClientApp:
// �йش����ʵ�֣������ RegisterClient.cpp
//

class CRegisterClientApp : public CWinApp
{
public:
	CRegisterClientApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRegisterClientApp theApp;