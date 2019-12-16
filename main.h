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
	tstring windowText;
	LOGFONT log;
	COLORREF color;
	MainWindow() {
		::ZeroMemory(&log, sizeof(log));
		HDC hdc = GetDC(0);
		_tcscpy(log.lfFaceName, _T("Times New Roman"));
		log.lfHeight = -18 * GetDeviceCaps(hdc, LOGPIXELSY) / 72;
		log.lfCharSet = EASTEUROPE_CHARSET;
		color = RGB(0, 0, 0);
	}
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};