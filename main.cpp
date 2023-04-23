#include "main.h"
#include "rc.h"
#include <bitset>

int main_dialog::idd() const {
	return IDD_DIALOG;
}
bool main_dialog::on_init_dialog() {
	return true;
}
bool main_dialog::on_ok() {
	return true;
}

void main_window::on_paint(HDC hdc) 
{
	PAINTSTRUCT ps;
	HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(hdc, GetStockObject(NULL_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));

	RECT r;
	GetClientRect(*this, &r);

	int width = r.right;
	int height = r.bottom;
	int size = min(width / 8, height / 8);

	HFONT hFont = CreateFont(
		size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

	for (int i = 0; i < 6; ++i) 
	{
		std::bitset<8> binary(i);
		TCHAR ch = static_cast<TCHAR>(i);

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

		TCHAR str[2] = { ch, '\0' };
		TextOut(hdc, 9 * size, i * size, str, 1);
	}

	DeleteObject(hBlackBrush);
	DeleteObject(hWhiteBrush);
}

void main_window::on_command(int id) {
	switch(id){
		case ID_FONT:
			break;
		case ID_TEXT:
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
