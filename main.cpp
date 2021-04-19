#include "main.h"
#include "rc.h"

int main_dialog::idd() const
{
	return IDD_DIALOG;
}
bool main_dialog::on_init_dialog()
{
	set_text(IDC_EDIT1, txt);
	return true;
}
bool main_dialog::on_ok()
{
	txt = get_text(IDC_EDIT1);
	return true;
}

bool get_font(HWND parent, LOGFONT& log_font, COLORREF& color)
{
	CHOOSEFONT choose_font;

	ZeroMemory(&choose_font, sizeof(choose_font));

	choose_font.lStructSize = sizeof(choose_font);
	choose_font.hwndOwner = parent;
	choose_font.lpLogFont = &log_font;
	choose_font.rgbColors = color;
	choose_font.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS; //show selected font, strikeout, underline, and text color 

	if (ChooseFont(&choose_font))
	{
		color = choose_font.rgbColors;

		return true;
	}

	return false;
}

void main_window::on_paint(HDC hdc)
{
	RECT rect;
	GetClientRect(*this, &rect);

	int width = rect.right / 9;

	if (txt2.empty()) //unhandled exception if not checked 
	{
		return;
	}

	int height = rect.bottom / txt2.size();

	HFONT h_font = (HFONT)SelectObject(hdc, CreateFontIndirect(&log_font));
	SetTextColor(hdc, color);

	for (int i = 0; i < txt2.size(); i++)
	{
		for (int j = 0; j < 8; j++)
		{
			rect = { j * width, i * height, (j + 1) * width, (i + 1) * height };

			if ((txt2[i] & (1 << (7 - j))) == 0)
			{
				FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
			}
		}
		rect = { 8 * width, i * height, 9 * width, (i + 1) * height };
		DrawText(hdc, &txt2[i], 1, &rect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	}
	DeleteObject((HFONT)SelectObject(hdc, h_font)); //delete created font
}

void main_window::on_command(int id)
{
	switch (id)
	{
	case ID_FONT:
		if (get_font(*this, log_font, color)) 
		{
			InvalidateRect(*this, NULL, true); //redraw window when font is changed
		}
		break;
	case ID_TEXT:
	{
		main_dialog dlg;
		dlg.txt = txt2;

		if (dlg.do_modal(0, *this) == IDOK)
		{
			txt2 = dlg.txt;
		}

		InvalidateRect(*this, NULL, true);
		break;
	}
	case ID_EXIT:
		::DestroyWindow(*this);
		break;
	}
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