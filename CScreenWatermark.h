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

    int				 m_top;             // ˮӡ�������Ͻǵ�����
    int				 m_left;
    int				 m_width;           // ˮӡ���ڳߴ�
    int				 m_height;

    int				 m_wmOpacity;       // ˮӡ͸����
    int			     m_wmFontSize;      // ˮӡ�����ֺ�
    int              m_wmFontStyle;     // ˮӡ������ʽ
    int              m_wmRotateAngle;   // ˮӡ��б��

    vector<int>      m_wmPosition;      // ˮӡ�Ź���λ��
    vector<Point>    m_wmVecPt;         // ˮӡ�Ź������
    vector<Point>    m_wmVecRotatePt;   // ˮӡ��б����

    wstring			 m_wmText;          // ˮӡ�ı�
    wstring          m_wmColor;         // ˮӡ��ɫ
    wstring			 m_wmFontName;      // ˮӡ����

    HWND			 m_hWnd;            // ���ھ��
    BLENDFUNCTION	 m_blend;           // ���ģʽ
    StringFormat	 m_wmFormat;        // �ַ�����ʽ
    ULONG_PTR		 m_gdiplusToken;    // GDI+ָ��

    WORD CreateWmWindow();
    ATOM RegisterWmWindowClass();
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT OnWndProc(UINT message, WPARAM wParam, LPARAM lParam);
    void OnPaint(HDC hdc);
};