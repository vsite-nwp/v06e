#include "main.h"
#include "rc.h"


bool GetFont(HWND parent, LOGFONT &lf, COLORREF& col)
{
	CHOOSEFONT cf;
	ZeroMemory(&cf, sizeof cf);
	cf.lStructSize = sizeof cf;
	cf.Flags = CF_INITTOLOGFONTSTRUCT
		| CF_SCREENFONTS | CF_EFFECTS;
	cf.hwndOwner = parent;
	cf.lpLogFont = &lf;
	cf.rgbColors = col;
	col = cf.rgbColors;
	return ChooseFont(&cf);
}



int MyDialog::IDD() {
	return IDD_DIALOG;
}

bool MyDialog::OnInitDialog() {
	SetText(IDC_EDIT1, text);
	return true;
}

bool MyDialog::OnOK() {
	text = GetText(IDC_EDIT1);
	return true;
}


void MainWindow::OnPaint(HDC hdc) {
	if (!text.size())
		return;
	RECT screen;
	GetClientRect(*this, &screen);
	int dy = screen.bottom / text.size();
	int dx = screen.right / 9;
	Font f(lf);
	DCSelObj d(hdc, f);
	SetTextColor(hdc,fore);
	for (int i = 0; i < text.size(); i++) {
		for (int j = 0; j < 8; j++) {
			RECT r = { j*dx, i*dy, (j + 1)*dx, (i + 1)*dy };
			if ((text[i] & (1 << (7 - j))) == 0)
				FillRect(hdc, &r, (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
		RECT r = { 8 * dx , i*dy, 9 * dx , (i + 1)*dy };
		::DrawText(hdc, &text[i], 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

}

void MainWindow::OnCommand(int id) {
	
	switch (id) {
	case ID_FONT:
		if(GetFont(*this, lf, fore))InvalidateRect(*this, NULL, true);
		break;
	case ID_TEXT:
	{
		MyDialog dia;
		dia.text = text;
		if (dia.DoModal(NULL, *this) == IDOK) {
			this->text = dia.text;
			InvalidateRect(*this, NULL, true);
		}
		break;
	}
	case ID_EXIT:
		DestroyWindow(*this);
		break;
	}
	
}

void MainWindow::OnDestroy() {
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
