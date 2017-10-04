
// O_MFCDlg.h : header file
//
#include "PictureNameWin.h"
#include "PictureEditeWin.h"
#include <cstring>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#pragma once
using namespace std;

// CO_MFCDlg dialog
class CO_MFCDlg : public CDialogEx
{
// Construction
public:
	CO_MFCDlg(CWnd* pParent = NULL);	// standard constructor
	bool attachWindow(string &pic,const char* name,int ID);     //将opencv的显示窗口与MFC的控件链接起来，
	bool showImage(string pic,int id,cv::Mat mat);              //效果是opencv的窗口恰好覆盖在控件上    
	CString GetModuleDir();
	char* CStringToChar(CString pstr);
// Dialog Data
	enum { IDD = IDD_O_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	       // DDX/DDV support
	
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButton2();                         //关闭摄像头
	afx_msg void OnBnClickedButton1();                         //打开摄像头
	afx_msg void OnTimer(UINT_PTR nIDEvent);         
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	
	cv::VideoCapture * video;
	string videowin_pic;
	bool vedio_flag;                                           //摄像开始标记
	bool open_flag;
	char curdir[128];                                          //保存应用程序当前所在的路径
	char picpath[128];                                         //保存默认图片路径
	char vediopath[128];                                       //保存摄像保存的路径
	cv::Mat mat;                                               //保存抓拍的每一帧图片
	cv::Mat t_mat;                                             //保存拍照的图片
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButton m_vedioctl;
	CvVideoWriter* videowrite;
};
