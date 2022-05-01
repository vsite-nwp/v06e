#include "main.h"
#include "rc.h"

int main_dialog::idd() const {
	return IDD_DIALOG;
}
bool main_dialog::on_init_dialog() {
	set_text(IDC_EDIT1, s);
	return true;
}
bool main_dialog::on_ok() {
	s = get_text(IDC_EDIT1);
	return true;
}

void main_window::on_paint(HDC hdc) {
	if (s.length()==0)
		return;
	RECT rect;
	::GetClientRect(*this, &rect);
	const double x = rect.right / 9.;
	const double y = rect.bottom / static_cast<double>(s.length());
	for (int i = 0; i < s.length(); i++) {
		for (int k = 0; k < 8;k++) {
			const RECT r = { x * k, y * i, x * (k + 1), y * (i + 1) };
			if ((s[i] & (1 << (7-k))) == 0) {
				FillRect(hdc, &r, (HBRUSH)::GetStockObject(BLACK_BRUSH));
			}
		}
		RECT r = { 8 * x, i * y, 9 * x, (i + 1) * y };
		::DrawText(hdc, &s[i], 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
	}
	
}

void main_window::on_command(int id) {
	switch(id){
		case ID_FONT:
			break;
		case ID_TEXT: 
		{
			main_dialog t;
			t.s = s;
			if (t.do_modal(0, *this) == IDOK) {
				s = t.s;
			}
			break;
		}
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