// MyMowayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyMoway.h"
#include "MyMowayDlg.h"
//#include "CMoway.h"
#include "MyBehaviours.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BEHAVIOUR_TIMER		1
#define SAMPLE_TIME			250

int mowayId = 0;
bool alive = false;
bool fear = false;
bool aggression = false;
bool love = false;
bool explore = false;
bool line = false;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMyMowayDlg dialog




CMyMowayDlg::CMyMowayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyMowayDlg::IDD, pParent)
	, mowayId(9)
	, ORIGEN_X(1)
	, ORIGEN_Y(1)
	, DESTINO_X(3)
	, DESTINO_Y(2)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyMowayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mowayId);
	DDV_MinMaxInt(pDX, mowayId, 0, 14);
	DDX_Control(pDX, IDC_BUTTON_ALIVE, m_alive);
	DDX_Control(pDX, IDC_BUTTON_FEAR, m_fear);
	DDX_Control(pDX, IDC_BUTTON_AGGRESSION, m_aggression);
	DDX_Control(pDX, IDC_BUTTON_LOVE, m_love);
	DDX_Control(pDX, IDC_BUTTON_EXPLORE, m_explore);
	DDX_Control(pDX, IDC_BUTTON_LINE, m_line);
	DDX_Text(pDX, IDC_EDIT2, ORIGEN_X);
	DDX_Text(pDX, IDC_EDIT3, ORIGEN_Y);
	DDX_Text(pDX, IDC_EDIT4, DESTINO_X);
	DDX_Text(pDX, IDC_EDIT5, DESTINO_Y);
}

BEGIN_MESSAGE_MAP(CMyMowayDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CMyMowayDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CMyMowayDlg::OnBnClickedButtonDisconnect)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CMyMowayDlg::OnEnterMowayId)
	ON_BN_CLICKED(IDC_BUTTON_ALIVE, &CMyMowayDlg::OnBnClickedButtonAlive)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_FEAR, &CMyMowayDlg::OnBnClickedButtonFear)
	ON_BN_CLICKED(IDC_BUTTON_AGGRESSION, &CMyMowayDlg::OnBnClickedButtonAggression)
	ON_BN_CLICKED(IDC_BUTTON_LOVE, &CMyMowayDlg::OnBnClickedButtonLove)
	ON_BN_CLICKED(IDC_BUTTON_EXPLORE, &CMyMowayDlg::OnBnClickedButtonExplore)
	ON_BN_CLICKED(IDC_BUTTON_LINE, &CMyMowayDlg::OnBnClickedButtonLine)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CMyMowayDlg::OnEnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, &CMyMowayDlg::OnEnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT4, &CMyMowayDlg::OnEnKillfocusEdit4)
	ON_EN_KILLFOCUS(IDC_EDIT5, &CMyMowayDlg::OnEnKillfocusEdit5)
END_MESSAGE_MAP()


// CMyMowayDlg message handlers

BOOL CMyMowayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyMowayDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyMowayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyMowayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMyMowayDlg::OnEnterMowayId()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	UpdateData(TRUE);
	if ((mowayId < 1) || (mowayId > 14))
	{
		AfxMessageBox("Please type a valid mOway robot id (1 - 14)");
		mowayId = 0;
		UpdateData(FALSE);
	}
}


void CMyMowayDlg::OnBnClickedButtonConnect()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	UpdateData(TRUE);
	if (mowayId == 0)
		AfxMessageBox("Please first type moway robot id");
	else
		if ((mowayId < 1) || (mowayId > 14))
		{
			AfxMessageBox("Please type a valid mOway robot id (1 - 14)");
			mowayId = 0;
		}
		else
		{
			mymoway.ConnectMoway(mowayId);
			mymoway.ChangeLEDState(CMoway::LED_FRONT,CMoway::ON);
			Sleep(300);
			mymoway.ChangeLEDState(CMoway::LED_FRONT,CMoway::OFF);
			Sleep(300);
			mymoway.ChangeLEDState(CMoway::LED_FRONT,CMoway::ON);
			Sleep(300);
			mymoway.ChangeLEDState(CMoway::LED_FRONT,CMoway::OFF);
		}
}

