#include "nwpwin.h"
#include "nwpdlg.h"

class MyDialog : public Dialog {
public:
	tstring t;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
protected:
	
	CHOOSEFONT cf;
	LOGFONT lf;
	tstring t;
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
	
public:
	MainWindow()  {
		
		//LOGFONT
		HDC hdc=GetDC(0);
		ZeroMemory(&lf, sizeof(lf)); 
		_tcscpy(lf.lfFaceName,_T("Arial"));
		lf.lfHeight = -MulDiv(12, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		ReleaseDC(0, hdc);
								  
		//CHOOSEFONT				  
		ZeroMemory(&cf, sizeof(cf));
		cf.lStructSize = sizeof(cf);
		cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
		cf.lpLogFont = &lf;
			
	}

	~MainWindow() {}
	
};


