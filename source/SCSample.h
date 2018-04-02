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
/* Name           : SCSample.h (main header file for the					*/
/*								SCSAMPLE application)						*/
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

#if !defined(AFX_SCSAMPLE_H__56EC04C5_3EEB_11D1_996E_0080C82AE17C__INCLUDED_)
#define AFX_SCSAMPLE_H__56EC04C5_3EEB_11D1_996E_0080C82AE17C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSCSampleApp:
// See SCSample.cpp for the implementation of this class
//

class CSCSampleApp : public CWinApp
{
public:
	CSCSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSCSampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCSAMPLE_H__56EC04C5_3EEB_11D1_996E_0080C82AE17C__INCLUDED_)
