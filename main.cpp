#include "main.h"
#include "rc.h"

int MyDialog::IDD(){
	return IDD_DIALOG;
}

bool MyDialog::OnInitDialog(){
	SetText(IDC_EDIT1, txt);
	return true;
}

bool MyDialog::OnOK(){
	txt = GetText(IDC_EDIT1);
	return true;
}

bool GetFont(HWND parent, LOGFONT &lf, COLORREF &color) {
	CHOOSEFONT cf;
	ZeroMemory(&cf, sizeof cf);
	cf.lStructSize = sizeof cf;
	cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
	cf.hwndOwner = parent;
	cf.lpLogFont = &lf;
	cf.rgbColors = color;
	if (ChooseFont(&cf)) {
		color = cf.rgbColors;
		return true;
	}
	return false;
}

void MainWindow::OnPaint(HDC hdc) {
}

void MainWindow::OnCommand(int id) {
	switch(id){
	case ID_FONT:
		GetFont(*this, lf, color);
		InvalidateRect(*this, NULL, true);
		break;
	case ID_TEXT:
		break;
	case ID_EXIT:
		DestroyWindow(*this);
		break;
	}
}

void MainWindow::OnDestroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"),
	(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.Run();
}
