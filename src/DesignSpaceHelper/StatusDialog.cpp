// StatusDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "StatusDialog.h"


// CStatusDialog dialog

IMPLEMENT_DYNAMIC(CStatusDialog, CDialog)

CStatusDialog::CStatusDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CStatusDialog::IDD, pParent),
	  processPos(0)
{
	m_maxPrg  = 100;
	m_cancel = false;
}

CStatusDialog::~CStatusDialog()
{
}

void CStatusDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_prgBar);
	DDX_Control(pDX, IDC_EDIT1, m_status);
}


BEGIN_MESSAGE_MAP(CStatusDialog, CDialog)
//	ON_BN_CLICKED(IDC_CANCELBTN, &CStatusDialog::OnBnClickedCancelbtn)
END_MESSAGE_MAP()

BOOL CStatusDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	//splash

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CStatusDialog::SetProgress(const CString &status)
{
	if(processPos > m_maxPrg) processPos = 0;
	m_prgBar.SetRange( 0, m_maxPrg);
	m_prgBar.SetPos(processPos);

	processPos += 10;

	m_status.SetWindowText(status);

	this->UpdateData();
	this->UpdateWindow();
	this->RedrawWindow();
	this->ShowWindow(SW_SHOW);
}

void CStatusDialog::OnFinished()
{
	CDialog::OnCancel();
}

void CStatusDialog::SetRange(int range)
{
	if(range > m_maxPrg)
		m_maxPrg = range;
};

CStatusDialog * GetStatusDlg(CStatusDialog * set)
{
	static CStatusDialog * csdlg;
	
	if (set) {
		csdlg = set;
	}
	ASSERT(csdlg != NULL);
	return csdlg;
};

void CStatusDialog::OnCancel()
{
	// TODO: Add your control notification handler code here
	m_cancel = true;
	CDialog::OnCancel();
}

void CStatusDialog::PostNcDestroy() 
{
	CDialog::PostNcDestroy();
	delete this; 
}
