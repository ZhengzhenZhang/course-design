
// HairCut.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "HairCut.h"
#include "MainFrm.h"

#include "HairCutDoc.h"
#include "HairCutView.h"
#include "DlgReg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHairCutApp

BEGIN_MESSAGE_MAP(CHairCutApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CHairCutApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CHairCutApp ����

CHairCutApp::CHairCutApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("HairCut.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CHairCutApp ����

CHairCutApp theApp;


// CHairCutApp ��ʼ��

BOOL CHairCutApp::InitInstance()
{

	CStdioFile stdFile;

	if (stdFile.Open(_T("Sys\\System.ini"), CFile::modeRead))
	{
		DWORD ser;
		TCHAR namebuf[128];
		TCHAR filebuf[128];
		//��ȡC�̵����к�
		::GetVolumeInformation(_T("c:\\"),namebuf,128,&ser,0,0,filebuf,128);

		CString strMachine;
		unsigned long s1 = 0,s2=0; 
		_asm 
		{ 
			mov eax,01h 
				xor edx,edx 
				cpuid 
				mov s1,edx 
				mov s2,eax 
		}

		strMachine.Format(_T("%u%u"), ser + s1, s1 + s2);

		TCHAR *pChar;

		pChar = strMachine.GetBuffer(strMachine.GetLength());

		int n = _tcslen(pChar);

		TCHAR tcReg[100];
		ZeroMemory(tcReg, sizeof (tcReg));
		int nKey[10] = {8, 9, 0, 7, 1, 5};
		for (int i = 0; i < n; i++)
		{
			int tmp = pChar[i] - _T('0');
			TCHAR tt = ((int)(pow(tmp + 2.0, nKey[i%6]) + 0.1)) % 10;
			tcReg[i%8] = (tcReg[i%8] + tt) % 10;
		}

		for (int i = 0; i < 8; i++)
			tcReg[i] += _T('0');

		CString strRightReg = tcReg;

		CString strReg;
		stdFile.ReadString(strReg);

		if (strReg != strRightReg)
		{
			CDlgReg dlg;
			dlg.m_strMachine = strMachine;
			dlg.m_strRightReg = strRightReg;
			if (IDCANCEL == dlg.DoModal())
			{
				exit(0);
			}

			stdFile.Close();

			CStdioFile stdWrite;
			stdWrite.Open(_T("Sys\\System.ini"), CFile::modeCreate | CFile::modeWrite);
			stdWrite.WriteString(strRightReg);

			stdWrite.Close();
		}
		else
		{
			stdFile.Close();
		}
	}
	else
	{
		AfxMessageBox(_T("�Ҳ���System.ini�ļ���"));
		exit(0);
	}

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("HairCut 1.0"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHairCutDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CHairCutView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	return TRUE;
}

int CHairCutApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CHairCutApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CHairCutApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CHairCutApp �Զ������/���淽��

void CHairCutApp::PreLoadState()
{
// 	BOOL bNameValid;
// 	CString strName;
// 	bNameValid = strName.LoadString(IDS_EDIT_MENU);
// 	ASSERT(bNameValid);
// 	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CHairCutApp::LoadCustomState()
{
}

void CHairCutApp::SaveCustomState()
{
}

// CHairCutApp ��Ϣ�������



