
// O_MFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "O_MFC.h"
#include "O_MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CO_MFCDlg dialog




CO_MFCDlg::CO_MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CO_MFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CO_MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON4, m_vedioctl);
}

BEGIN_MESSAGE_MAP(CO_MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CO_MFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CO_MFCDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON3, &CO_MFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CO_MFCDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CO_MFCDlg::OnBnClickedButton5)
END_MESSAGE_MAP()

CString CO_MFCDlg::GetModuleDir()   
{   
	
	HMODULE module = GetModuleHandle(0);   
	TCHAR pFileName[MAX_PATH];   
	GetModuleFileName(module, pFileName, MAX_PATH);   

	CString csFullPath(pFileName);   
	int nPos = csFullPath.ReverseFind( _T('\\') );   
	if( nPos < 0 )   
		return CString("");   
	else   
		return csFullPath.Left( nPos );  	
}  
//CString 转 char *
char * CO_MFCDlg::CStringToChar(CString pstr)
{
	int strlen=pstr.GetLength();
	int nbyte=WideCharToMultiByte(CP_ACP,0,pstr,strlen,NULL,0,NULL,NULL);
	char * VoicePath=new char[nbyte+1];
	memset(VoicePath,0,sizeof(VoicePath));
	WideCharToMultiByte(CP_OEMCP,0,pstr,strlen,VoicePath,nbyte,NULL,NULL);
	VoicePath[nbyte]=0;
	return VoicePath;
}
// CO_MFCDlg message handlers

BOOL CO_MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here  IDD_O_MFC_DIALOG
	this->open_flag=false;
	this->vedio_flag=false;
	this->video=NULL;
	this->videowrite=NULL;             
	memset(this->curdir,0,sizeof(this->curdir));
	memset(this->vediopath,0,sizeof(vediopath));
	CString msg=this->GetModuleDir();
	char *tt_curdir=this->CStringToChar(msg);
	memcpy(this->curdir,tt_curdir,strlen(tt_curdir));
	delete tt_curdir;
	tt_curdir=NULL;
	memset(picpath,0,sizeof(picpath));
	sprintf(picpath,"%s\\OpenCv.jpg",this->curdir);

	this->attachWindow(videowin_pic,"camera",IDC_STATIC);
	cv::Mat mat=cv::imread(picpath);
	showImage(this->videowin_pic,IDC_STATIC,mat);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
bool CO_MFCDlg::attachWindow(string &pic,const char* name,int ID)
{
	pic=string(name);
	cv::namedWindow(pic, 1);
	HWND hWnd = (HWND) cvGetWindowHandle(name);
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(ID)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	return true;
}
bool CO_MFCDlg::showImage(string pic,int id,cv::Mat mat)
{
	CRect rect;
	GetDlgItem(id)->GetClientRect(&rect);	
	cv::resize(mat,mat,cv::Size(rect.Width(),rect.Height()),CV_INTER_CUBIC);	
	imshow(pic,mat);
	return true;
}
void CO_MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CO_MFCDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CO_MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CO_MFCDlg::OnBnClickedButton2()      //关闭摄像头
{
	// TODO: Add your control notification handler code here
	this->open_flag=false;
	cv::Mat mat=cv::imread(picpath);
	showImage(this->videowin_pic,IDC_STATIC,mat);
}

#define WINDOW_WIDTH 20
void DrawEllipse(cv::Mat img,double angle) //绘制摄像小红点
{
	int thickness = 10;
	int lineType = 10;
	cv::ellipse(img,cv::Point(WINDOW_WIDTH+600,WINDOW_WIDTH/2),
		cv::Size(WINDOW_WIDTH/4,WINDOW_WIDTH/4),angle,0,360,cv::Scalar(0,0,255),thickness,lineType);
}
UINT CaptureThread(LPVOID * aPram)         //摄像头抓拍线程
{
	CO_MFCDlg* dlg=(CO_MFCDlg*)aPram;
	
	while(dlg->open_flag)
	{
		(*dlg->video)>>dlg->mat;
		if(dlg->vedio_flag)
		{
			DrawEllipse(dlg->mat,0);      //摄像的时候绘制小红圈
			cvWriteFrame(dlg->videowrite,&IplImage(dlg->mat));
		}
		dlg->showImage(dlg->videowin_pic,IDC_STATIC,dlg->mat);
		cv::waitKey(30);
	}
	return 0;
}
void CO_MFCDlg::OnBnClickedButton1()       //打开摄像头
{
	// TODO: Add your control notification handler code here
	this->open_flag=true;
	video=new cv::VideoCapture(0);
	if(!video)
		return ;
	AfxBeginThread((AFX_THREADPROC)CaptureThread,this);                 
}

