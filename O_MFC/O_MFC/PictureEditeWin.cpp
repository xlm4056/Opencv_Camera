// PictureEditeWin.cpp : implementation file
#include "stdafx.h"
#include "O_MFC.h"
#include "PictureEditeWin.h"
#include "afxdialogex.h"

// PictureEditeWin dialog
bool scrawl_flag=false;                                  //涂鸦界面开启标记避免多次打开
int  scrawl_type=-1;                                     //涂鸦类型 -1 不绘画，0点.....
IMPLEMENT_DYNAMIC(PictureEditeWin, CDialog)

PictureEditeWin::PictureEditeWin(CWnd* pParent /*=NULL*/)
	: CDialog(PictureEditeWin::IDD, pParent)
{
	memset(this->curdir,0,sizeof(this->curdir));
	CString t_curdirstr=this->GetModuleDir();
	char * t_curdir=this->CStringToChar(t_curdirstr);
	memcpy(this->curdir,t_curdir,strlen(t_curdir));
	delete t_curdir;
	t_curdir=NULL;
	scale=1;
}
// PictureEditeWin message handlers
CString PictureEditeWin::GetModuleDir()   
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
char * PictureEditeWin::CStringToChar(CString pstr)
{
	int strlen=pstr.GetLength();
	int nbyte=WideCharToMultiByte(CP_ACP,0,pstr,strlen,NULL,0,NULL,NULL);
	char * VoicePath=new char[nbyte+1];
	memset(VoicePath,0,sizeof(VoicePath));
	WideCharToMultiByte(CP_OEMCP,0,pstr,strlen,VoicePath,nbyte,NULL,NULL);
	VoicePath[nbyte]=0;
	return VoicePath;
}
BOOL PictureEditeWin::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  Add extra initialization here 
	attachWindow(pic,"Pictrue",IDC_STATIC);
	showImage(pic,IDC_STATIC,this->mat);
	beta=5;
	alpha=1.03;
	leftbtn_flag=false;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
PictureEditeWin::~PictureEditeWin()
{
}
bool PictureEditeWin::attachWindow(string &pic,const char* name,int ID)
{
	pic=string(name);
	cv::namedWindow(pic, 1);
	HWND hWnd = (HWND) cvGetWindowHandle(name);
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(ID)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	return true;
}
bool PictureEditeWin::showImage(string pic,int id,cv::Mat mat)
{
	CRect rect;
	GetDlgItem(id)->GetClientRect(&rect);	
	cv::resize(mat,mat,cv::Size(rect.Width(),rect.Height()),CV_INTER_CUBIC);	
	imshow(pic,mat);
	return true;
}
void PictureEditeWin::setMat(cv::Mat t_mat)
{
	this->mat=t_mat;
	tempImage=this->mat.clone();
}

void PictureEditeWin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON8, m_savebtn);
	DDX_Control(pDX, IDC_BUTTON1, m_graybtn);
	DDX_Control(pDX, IDC_BUTTON5, m_restorebtn);
}

BEGIN_MESSAGE_MAP(PictureEditeWin, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &PictureEditeWin::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &PictureEditeWin::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &PictureEditeWin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON6, &PictureEditeWin::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &PictureEditeWin::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON3, &PictureEditeWin::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &PictureEditeWin::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON9, &PictureEditeWin::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON7, &PictureEditeWin::OnBnClickedButton7)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void PictureEditeWin::OnBnClickedButton1()                 //灰度按钮处理事件
{
	// TODO: Add your control notification handler code here
	cvtColor(tempImage,tempImage,CV_RGB2GRAY);
	showImage(pic,IDC_STATIC,tempImage);

	this->UpdateData(false);
	this->m_graybtn.EnableWindow(false);
}

void PictureEditeWin::OnBnClickedButton5()                  //恢复按钮处理事件
{
	// TODO: Add your control notification handler code here
	showImage(pic,IDC_STATIC,this->mat);
	tempImage=this->mat.clone();
	this->UpdateData(false);
	this->m_graybtn.EnableWindow(true);
}

void PictureEditeWin::OnBnClickedButton2()                   //变亮按钮处理事件
{
	// TODO: Add your control notification handler code here
	for(int y=0;y<tempImage.rows;++y)
	{
		for(int x=0;x<tempImage.cols;++x)
		{
			for(int c=0;c<3;++c)
			{
				tempImage.at<cv::Vec3b>(y,x)[c] =  
                cv::saturate_cast<uchar>( tempImage.at<cv::Vec3b>(y,x)[c]  + beta); 
			}
		}
	}
	showImage(pic,IDC_STATIC,tempImage);
	this->UpdateData(false);
}


