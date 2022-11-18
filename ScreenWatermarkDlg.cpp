
// ScreenWatermarkDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ScreenWatermark.h"
#include "ScreenWatermarkDlg.h"
#include "afxdialogex.h"
#include "CScreenWatermark.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CScreenWatermarkDlg 对话框



CScreenWatermarkDlg::CScreenWatermarkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCREENWATERMARK_DIALOG, pParent)

	, showUserOpacity(100)
	, showUserAngle(0)
	, pos_1(FALSE)
	, pos_2(FALSE)
	, pos_3(FALSE)
	, pos_4(FALSE)
	, pos_5(FALSE)
	, pos_6(FALSE)
	, pos_7(FALSE)
	, pos_8(FALSE)
	, pos_9(FALSE)
	, pos_all(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScreenWatermarkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, userColor);
	DDX_Control(pDX, IDC_COMBO2, userFontSize);
	DDX_Control(pDX, IDC_COMBO3, userFontName);
	DDX_Control(pDX, IDC_COMBO4, userFontStyle);
	DDX_Control(pDX, IDC_SLIDER1, userOpacity);
	DDX_Control(pDX, IDC_SLIDER2, userAngle);
	DDX_Text(pDX, IDC_EDIT2, showUserOpacity);
	DDX_Text(pDX, IDC_EDIT3, showUserAngle);
	DDX_Check(pDX, IDC_CHECK1, pos_1);
	DDX_Check(pDX, IDC_CHECK2, pos_2);
	DDX_Check(pDX, IDC_CHECK3, pos_3);
	DDX_Check(pDX, IDC_CHECK4, pos_4);
	DDX_Check(pDX, IDC_CHECK5, pos_5);
	DDX_Check(pDX, IDC_CHECK6, pos_6);
	DDX_Check(pDX, IDC_CHECK7, pos_7);
	DDX_Check(pDX, IDC_CHECK8, pos_8);
	DDX_Check(pDX, IDC_CHECK9, pos_9);
	DDX_Check(pDX, IDC_CHECK10, pos_all);
}

BEGIN_MESSAGE_MAP(CScreenWatermarkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CScreenWatermarkDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CScreenWatermarkDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CScreenWatermarkDlg::OnBnClickedButton3)
	ON_WM_HSCROLL(IDC_SLIDER1)
END_MESSAGE_MAP()


// CScreenWatermarkDlg 消息处理程序

BOOL CScreenWatermarkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_EDIT1)->SetWindowTextW(L"涉密信息，严禁拍摄");
	userColor.AddString(_T("灰色"));
	userColor.AddString(_T("红色"));
	userColor.AddString(_T("绿色"));
	userColor.AddString(_T("蓝色"));
	userColor.SetCurSel(0);
	// font size
	userFontSize.AddString(_T("30"));
	userFontSize.AddString(_T("50"));
	userFontSize.AddString(_T("60"));
	userFontSize.AddString(_T("70"));
	userFontSize.AddString(_T("80"));
	userFontSize.SetCurSel(0);
	// font name
	userFontName.AddString(_T("宋体"));
	userFontName.AddString(_T("黑体"));
	userFontName.AddString(_T("仿宋"));
	userFontName.AddString(_T("楷体"));
	userFontName.SetCurSel(0);
	// user font style
	userFontStyle.AddString(_T("常规"));
	userFontStyle.AddString(_T("粗体"));
	userFontStyle.AddString(_T("斜体"));
	userFontStyle.SetCurSel(0);
	// opacity
	userOpacity.SetRange(0, 255);
	userOpacity.SetTicFreq(10);
	userOpacity.SetPos(100);
	// angle
	userAngle.SetRange(0, 180);
	userAngle.SetTicFreq(10);
	userAngle.SetPos(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CScreenWatermarkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CScreenWatermarkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CScreenWatermarkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

wmData* wmDataPtr = new wmData;
bool isActivated = false;
void ShowWatermark(LPVOID lpParameter);
DWORD watermarkThreadId;

void CScreenWatermarkDlg::OnBnClickedButton2()
{
	if (isActivated == true)
	{
		return;
	}
	else
	{
		watermarkThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ShowWatermark, wmDataPtr, 0, (LPDWORD)&watermarkThreadId);
		isActivated = true;
	}
}

void CScreenWatermarkDlg::OnBnClickedButton3()
{
	if (watermarkThread == NULL)
		return;
	PostThreadMessage(watermarkThreadId, WM_QUIT, NULL, NULL);
	isActivated = false;
}

void CScreenWatermarkDlg::OnBnClickedButton1()
{
	UpdateData(true);
	CString text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(text);
	// 颜色
	CString color;
	int color_index = userColor.GetCurSel();
	userColor.GetLBText(color_index, color);
	// 字体
	CString fontName;
	int fontName_index = userFontName.GetCurSel();
	userFontName.GetLBText(fontName_index, fontName);
	// 字体样式
	int fontStyle_index = userFontStyle.GetCurSel();
	// 字号
	CString fontSizeStr;
	int fontSize_index = userFontSize.GetCurSel();
	userFontSize.GetLBText(fontSize_index, fontSizeStr);
	// 透明度
	int opacity = userOpacity.GetPos();
	showUserOpacity = opacity;
	// 旋转角度
	int rotateAngle = userAngle.GetPos();
	// 水印位置
	vector<int> pos(9, 0);
	if (pos_all == true)
		pos = { 1,1,1,1,1,1,1,1,1 };
	if (pos_1 == true)
		pos[0] = 1;
	if (pos_2 == true)
		pos[1] = 1;
	if (pos_3 == true)
		pos[2] = 1;
	if (pos_4 == true)
		pos[3] = 1;
	if (pos_5 == true)
		pos[4] = 1;
	if (pos_6 == true)
		pos[5] = 1;
	if (pos_7 == true)
		pos[6] = 1;
	if (pos_8 == true)
		pos[7] = 1;
	if (pos_9 == true)
		pos[8] = 1;
	// 水印信息赋值
	wmDataPtr->wmText		 = (wstring)text;
	wmDataPtr->wmColor		 = (wstring)color;
	wmDataPtr->wmFontSize    = _ttoi(fontSizeStr);
	wmDataPtr->wmFontName	 = (wstring)fontName;
	wmDataPtr->wmOpacity	 = 255 - opacity;
	wmDataPtr->wmPosition	 = pos;
	wmDataPtr->wmRotateAngle = rotateAngle;
	wmDataPtr->wmFontStyle	 = fontStyle_index;
	UpdateData(false);
}

void CScreenWatermarkDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	CWnd* SliderCtrlPtr_1 = GetDlgItem(IDC_SLIDER1);
	CWnd* SliderCtrlPtr_2 = GetDlgItem(IDC_SLIDER2);
	CString cStr;
	if (pScrollBar == SliderCtrlPtr_1)
	{
		showUserOpacity = 1 * ((CSliderCtrl*)SliderCtrlPtr_1)->GetPos();
	}
	if (pScrollBar == SliderCtrlPtr_2)
	{
		showUserAngle = 1 * ((CSliderCtrl*)SliderCtrlPtr_2)->GetPos();
	}
	UpdateData(false);
}

void ShowWatermark(LPVOID lpParameter)
{
	wmData* userWmDataPtr = (wmData*)lpParameter;
	CScreenWatermark* wm = new CScreenWatermark(userWmDataPtr);
	wm->CreateWmWindow();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}