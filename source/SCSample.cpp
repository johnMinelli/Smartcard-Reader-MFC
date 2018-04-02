/****************************************************************************/
/*                                                                          */
/*         Copyright 1997 SCM Microsystems                                  */
/*                                                                          */
/*         This software is supplied under the terms of a license           */
/*         agreement or nondisclosure agreement and may not be copied       */
/*         or disclosed except in accordance with the terms of that         */
/*         agreement.                                                       */
/*                                                                          */
/****************************************************************************/
/*                                                                          */
/* Author         : Kerstin Jenett											*/
/* Creation date  : 07.10.1997												*/
/* Name           : SCSample.cpp (Defines the class behaviors               */
/*								  for the application.)                     */
/*                                                                          */
/* Description    : Resource Manager Sample for Windows 95 and				*/
/*                  Windows NT4.0											*/
/*                                                                          */
/****************************************************************************/
/*																			*/
/* Rev. Date        Author      Description									*/
/*--------------------------------------------------------------------------*/
/* 1.00	07.10.1997	K.Jenett	initial version								*/
/****************************************************************************/

#include "stdafx.h"
#include "SCSample.h"
#include "SCSampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSCSampleApp

BEGIN_MESSAGE_MAP(CSCSampleApp, CWinApp)
	//{{AFX_MSG_MAP(CSCSampleApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSCSampleApp construction

CSCSampleApp::CSCSampleApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSCSampleApp object

CSCSampleApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSCSampleApp initialization

BOOL CSCSampleApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CSCSampleDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