void PictureEditeWin::OnBnClickedButton6()                   //变暗按钮处理事件 
{
	// TODO: Add your control notification handler code here
	for(int y=0;y<tempImage.rows;++y)
	{
		for(int x=0;x<tempImage.cols;++x)
		{
			for(int c=0;c<3;++c)
			{
				tempImage.at<cv::Vec3b>(y,x)[c] =  
                cv::saturate_cast<uchar>( tempImage.at<cv::Vec3b>(y,x)[c]  - beta); 
			}
		}
	}
	showImage(pic,IDC_STATIC,tempImage);
	this->UpdateData(false);
}

void PictureEditeWin::OnBnClickedButton8()                   //保存按钮处理事件
{
	// TODO: Add your control notification handler code here
	PictureNameWin picwin;
	picwin.setWtype(1);
	picwin.DoModal();
	if(!picwin.filename)
	{
		return ;
	}
	char t_filepath[128]={0};
	memset(t_filepath,0,sizeof(t_filepath));
	sprintf(t_filepath,"C:\\Users\\Administrator\\Desktop\\%s",picwin.filename);

	bool res=cv::imwrite(t_filepath,tempImage);
	if(res)
	{
		this->MessageBox(_T("图片成功保存包桌面!"));
	}
	if(picwin.filename)
	{
		delete picwin.filename;
		picwin.filename=NULL;
	}
}


void PictureEditeWin::OnBnClickedButton3()                                     //对比度+
{
	// TODO: Add your control notification handler code here
	for(int y=0;y<tempImage.rows;++y)
	{
		for(int x=0;x<tempImage.cols;++x)
		{
			for(int c=0;c<3;++c)
			{
				tempImage.at<cv::Vec3b>(y,x)[c] =  
                cv::saturate_cast<uchar>( alpha*tempImage.at<cv::Vec3b>(y,x)[c]); 
			}
		}
	}
	showImage(pic,IDC_STATIC,tempImage);
	this->UpdateData(false);
}


void PictureEditeWin::OnBnClickedButton4()                                     //对比度-
{
	// TODO: Add your control notification handler code here
	for(int y=0;y<tempImage.rows;++y)
	{
		for(int x=0;x<tempImage.cols;++x)
		{
			for(int c=0;c<3;++c)
			{
				tempImage.at<cv::Vec3b>(y,x)[c] =  
                cv::saturate_cast<uchar>( tempImage.at<cv::Vec3b>(y,x)[c]/alpha); 
			}
		}
	}
	showImage(pic,IDC_STATIC,tempImage);
	this->UpdateData(false);
}


void PictureEditeWin::OnBnClickedButton9()                                     //文字编辑
{
	// TODO: Add your control notification handler code here



}

void PictureEditeWin::OnBnClickedButton7()                                     //绘画涂鸦
{
	// TODO: Add your control notification handler code here
	if(!scrawl_flag)
	{
		PaintTypeWin *ptwin=new PaintTypeWin;
		ptwin->Create(IDD_DIALOG3,NULL);
		ptwin->ShowWindow(SW_SHOW);
		scrawl_flag=true;
	}
}


BOOL PictureEditeWin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)  
	{  
		switch(pMsg->wParam)  
		{  
		case VK_ESCAPE:                                                       //Esc按键处理事件  
			scrawl_type=-1;
			return true;  
		case VK_RETURN:                                                       //Enter按键处理事件
			return true;
		case VK_F1:                                                           //开启帮助信息
			this->MessageBox(_T("照片和视频默认保存到桌面！"));
			return true;
		default:  
			;  
		}  
	}  
	return CDialog::PreTranslateMessage(pMsg);
}

void PictureEditeWin::OnLButtonDown(UINT nFlags, CPoint point)                //鼠标左键按下
{
	// TODO: Add your message handler code here and/or call default
	leftbtn_flag=true;
	this->start_point.x=point.x;
	this->start_point.y=point.y;
	if(scrawl_type==0)
	{
		cv::circle(this->tempImage,this->start_point,1,cv::Scalar(0,0,255),5,8);
		showImage(pic,IDC_STATIC,tempImage);
		this->UpdateData(false);
		
	}
	CDialog::OnLButtonDown(nFlags, point);
}



void PictureEditeWin::OnLButtonUp(UINT nFlags, CPoint point)                  //鼠标左键释放
{
	// TODO: Add your message handler code here and/or call default
	leftbtn_flag=false;
	this->end_point.x=point.x;
	this->end_point.y=point.y;
	switch(scrawl_type)
	{
	case 0:
		{

			break;
		}
	case 1:
		{

			break;
		}
	
	}



	CDialog::OnLButtonUp(nFlags, point);
}


void PictureEditeWin::OnMouseMove(UINT nFlags, CPoint point)                  //鼠标移动处理事件
{
	// TODO: Add your message handler code here and/or call default
	if(leftbtn_flag)
	{
		this->tmp_point.x=point.x;
		this->tmp_point.y=point.y;



	}
	CDialog::OnMouseMove(nFlags, point);
}
