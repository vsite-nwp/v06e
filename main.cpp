#include "main.h"
#include "rc.h"


int MyDialog::IDD() {
	return IDD_DIALOG;
}
bool MyDialog::OnInitDialog() {
	SetText(IDC_EDIT1, tekst);
	return true;
}
bool MyDialog::OnOK() {
	tekst = GetText(IDC_EDIT1);
	return true;
}
void MainWindow::OnPaint(HDC hdc) {
	if (str.size()==0)
		return;
	RECT rec;
	GetClientRect(*this, &rec);
	int rig = rec.right / 9;
	int bot = rec.bottom / str.size();
	SetTextColor(hdc, col);
	HFONT hf = (HFONT)SelectObject(hdc, CreateFontIndirect(&logf));
	HBRUSH hb = (HBRUSH)GetStockObject(BLACK_BRUSH);
	int i = 0;
	do {
		int j = 0;
		do {
			rec = {
				j * rig,i * bot,(j + 1) * rig,(i + 1) * bot
			};
			bool bijela = str[i] & (1 << (7 - j));
			if (bijela == false)
				FillRect(hdc, &rec, hb);
			j++;
		} while (j < 8);
		rec = {
			8 * rig,i * bot,9 * rig,(i + 1) * bot
		};
		DrawText(hdc, &str[i], 1, &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		i++;
	} while (i < str.size());
	DeleteObject(SelectObject(hdc, hf));
}
MainWindow::MainWindow() : col(RGB(0, 0, 0)) {
	::ZeroMemory(&logf, sizeof(logf));
	_tcscpy(logf.lfFaceName, _T("Arial"));
	HDC hdc = GetDC(0);
	logf.lfHeight = -16 * GetDeviceCaps(hdc, LOGPIXELSY) / 72;
	logf.lfCharSet = EASTEUROPE_CHARSET;
	ReleaseDC(0, hdc);
}
bool GetFont(HWND parent, LOGFONT& lf, COLORREF& col) {
	CHOOSEFONT chfont;
	ZeroMemory(&chfont, sizeof chfont);
	chfont.lStructSize = sizeof chfont;
	chfont.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
	chfont.hwndOwner = parent;
	chfont.lpLogFont = &lf;
	chfont.rgbColors = col;
	if (ChooseFont(&chfont)) {
		col = chfont.rgbColors;
		return true;
	}
	return false;
}
void MainWindow::OnCommand(int id) {
	MyDialog dialog;
	LOGFONT font = logf;
	COLORREF color = col;
	if (id == ID_FONT)
		if (GetFont(*this, logf, color))
			InvalidateRect(*this, NULL, true);
		else {
			logf = font; 
			col = color;
		}
	if (id == ID_TEXT)
	MyDialog dialog;
	dialog.tekst = str;
	if (dialog.DoModal(NULL, *this) == IDOK)
		this->str = dialog.tekst;
	InvalidateRect(*this, NULL, true);
	if (id == ID_EXIT)
		DestroyWindow(*this);
}
void MainWindow::OnDestroy() {
	::PostQuitMessage(0);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow) {
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"),
		(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.Run();
}
