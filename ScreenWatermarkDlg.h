
// ScreenWatermarkDlg.h: 头文件
//

#pragma once

#include "CScreenWatermark.h"

// CScreenWatermarkDlg 对话框
class CScreenWatermarkDlg : public CDialogEx
{
// 构造
public:
	CScreenWatermarkDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCREENWATERMARK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	HANDLE		watermarkThread;
	CComboBox	userColor;
	CComboBox	userFontSize;
	CComboBox	userFontName;
	CComboBox	userFontStyle;
	CSliderCtrl userOpacity;
	CSliderCtrl userAngle;
	int			showUserOpacity;
	int			showUserAngle;
protected:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
public:
	BOOL pos_1;
	BOOL pos_2;
	BOOL pos_3;
	BOOL pos_4;
	BOOL pos_5;
	BOOL pos_6;
	BOOL pos_7;
	BOOL pos_8;
	BOOL pos_9;
	BOOL pos_all;
};