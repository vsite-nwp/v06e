#include "main.h"
#include "rc.h"

int main_dialog::idd() const {
	return IDD_DIALOG;
}
bool main_dialog::on_init_dialog() {
	return true;
}
bool main_dialog::on_ok() {
	return true;
}

void main_window::on_paint(HDC hdc) {
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

int WINAPI WinMain(HINSTANCE hi, HINSTANCE, LPSTR, int)
{
	vsite::nwp::application app;
	main_window wnd;
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"), (UINT_PTR)LoadMenu(hi, MAKEINTRESOURCE(IDM_MAIN)));
	return app.run();
}
