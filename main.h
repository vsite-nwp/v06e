#include "nwpwin.h"
#include "nwpdlg.h"

class main_dialog : public vsite::nwp::dialog {
public:
	tstring tstr;
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
};

class main_window : public vsite::nwp::window {
public:
	tstring txt;
	LOGFONT lf;
	COLORREF cr{RGB(0,0,0)};
	COLORREF back{ RGB(255,255,255) };
	main_window();
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;
};