#include "main.h"
#include "rc.h"
#include <bitset>

class font {
	HFONT h;
public:
	font(const LOGFONT& lf) {
		h = ::CreateFontIndirect(&lf);
	}
	font(const TCHAR* name, int height, bool bold = false, bool italic = false, int angle = 0, bool underline = false) : h(0) {
		h = ::CreateFont(height, 0, angle * 10, 0, bold ? FW_BOLD : FW_NORMAL, italic, underline, 0, 0, 0, 0, 0, 0, name);
	}
	~font() { if (h) ::DeleteObject(h); }
	operator HFONT() { return h; }
};

class sel_obj {
	HDC hdc;
	HGDIOBJ hOld;
public:
	sel_obj(HDC hdc, HGDIOBJ hObj) :
		hdc(hdc), hOld(::SelectObject(hdc, hObj)) { }
	~sel_obj() { ::SelectObject(hdc, hOld); }
};

int main_dialog::idd() const {
	return IDD_DIALOG;
}
bool main_dialog::on_init_dialog() {
	set_text(IDC_EDIT1, str);
	return true;
}
bool main_dialog::on_ok() {
	str = get_text(IDC_EDIT1);
	return true;
}

main_window::main_window()
{
	HDC hdc = GetDC(NULL);
	int h = -16 * GetDeviceCaps(hdc, LOGPIXELSY) / 72;
	lf.lfHeight = h;
	colour = RGB(0, 0, 0);
	_tcscpy_s(lf.lfFaceName, _T("Arial"));
	ReleaseDC(NULL, hdc);
}

void main_window::on_paint(HDC hdc) 
{
	if (s.length() == 0) return;

	RECT r;
	POINT letter_position;
	GetClientRect(*this, &r);

	int width = r.right;
	int height = r.bottom;

	int cell_width = int(r.right / 9);
	int cell_height = int(r.bottom / s.length());

	HFONT prev_font = (HFONT)::SelectObject(hdc, ::CreateFontIndirect(&lf));
	::SetTextColor(hdc, colour);

	for (int i = 0; i < s.size(); ++i) 
	{
		std::bitset<8> binary(s[i]);
		TCHAR ch = s[i];

		for (int j = 7; j >= 0; --j) 
		{
			int bitIndex = 7 - j;
			RECT r = { 
				bitIndex * cell_width,
				i * cell_height, 
				(bitIndex + 1) * cell_width,
				(i + 1) * cell_height 
			};

			if (!binary[j])
			{
				FillRect(hdc, &r, (HBRUSH)::GetStockObject(BLACK_BRUSH));
			}
		}

		letter_position.x = cell_width * 8 + cell_width / 2;
		letter_position.y = cell_height * i + cell_height / 2;

		::TextOut(hdc, letter_position.x, letter_position.y, &ch, 1);
	}

	DeleteObject(::SelectObject(hdc, prev_font));
}

void main_window::on_command(int id) {
	switch(id){
		case ID_FONT:
			if (get_font(*this, lf, colour))
			{
				InvalidateRect(*this, NULL, true);
			}
			break;

		case ID_TEXT:
			get_text();
			InvalidateRect(*this, NULL, true);
			break;

		case ID_EXIT:
			::DestroyWindow(*this);
			break;
	}

	::InvalidateRect(*this, 0, true);
}

void main_window::get_text()
{
	main_dialog dialog;
	dialog.str = s;

	if (dialog.do_modal(0, *this) == IDOK)
	{
		s = dialog.str;
	}
}

bool main_window::get_font(HWND parent, LOGFONT& lf, COLORREF& colour)
{
	CHOOSEFONT cf{ sizeof CHOOSEFONT };
	cf.hwndOwner = parent;
	cf.lpLogFont = &lf;
	cf.rgbColors = colour;
	cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;

	if (!ChooseFont(&cf))
		return false;

	colour = cf.rgbColors;
	return true;
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	vsite::nwp::application app;
	main_window wnd;
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"), (int)LoadMenu(instance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.run();
}
