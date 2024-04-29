#include "main.h"
#include "rc.h"

int main_dialog::idd() const {
	return IDD_DIALOG;
}
bool main_dialog::on_init_dialog() {
	set_text(IDC_EDIT1, tstr);
	return true;
}
bool main_dialog::on_ok() {
	tstr = get_text(IDC_EDIT1);
	return true;
}

void get_font(HWND parent, LOGFONT& lf, COLORREF& cr)
{
	CHOOSEFONT cf{ sizeof CHOOSEFONT };
	cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
	cf.hwndOwner = parent;
	cf.lpLogFont = &lf;
	::ChooseFont(&cf);
	cr = cf.rgbColors;
}


COLORREF get_color(HWND parent, COLORREF cur) {
	COLORREF custom_colors[16]{ 0 };
	CHOOSECOLOR cc{ sizeof CHOOSECOLOR };
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	cc.hwndOwner = parent;
	cc.lpCustColors = custom_colors;
	cc.rgbResult = cur;
	if (::ChooseColor(&cc))
		cur = cc.rgbResult;
	return cur;
}


main_window::main_window() {
	ZeroMemory(&lf, sizeof(lf));
	_tcscpy_s(lf.lfFaceName, _T("Arial"));
	HDC hdc = ::GetDC(0);

	lf.lfHeight = -18 * ::GetDeviceCaps(hdc, LOGPIXELSY) / 72;
	cr = RGB(0, 0, 0);
	::ReleaseDC(0, hdc);
}

void main_window::on_paint(HDC hdc) {
	if (txt.empty())
	{
		return;
	}
	RECT rect;
	GetClientRect(*this, &rect);
	HBRUSH background = CreateSolidBrush(back);
	FillRect(hdc, &rect, background);
	const double x = rect.right / 9.;
	const double y = rect.bottom / static_cast<double>(txt.size());

	HFONT hf = (HFONT)SelectObject(hdc, CreateFontIndirect(&lf));
	SetTextColor(hdc, cr);
	HBRUSH hb = CreateSolidBrush(cr);
	
	for (size_t i = 0; i < txt.size(); ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			const RECT r = {j * x, i * y, (j + 1) * x, (i + 1) * y };

			if ((txt[i] & (1 << (7 - j))) == 0)
			{
				FillRect(hdc, &r, hb);
			}
		}
		RECT r = { 8 * x, i * y, 9 * x, (i + 1) * y };
		::SetBkMode(hdc, TRANSPARENT);
		DrawText(hdc, &txt[i], 1, &r, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	}
	DeleteObject((HFONT)SelectObject(hdc, hf));
}

void main_window::on_command(int id) {
	switch (id) {
	case ID_FONT:
	{
		get_font(*this, lf,cr);
		break;
	}
	case ID_TEXT:
	{
		main_dialog t;
		t.tstr = txt;
		if (t.do_modal(0, *this) == IDOK) {
			txt = t.tstr;
		}
		break;
	}
	case ID_COLOR: 
	{
		back = get_color(*this, back);
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
