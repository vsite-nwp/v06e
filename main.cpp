#include "main.h"
#include "rc.h"



int main_dialog::idd() const {
	return IDD_DIALOG;
}
bool main_dialog::on_init_dialog() {
	set_text(IDC_EDIT1, txt);
	return true;
}
bool main_dialog::on_ok() {
	txt = get_text(IDC_EDIT1);
	return true;
}

main_window::main_window() {
	ZeroMemory(&lf, sizeof(lf));
	_tcscpy_s(lf.lfFaceName, _T("Arial"));
	HDC hdc = ::GetDC(0);
	
	lf.lfHeight = -16 * ::GetDeviceCaps(hdc, LOGPIXELSY) / 72;
	cr = RGB(0, 0, 0);
	::ReleaseDC(0, hdc);
}

bool get_font(HWND hw, LOGFONT& logf, COLORREF& cr) {
	LOGFONT lf{ logf };
	CHOOSEFONT cf{ sizeof cf, hw, 0, &lf, 0, CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS, cr };
	if (ChooseFont(&cf)) {
		logf = lf;
		cr = cf.rgbColors;
		return true;
	}
	return false;
}


void main_window::on_paint(HDC hdc) {
	RECT r;
	GetClientRect(*this, &r);

	int x = r.right / 9;

	if (txt.empty()) 
	{
		return;
	}

	int y = r.bottom / txt.size();

	HFONT hf = (HFONT)SelectObject(hdc, CreateFontIndirect(&lf));
	SetTextColor(hdc, cr);
	HBRUSH hb = (HBRUSH)GetStockObject(BLACK_BRUSH);

	for (int i = 0; i < txt.size(); i++)
	{
		for (int j = 0; j < 8; j++)
		{
			r = { j * x, i * y, (j + 1) * x, (i + 1) * y };

			if ((txt[i] & (1 << (7 - j))) == 0)
			{
				FillRect(hdc, &r, hb);
			}
		}
		r = { 8 * x, i * y, 9 * x, (i + 1) * y };
		DrawText(hdc, &txt[i], 1, &r, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	}
	DeleteObject((HFONT)SelectObject(hdc, hf)); 
}

void main_window::on_command(int id) {
	switch (id) {
	case ID_FONT:
		get_font(*this, lf, cr);
		break;
	case ID_TEXT:
	{
		main_dialog t;
		t.txt = txt;
		if (t.do_modal(0, *this) == IDOK) {
			txt = t.txt;
		}
		break;
	}
	case ID_EXIT:
		::DestroyWindow(*this);
		break;
	}
	InvalidateRect(*this, NULL, true);
}


void main_window::on_destroy() {
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	vsite::nwp::application app;
	main_window wnd;
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"), (int)LoadMenu(instance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.run();
}