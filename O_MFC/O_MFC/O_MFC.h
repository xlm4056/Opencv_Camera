
// O_MFC.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CO_MFCApp:
// See O_MFC.cpp for the implementation of this class
//

class CO_MFCApp : public CWinApp
{
public:
	CO_MFCApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CO_MFCApp theApp;