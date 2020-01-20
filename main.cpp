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
	RECT rc;
	GetClientRect(*this, &rc);

	if (!str.size())
		return;

	long dx = rc.right / 9;
	long dy = rc.bottom / str.size();

	SetTextColor(hdc, color);
	HFONT hf = (HFONT)SelectObject(hdc, CreateFontIndirect(&lf));

	for (int i = 0; i < str.size(); i++) {
		for (int j = 0; j < 8; j++) {
			rc = { j*dx, i*dy, (j + 1)*dx, (i + 1)*dy };
			bool white = str[i] & (1 << (7 - j));
			if (!white)
				FillRect(hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
		rc = { 8 * dx, i*dy, 9 * dx, (i + 1)*dy };
		DrawText(hdc, &str[i], 1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	DeleteObject(SelectObject(hdc, hf));
}



void MainWindow::OnCommand(int id) {
	MyDialog dlg;
	LOGFONT font = lf;
	COLORREF colour = color;
	switch(id){
	case ID_FONT: 
		if (GetFont(*this, lf, color))
			InvalidateRect(*this, NULL, true);
		else { lf = font; color = colour; }
		break;
	case ID_TEXT:
		dlg.txt = str;
		if (dlg.DoModal(NULL, *this) == IDOK) {
			this->str = dlg.txt;
		}
		InvalidateRect(*this, NULL, true);
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
