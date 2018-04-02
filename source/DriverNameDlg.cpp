// DriverNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SCSample.h"
#include "DriverNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDriverNameDlg dialog


CDriverNameDlg::CDriverNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDriverNameDlg::IDD, pParent)
{
	act_Name = 0;
	//{{AFX_DATA_INIT(CDriverNameDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDriverNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDriverNameDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDriverNameDlg, CDialog)
	//{{AFX_MSG_MAP(CDriverNameDlg)
	ON_CBN_SELCHANGE(IDC_DRIVER_NAME, OnSelchangeDriverName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDriverNameDlg message handlers

void CDriverNameDlg::OnSelchangeDriverName() 
{
	CComboBox *pbox1 = (CComboBox*)GetDlgItem(IDC_DRIVER_NAME);
	act_Name = pbox1->GetCurSel();
	
}

BOOL CDriverNameDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CComboBox *pbox1 = (CComboBox*)GetDlgItem(IDC_DRIVER_NAME);
	pbox1->ResetContent();
	for (int i=0; i<Count; i++)
		pbox1->InsertString(i, Name+(i*100));                             
	pbox1->EnableWindow(TRUE);
	pbox1->SetItemData(0, act_Name);
	pbox1->SetCurSel(act_Name);	                            

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

