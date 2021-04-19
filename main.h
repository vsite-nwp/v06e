#include "nwpwin.h"
#include "nwpdlg.h"

class main_dialog : public vsite::nwp::dialog {
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;

public:
	tstring txt;
};

class main_window : public vsite::nwp::window {
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;

public:
	tstring txt2;
	COLORREF color;
	LOGFONT log_font;

	main_window()
	{
		HDC hdc = GetDC(0);
		ZeroMemory(&log_font, sizeof(log_font));
		log_font.lfHeight = -18 * GetDeviceCaps(hdc, LOGPIXELSY) / 72;
		ReleaseDC(0, hdc);
	}
};
