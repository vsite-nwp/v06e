#include "main.h"
#include "rc.h"

int main_dialog::idd() const {
	return IDD_DIALOG;
}
bool main_dialog::on_init_dialog() {
	set_text(IDC_EDIT1, text);
	return true;
}
bool main_dialog::on_ok() {
	text = get_text(IDC_EDIT1);
	return true;
}

void main_window::on_paint(HDC hdc) {
	if (!str.size())
		return;
	RECT rect;
	GetClientRect(*this, &rect);
	int x = rect.right / 9;
	int y = rect.bottom / str.size(); 
	for (int i = 0; i < str.size(); i++) {
		for (int k = 0; k < 8;k++) {
			rect = { x * k, y * i, x * (k + 1), y * (i + 1) };
			if ((str[i] & (1 << k)) == 0) {
				FillRect(hdc, &rect, (HBRUSH) BLACK_BRUSH);
			}
		}
		
	}
	
}

void main_window::on_command(int id) {
	switch(id){
		case ID_FONT:
			break;
		case ID_TEXT: 
		{
			main_dialog t;
			t.text = str;
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
