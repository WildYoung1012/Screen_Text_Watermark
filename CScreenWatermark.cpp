#include "pch.h"
#include "CScreenWatermark.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>

CScreenWatermark::CScreenWatermark(wmData* userWmData)
{
    GdiplusStartupInput gdiplusStartupInput;

    m_top           = 0;
    m_left          = 0;
    m_width         = 1920;
    m_height        = 1080;
    m_wmOpacity     = userWmData->wmOpacity;
    m_wmPosition    = userWmData->wmPosition;
    m_wmRotateAngle = userWmData->wmRotateAngle;
    m_wmVecPt       = { Point(200, 200), Point(800, 200), Point(1400, 200),
                        Point(200, 500), Point(800, 500), Point(1400, 500),
                        Point(200, 800), Point(800, 800), Point(1400, 800)
    };
    m_wmVecRotatePt = { Point(500, 300), Point(1100, 300), Point(1700, 300),
                        Point(500, 600), Point(1100, 600), Point(1700, 600),
                        Point(500, 900), Point(1100, 900), Point(1700, 900)
    };

    m_gdiplusToken  = 0;
    m_wmColor       = userWmData->wmColor;
    m_wmText        = userWmData->wmText;
    m_wmFontName    = userWmData->wmFontName;
    m_wmFontSize    = userWmData->wmFontSize;
    m_wmFontStyle   = userWmData->wmFontStyle;

    GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
}

CScreenWatermark::~CScreenWatermark(void)
{
    GdiplusShutdown(m_gdiplusToken);
}

ATOM CScreenWatermark::RegisterWmWindowClass()
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_s_hInstance;
    wcex.hIcon = NULL;
    wcex.hCursor = NULL;
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"ScW";
    wcex.hIconSm = NULL;

    return RegisterClassEx(&wcex);
}

WORD CScreenWatermark::CreateWmWindow()
{
    RegisterWmWindowClass();

    m_blend.BlendOp = 0;
    m_blend.BlendFlags = 0;
    m_blend.AlphaFormat = 1;
    m_blend.SourceConstantAlpha = 60;

    m_wmFormat.SetAlignment(StringAlignmentNear);
    m_hWnd = ::CreateWindowEx((WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT | WS_EX_TOPMOST) & ~WS_EX_APPWINDOW, L"ScW", L"", WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP,
        m_left, m_top, m_width, m_height, NULL, NULL, m_s_hInstance, NULL);
    ::SetProp(m_hWnd, L"CLASSPOINTER", this);

    ::PostMessage(m_hWnd, WM_PAINT, 0, 0);

    return 0;
}

LRESULT CALLBACK CScreenWatermark::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HANDLE h = ::GetProp(hWnd, L"CLASSPOINTER");

    CScreenWatermark* p = (CScreenWatermark*)h;
    if (NULL == h)
    {
        return ::DefWindowProc(hWnd, message, wParam, lParam);
    }

    return p->OnWndProc(message, wParam, lParam);
}

LRESULT CScreenWatermark::OnWndProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC          hdc;
    PAINTSTRUCT  ps;

    BringWindowToTop(m_hWnd);

    switch (message)
    {
    case WM_PAINT:
        hdc = ::BeginPaint(m_hWnd, &ps);
        OnPaint(hdc);
        EndPaint(m_hWnd, &ps);
        BringWindowToTop(m_hWnd);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(m_hWnd, message, wParam, lParam);
    }
    return DefWindowProc(m_hWnd, message, wParam, lParam);
}

void CScreenWatermark::OnPaint(HDC hdc)
{
    HDC          hdcMemory = CreateCompatibleDC(hdc);

    HBITMAP      hBitMap = CreateCompatibleBitmap(hdc, m_width, m_height);
    SelectObject(hdcMemory, hBitMap);

    Graphics     graphics(hdcMemory);

    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.SetInterpolationMode(InterpolationModeHighQualityBicubic);

    vector<GraphicsPath*> vecPathPtr;
    FontFamily fontFamily(m_wmFontName.c_str());

    for (int i = 0; i < m_wmPosition.size(); i++)
    {
        if (m_wmPosition[i] == 1)
        {
            RectF rect(m_wmVecPt[i].X, m_wmVecPt[i].Y, 600, 200);
            GraphicsPath* tempPath = new GraphicsPath;
            tempPath->AddString(m_wmText.c_str(), m_wmText.length(), &fontFamily, m_wmFontStyle, m_wmFontSize, rect, &m_wmFormat);

            Matrix* tiltMatrixPtr = new Matrix();

            tiltMatrixPtr->Translate(m_wmVecRotatePt[i].X, m_wmVecRotatePt[i].Y);
            tiltMatrixPtr->Rotate(m_wmRotateAngle);
            tiltMatrixPtr->Translate(-m_wmVecRotatePt[i].X, -m_wmVecRotatePt[i].Y);

            tempPath->Transform(tiltMatrixPtr);

            vecPathPtr.push_back(tempPath);
        }
    }

    Color wmColor;
    if (0 == _wcsicmp(m_wmColor.c_str(), L"红色"))
    {
        wmColor = Color(m_wmOpacity, 255, 0, 0);
    }
    else if (0 == _wcsicmp(m_wmColor.c_str(), L"绿色"))
    {
        wmColor = Color(m_wmOpacity, 0, 255, 0);
    }
    else if (0 == _wcsicmp(m_wmColor.c_str(), L"蓝色"))
    {
        wmColor = Color(m_wmOpacity, 0, 0, 255);
    }
    else if (0 == _wcsicmp(m_wmColor.c_str(), L"灰色"))
    {
        wmColor = Color(m_wmOpacity, 212, 212, 212);
    }

    Pen pen(wmColor, 2);
    SolidBrush sldBrush(wmColor);

    for (int i = 0; i < vecPathPtr.size(); i++)
    {
        graphics.DrawPath(&pen, vecPathPtr[i]);
        graphics.FillPath(&sldBrush, vecPathPtr[i]);
    }

    LONG lWindowLong = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
    if ((lWindowLong & WS_EX_LAYERED) != WS_EX_LAYERED)
    {
        lWindowLong = lWindowLong | WS_EX_LAYERED;
        ::SetWindowLong(m_hWnd, GWL_EXSTYLE, lWindowLong);
    }

    POINT ptSrc = { 0, 0 };
    POINT ptWinPos = { m_left, m_top };
    HDC   hdcScreen = ::GetDC(m_hWnd);
    SIZE  sizeWindow = { m_width, m_height };
    BOOL  bRet = UpdateLayeredWindow(m_hWnd, hdcScreen, &ptWinPos,
        &sizeWindow, hdcMemory, &ptSrc,
        0, &m_blend, ULW_ALPHA);

    ::SetWindowPos(m_hWnd, HWND_TOPMOST, m_left, m_top, m_width, m_height, SWP_SHOWWINDOW);
    ::ReleaseDC(m_hWnd, hdcScreen);
    ::ReleaseDC(m_hWnd, hdc);

    hdcScreen = NULL;
    hdc = NULL;

    DeleteObject(hBitMap);
    DeleteDC(hdcMemory);
    hdcMemory = NULL;
}