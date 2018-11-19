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
	LOGFONT font_style;
	tstring window_text;
	MainWindow() : window_text("težak zadatak") {
		ZeroMemory(&font_style, sizeof(font_style));
		HDC hdc = GetDC(0);
		font_style.lfHeight = -20 * GetDeviceCaps(hdc, LOGPIXELSY) / 72;
		ReleaseDC(0, hdc);
	}
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
