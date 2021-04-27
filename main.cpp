
#include "main.h"
#include "rc.h"

int main_dialog::idd() const {
	return IDD_DIALOG;
}
bool main_dialog::on_init_dialog() {
	set_text(IDC_EDIT1, tstring);
	return true;
}
bool main_dialog::on_ok() {
	tstring = get_text(IDC_EDIT1);
	return true;
}
bool getFont(HWND hwnd, LOGFONT& logfnt, COLORREF& clr)
{
	CHOOSEFONT fnt;
	ZeroMemory(&fnt, sizeof(fnt));
	fnt.lStructSize = sizeof(fnt);

	fnt.hwndOwner = hwnd;
	fnt.rgbColors = clr;
	fnt.lpLogFont = &logfnt;

	fnt.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT | CF_EFFECTS;

	if (ChooseFont(&fnt))
	{
		clr = fnt.rgbColors;

		return true;
	}

	return false;
}


void main_window::on_paint(HDC hdc) {
	if (tstring2.size() < 1)
		return;

	RECT rct;
	HFONT h_font = (HFONT)SelectObject(hdc, CreateFontIndirect(&log));
	GetClientRect(*this, &rct);

	int visina = rct.bottom / tstring2.size();
	int sirina = rct.right / 9;


	SetTextColor(hdc, colorRef);

	HBRUSH hbrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	for (int i = 0; i < tstring2.size(); i++) {
		for (int j = 0; j < 8; j++) {
			rct = { sirina * j ,visina * i , sirina * (j + 1)  ,visina * (i + 1) };

			bool boja = tstring2[i] & (1 << (7 - j));
			if (!boja)
				FillRect(hdc, &rct, hbrush);

		}
		rct = {
			8 * sirina, i * visina, 9 * sirina, (i + 1) * visina
		};
		DrawText(hdc, &tstring2[i], 1, &rct, DT_VCENTER | DT_CENTER);
	}
	DeleteObject((HFONT)SelectObject(hdc, h_font));
}

void main_window::on_command(int id) {
	switch (id) {
	case ID_FONT:
		if (getFont(*this, log, colorRef)) {
			InvalidateRect(*this, NULL, true);
		}
		break;
	case ID_TEXT:
	{
		main_dialog dialog;
		dialog.tstring = tstring2;

		if (dialog.do_modal(0) != IDOK) {
			return;
		}
		else {
			tstring2 = dialog.tstring;
			InvalidateRect(*this, NULL, true);
		}
		break;
	}
	case ID_EXIT:
		::DestroyWindow(*this);
		break;
	}
}


main_window::main_window() : colorRef(RGB(0, 0, 0)) {
	::ZeroMemory(&log, sizeof(log));
	_tcscpy(log.lfFaceName, _T("Ascii"));
	HDC hdc = GetDC(0);

	log.lfHeight = -16 * GetDeviceCaps(hdc, LOGPIXELSY) / 72;
	log.lfCharSet = EASTEUROPE_CHARSET;

	ReleaseDC(0, hdc);
}


void main_window::on_destroy() {
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int) {
	vsite::nwp::application app;
	main_window wnd;
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"), (int)LoadMenu(instance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.run();
}