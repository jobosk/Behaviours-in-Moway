// MyMowayDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CMyMowayDlg dialog
class CMyMowayDlg : public CDialog
{
// Construction
public:
	CMyMowayDlg(CWnd* pParent = NULL);	// standard constructor
	CMoway mymoway;

// Dialog Data
	enum { IDD = IDD_MYMOWAY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


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
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	int mowayId;
	afx_msg void OnEnterMowayId();
	afx_msg void OnBnClickedButtonAlive();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_alive;
	CButton m_fear;
	afx_msg void OnBnClickedButtonFear();
	CButton m_aggression;
	afx_msg void OnBnClickedButtonAggression();
	CButton m_love;
	afx_msg void OnBnClickedButtonLove();
	CButton m_explore;
	afx_msg void OnBnClickedButtonExplore();
	CButton m_line;
	afx_msg void OnBnClickedButtonLine();
	afx_msg void OnEnKillfocusEdit2();
	int ORIGEN_X;
	int ORIGEN_Y;
	afx_msg void OnEnKillfocusEdit3();
	int DESTINO_X;
	afx_msg void OnEnKillfocusEdit4();
	int DESTINO_Y;
	afx_msg void OnEnKillfocusEdit5();
};
