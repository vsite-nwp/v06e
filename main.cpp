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

void main_window::on_paint(HDC hdc) {
	if (!str.size())
		return;

	RECT r;
	GetClientRect(*this, &r);
	HFONT hf = CreateFontIndirect(&lf);
	SelectObject(hdc, hf);

	int x = r.right / 9;
	int y = r.bottom / str.size();
	SetTextColor(hdc, color);

	HBRUSH hb = (HBRUSH)GetStockObject(BLACK_BRUSH);
	for (int i = 0; i < str.length(); i++) {
		for (int k = 0; k < 8; k++) {
			const RECT r = { x * k, y * i, x * (k + 1), y * (i + 1) };
			if ((str[i] & (1 << (7 - k))) == 0) {
				FillRect(hdc, &r, hb);
			}
		}
		RECT r = { 8 * x, i * y, 9 * x, (i + 1) * y };
		::DrawText(hdc, &str[i], 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	DeleteObject(hf);
}

void main_window::on_command(int id) {
	switch (id) {
	case ID_FONT: {


		CHOOSEFONT cf;
		ZeroMemory(&cf, sizeof cf);
		cf.lStructSize = sizeof cf;
		cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
		cf.lpLogFont = &lf;
		cf.hwndOwner = GetParent(0);
		cf.rgbColors = color;
		if (ChooseFont(&cf)) {
			InvalidateRect(*this, 0, true);
			color = cf.rgbColors;
		}
	}
				break;
	case ID_TEXT: {
				main_dialog dlg;
				dlg.txt = str;
				if (dlg.do_modal(0, *this) == IDOK) {
					this->str = dlg.txt;
					InvalidateRect(*this, NULL, true);
				}
	}
			break;
		case ID_EXIT:
			::DestroyWindow(*this);
			break;
	}
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
