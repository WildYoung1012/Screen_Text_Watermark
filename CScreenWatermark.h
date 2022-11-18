#pragma once

#include <string>
#include <vector>
#include <GdiPlus.h>

using namespace std;
using namespace Gdiplus;

static HINSTANCE m_s_hInstance;

struct wmData {
    wstring      wmText;
    wstring      wmColor;
    wstring      wmFontName;
    int          wmOpacity;
    int          wmFontSize;
    int          wmFontStyle;
    int          wmRotateAngle;
    vector<int>  wmPosition;
};

class CScreenWatermark
{
public:
    CScreenWatermark(wmData* userWmData);
    ~CScreenWatermark(void);

    int				 m_top;             // 水印窗口左上角点坐标
    int				 m_left;
    int				 m_width;           // 水印窗口尺寸
    int				 m_height;

    int				 m_wmOpacity;       // 水印透明度
    int			     m_wmFontSize;      // 水印文字字号
    int              m_wmFontStyle;     // 水印文字样式
    int              m_wmRotateAngle;   // 水印倾斜度

    vector<int>      m_wmPosition;      // 水印九宫格位置
    vector<Point>    m_wmVecPt;         // 水印九宫格基点
    vector<Point>    m_wmVecRotatePt;   // 水印倾斜基点

    wstring			 m_wmText;          // 水印文本
    wstring          m_wmColor;         // 水印颜色
    wstring			 m_wmFontName;      // 水印字体

    HWND			 m_hWnd;            // 窗口句柄
    BLENDFUNCTION	 m_blend;           // 混合模式
    StringFormat	 m_wmFormat;        // 字符串格式
    ULONG_PTR		 m_gdiplusToken;    // GDI+指针

    WORD CreateWmWindow();
    ATOM RegisterWmWindowClass();
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT OnWndProc(UINT message, WPARAM wParam, LPARAM lParam);
    void OnPaint(HDC hdc);
};