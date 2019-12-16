#include "main.h"
#include "rc.h"

bool GetFont(HWND parent, LOGFONT& log, COLORREF& color)
{
	CHOOSEFONT cf;
	ZeroMemory(&cf, sizeof cf);
	cf.lStructSize = sizeof cf;
	cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
	cf.hwndOwner = parent;
	cf.lpLogFont = &log;
	cf.rgbColors = color;
	bool fontChange = ChooseFont(&cf);
	color = cf.rgbColors;
	return fontChange;
}

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
	if (windowText.size() == 0) {
		return;
	}
	RECT screen;
	GetClientRect(*this, &screen);
	int x = screen.right / 9;
	int y = screen.bottom / windowText.size();
	HFONT previous_font = (HFONT)SelectObject(hdc, CreateFontIndirect(&log));
	SetTextColor(hdc, color);
	for (int i = 0; i < windowText.size(); ++i) {
		for (int j = 0; j < 8; ++j) {
			screen = { j*x, i*y, (j + 1)*x, (i + 1)*y };
			if ((windowText[i] & (1 << (7 - j))) == 0) {
				FillRect(hdc, &screen, (HBRUSH)GetStockObject(BLACK_BRUSH));
			}
		}
		screen = { 8 * x , i*y, 9 * x , (i + 1)*y };
		DrawText(hdc, &windowText[i], 1, &screen, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	DeleteObject((HFONT)SelectObject(hdc, previous_font));
}

void MainWindow::OnCommand(int id) {
	LOGFONT logCopy = log;
	COLORREF colorCopy = color;

	switch (id) {
	case ID_FONT: {
		if (GetFont(*this, log, color)) {
			InvalidateRect(*this, NULL, true);
		}
		else {
			log = logCopy;
			color = colorCopy;
		}
		break;
	}
	case ID_TEXT: {
		MyDialog dlg;
		dlg.text = windowText;
		if (dlg.DoModal(NULL, *this) == IDOK) {
			windowText = dlg.text;
			InvalidateRect(*this, NULL, true);
		}
		break;
	}
	case ID_EXIT: {
		DestroyWindow(*this);
		break;
	}
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
