#pragma once


// PaintTypeWin dialog

class PaintTypeWin : public CDialog
{
	DECLARE_DYNAMIC(PaintTypeWin)

public:
	PaintTypeWin(CWnd* pParent = NULL);   // standard constructor
	virtual ~PaintTypeWin();

// Dialog Data
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//virtual BOOL DestroyWindow();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnPointBtnClickedButton1();
	afx_msg void OnCircleBtnClickedButton2();
	afx_msg void OnEllipseBtnClickedButton8();
	afx_msg void OnLineBtnClickedButton6();
	afx_msg void OnCurveBtnClickedButton10();
	afx_msg void OnRectangleBtnClickedButton3();
	afx_msg void OnCleanBtnClickedButton4();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
