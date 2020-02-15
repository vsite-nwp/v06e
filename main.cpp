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

void GetFont(HWND parent, LOGFONT &lf, COLORREF& color)
{
	CHOOSEFONT cf;
	LOGFONT former_font = lf;
	ZeroMemory(&cf, sizeof cf);
	cf.lStructSize = sizeof cf;
	cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
	cf.hwndOwner = parent;
	cf.lpLogFont = &lf;
	cf.rgbColors = color;
	if (ChooseFont(&cf))
		color = cf.rgbColors;
	else
		lf = former_font;
}

void MainWindow::OnPaint(HDC hdc) {
	if (!str.size())
		return;
	RECT rc;
	GetClientRect(*this, &rc);
	int x = rc.right / 9;
	int y = rc.bottom / str.size();
	SetTextColor(hdc, color);
	HFONT hFont = (HFONT)SelectObject(hdc, CreateFontIndirect(&lf));
	for (int i = 0; i < str.size(); i++) {
		for (int j = 0; j < 8; j++) {
			rc = { j * x, i * y, (j + 1) * x, (i + 1) * y };
			if ((str[i] & (1 << (7 - j))) == 0)
				FillRect(hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
		rc = { 8 * x, i * y, 9 * x, (i + 1) * y };
		DrawText(hdc, &str[i], 1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	//DeleteObject((HFONT)SelectObject(hdc, hFont));
}

void MainWindow::OnCommand(int id) {
	switch(id){
	case ID_FONT:
		GetFont(*this, lf, color);
		break;
	case ID_TEXT:
	{
		MyDialog dialog;
		dialog.text = str;
		if (dialog.DoModal(0, *this) == IDOK) {
			str = dialog.text;
		}
		break;
	}
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
