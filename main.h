#include "nwpwin.h"
#include "nwpdlg.h"
#include <vector>

class main_dialog : public vsite::nwp::dialog {
public:
	tstring str;

protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;

};

class main_window : public vsite::nwp::window {
public:
	main_window();
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;

private:
	LOGFONT lf{};
	std::vector<POINT> v;
	tstring s = _T("NWP-L06e");
	COLORREF colour = RGB(0, 0, 0);
	void get_font(HWND parent, LOGFONT& lf);
	void get_text();
	void draw_letter(HDC hdc, RECT rc,POINT position, TCHAR* text);
};
