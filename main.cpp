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
	_tcscpy_s(lf.lfFaceName, _T("Arial"));
	lf.lfHeight = h;
	ReleaseDC(NULL, hdc);
}

void main_window::on_paint(HDC hdc) 
{
	PAINTSTRUCT ps;
	HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(hdc, GetStockObject(NULL_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));

	RECT r;
	POINT letter_position;
	GetClientRect(*this, &r);

	int width = r.right;
	int height = r.bottom;

	int cell_width = int(r.right / 9);
	int cell_height = int(r.bottom / s.length());

	for (int i = 0; i < s.size(); ++i) 
	{
		std::bitset<8> binary(s[i]);
		TCHAR ch = static_cast<TCHAR>(s[i]);

		for (int j = 7; j >= 0; --j) 
		{
			HBRUSH hBrush = binary[j] ? hWhiteBrush : hBlackBrush;
			int bitIndex = 7 - j;
			RECT r = { 
				bitIndex * cell_width,
				i * cell_height, 
				(bitIndex + 1) * cell_width,
				(i + 1) * cell_height 
			};

			FillRect(hdc, &r, hBrush);
		}

		letter_position.x = cell_width * 8 + cell_width / 2;
		letter_position.y = cell_height * i + cell_height / 2;

		
		draw_letter(hdc, r, letter_position, &ch);
	}

	DeleteObject(hBlackBrush);
	DeleteObject(hWhiteBrush);
}

void main_window::on_command(int id) {
	switch(id){
		case ID_FONT:
			get_font(*this, lf);
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

void main_window::get_font(HWND parent, LOGFONT& lf)
{
	CHOOSEFONT cf{ sizeof CHOOSEFONT };
	cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
	cf.hwndOwner = parent;
	cf.lpLogFont = &lf;
	::ChooseFont(&cf);
}

void main_window::draw_letter(HDC hdc, RECT rc, POINT position, TCHAR* text)
{
	::SetTextColor(hdc, RGB(0, 0, 0));
	::SetBkColor(hdc, RGB(255, 255, 255));
	font f(lf);
	sel_obj sf(hdc, f);

	::TextOut(hdc, position.x, position.y, text, 1);
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
