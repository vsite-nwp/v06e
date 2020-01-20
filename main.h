#include "nwpwin.h"
#include "nwpdlg.h"

class MyDialog : public Dialog {
public:
	tstring txt;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
	tstring str;
	LOGFONT lf;
	COLORREF color;
public:
	MainWindow() : str("Dinamo prvak") {
		ZeroMemory(&lf, sizeof(lf));
		_tcscpy(lf.lfFaceName, _T("Times New Roman"));
		HDC hdc = GetDC(0);
		lf.lfHeight = -16 * GetDeviceCaps(hdc, LOGPIXELSY) / 72;
		lf.lfCharSet = EASTEUROPE_CHARSET;
		ReleaseDC(0, hdc);
	}
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