void CMyMowayDlg::OnBnClickedButtonDisconnect()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	UpdateData(TRUE);
	if (alive || fear || aggression || love || explore)
	{
		KillTimer(BEHAVIOUR_TIMER);
		Sleep(SAMPLE_TIME);
		mymoway.MotorStop();
	}
	mymoway.DisconnectMoway();
}


void CMyMowayDlg::OnBnClickedButtonAlive()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	if (mowayId == 0) return;
	if (alive)
	{
		KillTimer(BEHAVIOUR_TIMER);
		Sleep(SAMPLE_TIME);
		mymoway.MotorStop();
		mymoway.ChangeLEDState(CMoway::LED_FRONT,CMoway::OFF);
		alive = false;
		m_alive.SetWindowTextA("Start Alive");
		UpdateData(FALSE);
		return;
	}
	alive = true;
	fear = false;
	aggression = false;
	love = false;
	explore = false;
	line = false;
	SetTimer(BEHAVIOUR_TIMER,SAMPLE_TIME,NULL);
	m_alive.SetWindowTextA("Stop Alive");
	UpdateData(FALSE);
}

void CMyMowayDlg::OnBnClickedButtonFear()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	if (mowayId == 0) return;
	if (fear)
	{
		KillTimer(BEHAVIOUR_TIMER);
		Sleep(SAMPLE_TIME);
		mymoway.MotorStop();
		mymoway.ChangeLEDState(CMoway::LED_FRONT,CMoway::OFF);
		fear = false;
		m_fear.SetWindowTextA("Start Fear");
		UpdateData(FALSE);
		return;
	}
	alive = false;
	fear = true;
	aggression = false;
	love = false;
	explore = false;
	line = false;
	SetTimer(BEHAVIOUR_TIMER,SAMPLE_TIME,NULL);
	m_fear.SetWindowTextA("Stop Fear");
	UpdateData(FALSE);
}

void CMyMowayDlg::OnBnClickedButtonAggression()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	if (mowayId == 0) return;
	if (aggression)
	{
		KillTimer(BEHAVIOUR_TIMER);
		Sleep(SAMPLE_TIME);
		mymoway.MotorStop();
		mymoway.ChangeLEDState(CMoway::LED_FRONT,CMoway::OFF);
		aggression = false;
		m_aggression.SetWindowTextA("Start Aggr.");
		UpdateData(FALSE);
		return;
	}
	alive = false;
	fear = false;
	aggression = true;
	love = false;
	explore = false;
	line = false;
	SetTimer(BEHAVIOUR_TIMER,SAMPLE_TIME,NULL);
	m_aggression.SetWindowTextA("Stop Aggr.");
	UpdateData(FALSE);
}

void CMyMowayDlg::OnBnClickedButtonLove()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	if (mowayId == 0) return;
	if (love)
	{
		KillTimer(BEHAVIOUR_TIMER);
		Sleep(SAMPLE_TIME);
		mymoway.MotorStop();
		mymoway.ChangeLEDState(CMoway::LED_FRONT,CMoway::OFF);
		love = false;
		m_love.SetWindowTextA("Start Love");
		UpdateData(FALSE);
		return;
	}
	alive = false;
	fear = false;
	aggression = false;
	love = true;
	explore = false;
	line = false;
	SetTimer(BEHAVIOUR_TIMER,SAMPLE_TIME,NULL);
	m_love.SetWindowTextA("Stop Love");
	UpdateData(FALSE);
}

