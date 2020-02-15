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
	tstring str;
	LOGFONT lf;
	COLORREF color;
	MainWindow()
	{
		HDC hdc = GetDC(0);
		ZeroMemory(&lf, sizeof(lf));
		lf.lfHeight = -18 * GetDeviceCaps(hdc, LOGPIXELSY) / 72;
		lf.lfCharSet = EASTEUROPE_CHARSET;
		_tcscpy(lf.lfFaceName, _T("Arial"));
		color = RGB(0, 0, 0);
		ReleaseDC(0, hdc);
	}

protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
