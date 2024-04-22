#include "nwpwin.h"
#include "nwpdlg.h"

class main_dialog : public vsite::nwp::dialog {
public:
	tstring txt;

protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
};

class main_window : public vsite::nwp::window {
	tstring str;
	LOGFONT lf;
	COLORREF color;
public:
	main_window() {
		_tcscpy_s(lf.lfFaceName, _T("Arial"));
		HDC hdc = ::GetDC(0);
		lf.lfHeight = -16 * ::GetDeviceCaps(hdc, LOGPIXELSY) / 72;
		color = RGB(0, 0, 0);
		lf.lfCharSet = EASTEUROPE_CHARSET;
		lf.lfStrikeOut = false;
		lf.lfUnderline = false;
		lf.lfItalic = false;
		lf.lfOrientation = 0;
		lf.lfEscapement = 0;
		::ReleaseDC(0, hdc);
	}
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;
};
