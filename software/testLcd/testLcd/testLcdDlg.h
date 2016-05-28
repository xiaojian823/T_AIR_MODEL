
// testLcdDlg.h : header file
//

#pragma once

#include "CommuSerialPort.h"
#include "afxwin.h"
// CtestLcdDlg dialog
class CtestLcdDlg : public CDialogEx
{
// Construction
public:
	CtestLcdDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TESTLCD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
public:
	CCommuSerialPort m_serPort;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CComboBox m_selCommPort;
};
