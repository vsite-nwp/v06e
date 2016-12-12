#include "main.h"
#include "rc.h"
bool GetFont(HWND parent,LOGFONT &lf, COLORREF &col) {
	CHOOSEFONT cf;
	ZeroMemory(&cf, sizeof cf);
	cf.lStructSize = sizeof cf;
	cf.Flags = CF_INITTOLOGFONTSTRUCT
		| CF_SCREENFONTS | CF_EFFECTS;
	cf.hwndOwner = parent;
	cf.lpLogFont = &lf;
	cf.rgbColors = col;
	if (ChooseFont(&cf)) {
		col = cf.rgbColors;
		return true;
	}
	return false;
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
	RECT rc;
	GetClientRect(*this, &rc);
	double dx = rc.right / 9;
	if (!s.size())
		return;
	double dy = rc.bottom / s.size();
	SetTextColor(hdc, col);
	HFONT hf = (HFONT)SelectObject(hdc,CreateFontIndirect(&lf));
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < 8; j++) {
			RECT r = { j*dx, i*dy, (j + 1)*dx, (i + 1)*dy };
			bool black = s[i] & (1 << (7 - j));
			if (!black) FillRect(hdc, &r, HBRUSH(GetStockObject(BLACK_BRUSH)));
		}
		RECT r = { 8*dx, i*dy, 9 *dx, (i + 1)*dy };
		DrawText(hdc,&s[i],1,&r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	DeleteObject(hf);
}

MainWindow::MainWindow() : col(RGB(0, 0, 0)) {
	::ZeroMemory(&lf, sizeof(lf));
	_tcscpy(lf.lfFaceName, _T("Arial"));

	HDC hdc = GetDC(0);
	lf.lfHeight=-16 * GetDeviceCaps(hdc, LOGPIXELSY) / 72;
	lf.lfCharSet = EASTEUROPE_CHARSET;
		ReleaseDC(0, hdc);
}

void MainWindow::OnCommand(int id) {
	switch(id){
	case ID_FONT:
		GetFont(*this, lf, col);
		InvalidateRect(*this, NULL, true);
		break;
	case ID_TEXT:
	{
		MyDialog dlg;
		dlg.text = s;
		if (dlg.DoModal(NULL, *this) == IDOK) {
			this->s = dlg.text;
		}
		InvalidateRect(*this, NULL, true);
		break;
	}
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
