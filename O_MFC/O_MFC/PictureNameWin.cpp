// PictureNameWin.cpp : implementation file
//

#include "stdafx.h"
#include "O_MFC.h"
#include "PictureNameWin.h"
#include "afxdialogex.h"

// PictureNameWin dialog

IMPLEMENT_DYNAMIC(PictureNameWin, CDialogEx)

PictureNameWin::PictureNameWin(CWnd* pParent /*=NULL*/)
	: CDialogEx(PictureNameWin::IDD, pParent)
{
	first_setsuffix=true;
	filename=NULL;
	vedioname=NULL;
	this->wtype=-1;
}

PictureNameWin::~PictureNameWin()
{
}

void PictureNameWin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_filenamectl);
	DDX_Control(pDX, IDC_COMBO1, m_suffixctl);
}


BEGIN_MESSAGE_MAP(PictureNameWin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &PictureNameWin::OnBnClickedButton1)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

//CString 转 char *
char * PictureNameWin::CStringToChar(CString pstr)
{
	int strlen=pstr.GetLength();
	int nbyte=WideCharToMultiByte(CP_ACP,0,pstr,strlen,NULL,0,NULL,NULL);
	char * VoicePath=new char[nbyte+1];
	memset(VoicePath,0,sizeof(VoicePath));
	WideCharToMultiByte(CP_OEMCP,0,pstr,strlen,VoicePath,nbyte,NULL,NULL);
	VoicePath[nbyte]=0;
	return VoicePath;
}


// PictureNameWin message handlers
void PictureNameWin::setWtype(int t_type)
{
	this->wtype=t_type;
}

void PictureNameWin::OnBnClickedButton1()                   //确定按钮处理事件
{
	// TODO: Add your control notification handler code here
	CString tmp;
	this->m_filenamectl.GetWindowText(tmp);
	if(tmp==_T(""))
	{
		this->MessageBox(_T("名称不能为空!"));
		return ;
	}
	CString tmpsuffix;
	this->m_suffixctl.GetWindowText(tmpsuffix);
	tmp+=tmpsuffix;
	//tmp copy to filename
	filename=this->CStringToChar(tmp);
	this->PostMessage(WM_CLOSE);
}

void PictureNameWin::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL PictureNameWin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)  
    {  
        switch(pMsg->wParam)  
        {  
            case VK_ESCAPE:                        //Esc按键处理事件  
                return true;  
            case VK_RETURN:                        //Enter按键处理事件
				this->OnBnClickedButton1();
                return true;
			case VK_F1:                            //开启帮助信息
				this->MessageBox(_T("照片和视频默认保存到桌面！"));
				return true;
            default:  
				;  
        }  
    }  
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL PictureNameWin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	if(first_setsuffix&&this->wtype==1)
	{
		this->m_suffixctl.AddString(_T(".jpg"));
		this->m_suffixctl.AddString(_T(".png"));
		this->m_suffixctl.SetCurSel(0);
		this->UpdateData(false);
		first_setsuffix=false;
	}
	else if(first_setsuffix&&this->wtype==2)
	{
		this->m_suffixctl.AddString(_T(".avi"));
		this->m_suffixctl.AddString(_T(".mp4"));
		this->m_suffixctl.AddString(_T(".flv"));
		this->m_suffixctl.SetCurSel(0);
		this->UpdateData(false);
		first_setsuffix=false;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
