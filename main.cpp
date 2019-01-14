#include "main.h"
#include "rc.h"

int MyDialog::IDD(){
	return IDD_DIALOG;
}

bool MyDialog::OnInitDialog(){
	SetText(IDC_EDIT1, text);
	return true;
}

bool MyDialog::OnOK(){
	text = GetText(IDC_EDIT1);
	return true;
}



void MainWindow::OnPaint(HDC hdc) {
	if (!str.size())
		return;
	RECT rc;
	GetClientRect(*this, &rc);
	int rt = rc.right / 9;
	int btm = rc.bottom / str.size();
	SetTextColor(hdc, color);
	HFONT hf = (HFONT)SelectObject(hdc, CreateFontIndirect(&lf));
	HBRUSH hb = (HBRUSH)GetStockObject(BLACK_BRUSH);
	for (int i = 0; i < str.size(); i++) {
		for (int j = 0; j < 8; j++) {
			rc = { j*rt,i*btm,(j + 1)*rt,(i + 1)*btm };
			bool white = str[i] & (1 << (7 - j));
			if (!white)
				FillRect(hdc, &rc, hb);
		}
		rc = { 8 * rt, i*btm, 9 * rt, (i + 1)*btm };
		DrawText(hdc, &str[i], 1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	DeleteObject(SelectObject(hdc, hf));
}
bool GetFont(HWND parent, LOGFONT &lf, COLORREF &color) {
	CHOOSEFONT cf;
	ZeroMemory(&cf, sizeof cf);
	cf.lStructSize = sizeof cf;
	cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
	cf.hwndOwner = parent;
	cf.lpLogFont = &lf;
	cf.rgbColors = color;
	if (ChooseFont(&cf)){
		color = cf.rgbColors;
		return true;
	}
	return false;
}

void MainWindow::OnCommand(int id) {
	MyDialog dijalog;
	LOGFONT font = lf;
	COLORREF c = color;
	switch (id) {
	case ID_TEXT:
	{
		MyDialog dijalog;
		InvalidateRect(*this, NULL, true);
		if (dijalog.DoModal(NULL, *this) == IDOK)
			this->str = dijalog.text;
		dijalog.text = str;
		break;
	}
	case ID_FONT:
		lf = font; color = c;
		if (GetFont(*this, lf, color))
			InvalidateRect(*this, NULL, true);
		break;
	case ID_EXIT:
		DestroyWindow(*this);
	}
}

	MainWindow::MainWindow() : color(RGB(0, 0, 0))
	{
		::ZeroMemory(&lf, sizeof(lf));
		_tcscpy(lf.lfFaceName, _T("Arial"));
		HDC hdc = GetDC(0);
		lf.lfHeight = -16 * GetDeviceCaps(hdc, LOGPIXELSY) / 72;
		lf.lfCharSet = EASTEUROPE_CHARSET;
		ReleaseDC(0, hdc);
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
