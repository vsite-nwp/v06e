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
	return true;
}
bool main_dialog::on_ok() {
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
	int size = min(width / 8, height / 8);


	tstring str = _T("012345");

	for (int i = 0; i < str.size(); ++i) 
	{
		std::bitset<8> binary(str[i]);
		TCHAR ch = static_cast<TCHAR>(str[i]);

		for (int j = 7; j >= 0; --j) 
		{
			HBRUSH hBrush = binary[j] ? hWhiteBrush : hBlackBrush;
			int bitIndex = 7 - j;
			RECT r = { 
				bitIndex* size,
				i * size, 
				(bitIndex + 1) * size,
				(i + 1) * size 
			};

			FillRect(hdc, &r, hBrush);
		}

		letter_position.x = size * 8 + size / 2;
		letter_position.y = size * i + size / 2;

		
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
			break;
		case ID_EXIT:
			::DestroyWindow(*this);
			break;
	}

	::InvalidateRect(*this, 0, true);
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
