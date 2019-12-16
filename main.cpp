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
	RECT rectangle;
	GetClientRect(*this, &rectangle);
	int x = rectangle.right / 9;
	int y = rectangle.bottom / windowText.size();
	HFONT previous_font = (HFONT)SelectObject(hdc, CreateFontIndirect(&log));
	SetTextColor(hdc, color);
	int i = 0;
	while (i < windowText.size()) {
		int j = 0;
		while (j < 8) {
			rectangle = { j*x, i*y, (j+1)*x, (i+1)*y };
			if ((windowText[i] & (1 << (7 - j))) == 0) {
				FillRect(hdc, &rectangle, (HBRUSH)GetStockObject(BLACK_BRUSH));
			}
			++j;
		}
		rectangle = { 8*x , i*y, 9*x , (i+1)*y };
		DrawText(hdc, &windowText[i], 1, &rectangle, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		++i;
	}
	DeleteObject((HFONT)SelectObject(hdc, previous_font));
}

void MainWindow::OnCommand(int id) {
	switch (id) {
	case ID_FONT: {
		LOGFONT lcopy = log;
		COLORREF ccopy = color;
		font.lpLogFont = &lcopy;
		font.rgbColors = ccopy;
		if (ChooseFont(&font) == true) {
			color = font.rgbColors;
			log = lcopy;
			InvalidateRect(*this, NULL, true);
		}
		break;
	}
	case ID_TEXT: {
		MyDialog dlg;
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