void CO_MFCDlg::OnTimer(UINT_PTR nIDEvent)  //定时器处理会卡顿，运行一会儿就会界面卡死
{
	// TODO: Add your message handler code here and/or call default
	CDialogEx::OnTimer(nIDEvent);
}

void CO_MFCDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	this->open_flag=false;
	if(this->video!=NULL)
	{
		this->video->release();
		this->vedio_flag=false;
		cvReleaseVideoWriter(&videowrite);        //释放
		videowrite=NULL;
	}
	CDialogEx::OnClose();
}


void CO_MFCDlg::OnBnClickedButton3()           //点击拍照
{
	// TODO: Add your control notification handler code here
	if(this->open_flag)
	{
		this->t_mat=this->mat;
		PictureEditeWin pewin;
		cv::Mat tt_mat=this->t_mat.clone();
		pewin.setMat(tt_mat);
		pewin.DoModal();
	}
	else
	{
		this->MessageBox(_T("摄像头未开启!"));
	}
}


void CO_MFCDlg::OnBnClickedButton4()           //开始摄像
{
	// TODO: Add your control notification handler code here
	if(this->open_flag&&!this->vedio_flag)
	{
		//弹出输入名称对话框
		PictureNameWin picwin;
		picwin.setWtype(2);
		picwin.DoModal();
		if(!picwin.filename)
		{
			return ;
		}
		char t_filepath[128];
		memset(t_filepath,0,sizeof(t_filepath));
		sprintf(t_filepath,"C:\\Users\\Administrator\\Desktop\\%s",picwin.filename);
		memcpy(vediopath,t_filepath,sizeof(t_filepath));
		m_vedioctl.SetWindowText(_T("结束摄像"));
		////////////////////////////////////////////////////////////////////////////
		this->videowrite=cvCreateVideoWriter(vediopath, CV_FOURCC('X', 'V', 'I', 'D'), 25,  
			cvSize(this->mat.cols,this->mat.rows)); //创建CvVideoWriter对象并分配空间  
		//保存的文件名为camera.avi，编码要在运行程序时选择，大小就是摄像头视频的大小，帧频率是32  
		if(video) //如果能创建CvVideoWriter对象则表明成功  
		{  
			cout<<"VideoWriter has created."<<endl;  
		}  
		this->vedio_flag=true;
	}
	else if(this->open_flag&&this->vedio_flag)
	{
		m_vedioctl.SetWindowText(_T("开启摄像"));
		this->vedio_flag=false;
		cvReleaseVideoWriter(&videowrite);        //释放
		videowrite=NULL;
	}
	else
	{
		this->MessageBox(_T("摄像头未开启!"));
	}
	this->UpdateData(false);
}


void CO_MFCDlg::OnBnClickedButton5()           //其他操作
{
	// TODO: Add your control notification handler code here
}


BOOL CO_MFCDlg::PreTranslateMessage(MSG* pMsg)//处理键盘事件
{
	// TODO: Add your specialized code here and/or call the base class
	char nChar = pMsg->wParam;
    if(nChar == 'S' && ((GetAsyncKeyState( VK_LCONTROL ) & 0x8000)))
    {
		//this->MessageBox(_T("ctrl + s"));
		//弹出输入名称对话框
		return true;
    }
	if (pMsg->message == WM_KEYDOWN)  
    {  
        switch(pMsg->wParam)  
        {  
            case VK_ESCAPE: //Esc按键事件  
                return true;  
            case VK_RETURN: //Enter按键事件

                return true;
			case VK_F1:     //开启帮助信息
				this->MessageBox(_T("照片和视频默认保存到桌面！"));
				return true;
            default:  
                ;  
        }  
    }  
	return CDialogEx::PreTranslateMessage(pMsg);
}
