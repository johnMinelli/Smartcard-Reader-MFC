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
/* Name           : SCSampleDlg.h  (header file)							*/
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

#if !defined(AFX_SCSAMPLEDLG_H__56EC04C7_3EEB_11D1_996E_0080C82AE17C__INCLUDED_)
#define AFX_SCSAMPLEDLG_H__56EC04C7_3EEB_11D1_996E_0080C82AE17C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
//
#define NUMBER_OF_READERS	4
#define NAME_LENGTH			100
#define MAX_INPUT			1024
#define MAX_OUTPUT			4000
#define MAX_RESPONSE		2000

/////////////////////////////////////////////////////////////////////////////
// CSCSampleDlg dialog
#include "winscard.h"




class CSCSampleDlg : public CDialog
{
// Construction
public:
	CSCSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSCSampleDlg)
	enum { IDD = IDD_SCSAMPLE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSCSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	HICON			m_hIcon;
	CString			MessageBuffer;
	long			ret;
	
	PBYTE			pInBuffer;
	long			InBufferLength;

	PBYTE			pOutBuffer;
	int				OutBufferLine;
	short      		line;

	short			act_Name;
	short			ReaderCount;
	char			ReaderName[NUMBER_OF_READERS][NAME_LENGTH];
	PBYTE			pResponseBuffer;
	unsigned long	ResponseLength;
	long			ProtocolType;

	void	UpdateMouseDisplay(void);
	short	AToHex(char *mhstr, BYTE *buf);
	void	GetErrorCode(long ret);

	// Generated message map functions
	//{{AFX_MSG(CSCSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCardDisconnect();
	afx_msg void OnConnect();
	afx_msg void OnTransmit();
	virtual void OnCancel();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCSAMPLEDLG_H__56EC04C7_3EEB_11D1_996E_0080C82AE17C__INCLUDED_)
