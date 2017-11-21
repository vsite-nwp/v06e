#include "nwpwin.h"
#include "nwpdlg.h"

class MyDialog : public Dialog {
public:
	tstring text;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
public:
	LOGFONT fl;
	tstring wintext;
	MainWindow() : wintext("Luka Sever") {
		ZeroMemory(&fl, sizeof(fl));
		_tcscpy(fl.lfFaceName, _T("Arial"));
		HDC hdc = GetDC(0);
		fl.lfHeight = -12 * GetDeviceCaps(hdc, LOGPIXELSY) / 72;
		ReleaseDC(0, hdc);
	}
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};

