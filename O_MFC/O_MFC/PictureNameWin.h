#pragma once


// PictureNameWin dialog

class PictureNameWin : public CDialogEx
{
	DECLARE_DYNAMIC(PictureNameWin)

public:
	PictureNameWin(CWnd* pParent = NULL);   // standard constructor
	virtual ~PictureNameWin();
	char * CStringToChar(CString pstr);
	void setWtype(int t_type);
// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CEdit m_filenamectl;
	CComboBox m_suffixctl;
	int wtype;                                    //判断是照相还是摄像1 照相  2摄像
	bool first_setsuffix;
	char *filename;                               //保存拍照的图片名称
	char * vedioname;                             //保存摄像的视频名称
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
};
