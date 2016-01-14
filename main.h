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
	HDC hdc;
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
	
public:
	MainWindow()  {
		
		//LOGFONT
		hdc= GetDC(0);
		ZeroMemory(&lf, sizeof(lf)); 
		int PointSize = (12*96) / 72;			//jedan point je 1/72 incha, a 96 pixela je po inchu
												//za font pointa 12, broj pixela je 12*96/72=16
		lf.lfHeight = -MulDiv(PointSize, GetDeviceCaps(hdc, LOGPIXELSY), 96);
		(tstring)lf.lfFaceName = "NWP";
								  
		//CHOOSEFONT				  
		ZeroMemory(&cf, sizeof(cf));
		cf.lStructSize = sizeof(cf);
		cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
		cf.lpLogFont = &lf;
			
	}

	~MainWindow() { ReleaseDC(0, hdc); }
	
};