void CMyMowayDlg::OnBnClickedButtonExplore()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	if (mowayId == 0) return;
	if (explore)
	{
		KillTimer(BEHAVIOUR_TIMER);
		Sleep(SAMPLE_TIME);
		mymoway.MotorStop();
		mymoway.ChangeLEDState(CMoway::LED_FRONT,CMoway::OFF);
		explore = false;
		m_explore.SetWindowTextA("Start Explore");
		UpdateData(FALSE);
		return;
	}
	alive = false;
	fear = false;
	aggression = false;
	love = false;
	explore = true;
	line = false;
	SetTimer(BEHAVIOUR_TIMER,SAMPLE_TIME,NULL);
	m_explore.SetWindowTextA("Stop Explore");
	UpdateData(FALSE);
}

void CMyMowayDlg::OnBnClickedButtonLine()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	if (mowayId == 0) return;
	if (line)
	{
		KillTimer(BEHAVIOUR_TIMER);
		Sleep(SAMPLE_TIME);
		mymoway.MotorStop();
		mymoway.ChangeLEDState(CMoway::LED_FRONT,CMoway::OFF);
		line = false;
		m_line.SetWindowTextA("Start Line");
		UpdateData(FALSE);
		return;
	}
	alive = false;
	fear = false;
	aggression = false;
	love = false;
	explore = false;
	line = true;
	SetTimer(BEHAVIOUR_TIMER,SAMPLE_TIME,NULL);
	m_line.SetWindowTextA("Stop Line");
	UpdateData(FALSE);
}

void CMyMowayDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Agregue aquí su código de controlador de mensajes o llame al valor predeterminado
	if (nIDEvent != BEHAVIOUR_TIMER) return;

	if (alive)
	{
		//TODO1: IMPLEMENT ALIVE BEHAVIOUR:

		aliveBehaviour(&mymoway, ORIGEN_X, ORIGEN_Y, DESTINO_X, DESTINO_Y);
		OnBnClickedButtonAlive();

		// END OF YOUR IMPLEMENTATION FOR ALIVE BEHAVIOUR
	}

	if (fear)
	{
		//TODO2: IMPLEMENT FEAR BEHAVIOUR:

		fearBehaviour(&mymoway);

		// END OF YOUR IMPLEMENTATION FOR FEAR BEHAVIOUR
	}

	if (aggression)
	{
		//TODO3: IMPLEMENT AGGRESSION BEHAVIOUR:

		aggressionBehaviour(&mymoway);

		// END OF YOUR IMPLEMENTATION FOR AGGRESSION BEHAVIOUR
	}

	if (love)
	{
		//TODO4: IMPLEMENT LOVE BEHAVIOUR:
      
		loveBehaviour(&mymoway);

		// END OF YOUR IMPLEMENTATION FOR LOVE BEHAVIOUR
	}

	if (explore)
	{
		//TODO5: IMPLEMENT EXPLORE BEHAVIOUR:

		exploreBehaviour(&mymoway);

		// END OF YOUR IMPLEMENTATION FOR EXPLORE BEHAVIOUR
	}

	if (line)
	{
		//TODO6: IMPLEMENT LINE FOLLOWING BEHAVIOUR:

		lineBehaviour(&mymoway);

		// END OF YOUR IMPLEMENTATION FOR LINE FOLLOWING BEHAVIOUR
	}

	CDialog::OnTimer(nIDEvent);
}



void CMyMowayDlg::OnEnKillfocusEdit2()
{
	UpdateData(TRUE);
	// TODO: Agregue aquí su código de controlador de notificación de control
}


void CMyMowayDlg::OnEnKillfocusEdit3()
{
	UpdateData(TRUE);
	// TODO: Agregue aquí su código de controlador de notificación de control
}


void CMyMowayDlg::OnEnKillfocusEdit4()
{
	UpdateData(TRUE);
	// TODO: Agregue aquí su código de controlador de notificación de control
	UpdateData(TRUE);
}


void CMyMowayDlg::OnEnKillfocusEdit5()
{
	UpdateData(TRUE);
	// TODO: Agregue aquí su código de controlador de notificación de control

}
