// DoctorClient.h : DoctorClient Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CDoctorClientApp:
// �йش����ʵ�֣������ DoctorClient.cpp
//

class CDoctorClientApp : public CWinApp
{
public:
	CDoctorClientApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDoctorClientApp theApp;