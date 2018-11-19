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
	RECT rc;
	GetClientRect(*this, &rc);
	long x = rc.right / 9;
	long y = rc.bottom / window_text.size();
	HFONT previous_font = (HFONT)SelectObject(hdc, CreateFontIndirect(&font_style));
	SetTextColor(hdc, text_color);
	for (int i = 0; i < window_text.size(); i++) {
		for (int j = 0; j < 8; j++) {
			rc = { j*x, i*y, (j + 1)*x, (i + 1)*y };
			if ((window_text[i] & (1 << (7 - j))) == 0) FillRect(hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
		rc = { 8 * x, i*y, 9 * x, (i + 1)*y };
		DrawText(hdc, &window_text[i], 1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	DeleteObject((HFONT)SelectObject(hdc, previous_font));
}

void GetFont(HWND parent, LOGFONT &fontstyle, COLORREF &color) {
	CHOOSEFONT sel_font;
	ZeroMemory(&sel_font, sizeof(sel_font));
	sel_font.hwndOwner = parent;
	sel_font.lStructSize = sizeof(sel_font);
	sel_font.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
	sel_font.lpLogFont = &fontstyle;
	sel_font.rgbColors = color;
	ChooseFont(&sel_font);
	color = sel_font.rgbColors;
}

void MainWindow::OnCommand(int id) {
	switch(id){
	case ID_FONT:
		GetFont(*this, font_style, text_color);
		break;
	case ID_TEXT: {
		MyDialog dialog;
		dialog.text = window_text;
		if (dialog.DoModal(0, *this) == IDOK)
			window_text = dialog.text;
		break; }
	case ID_EXIT:
		DestroyWindow(*this);
		break;
	}
	InvalidateRect(*this, NULL, true);
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
