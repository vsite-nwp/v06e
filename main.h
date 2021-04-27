#include "nwpwin.h"
#include "nwpdlg.h"

class main_dialog : public vsite::nwp::dialog {
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;

public:

	tstring tstring;
};

class main_window : public vsite::nwp::window {
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;

public:

	tstring tstring2;
	LOGFONT log;
	COLORREF colorRef;

	main_window();
};