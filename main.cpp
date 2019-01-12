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

bool GetFont(HWND parent, LOGFONT &lf,COLORREF &color) {
	CHOOSEFONT odaberi;
	ZeroMemory(&odaberi, sizeof odaberi);
	odaberi.lStructSize = sizeof odaberi;
	odaberi.Flags = CF_INITTOLOGFONTSTRUCT
		| CF_SCREENFONTS | CF_EFFECTS;
	odaberi.hwndOwner = parent;
	odaberi.lpLogFont = &lf;
	odaberi.rgbColors = color;
	if (ChooseFont(&odaberi))
	{
		color = odaberi.rgbColors;
		return true;
	}
	return false;
	
}

void MainWindow::OnPaint(HDC hdc) {

	if (!str.size())
		return;
	RECT rc;
	GetClientRect(*this, &rc);

	long dx = rc.right / 9;
	long dy = rc.bottom / str.size();

	SetTextColor(hdc, color);
	HFONT hf = (HFONT)SelectObject(hdc,CreateFontIndirect(&lf));
	HBRUSH hb = (HBRUSH)GetStockObject(BLACK_BRUSH);

	for (int i = 0; i < str.size(); i++) {
		for (int j = 0; j < 8; j++) {
			
		rc = { j*dx,i*dy,(j + 1)*dx,(i + 1)*dy };
			bool white = str[i] & (1 << (7 - j));
			if (!white) 
				FillRect(hdc, &rc,hb);
		}
		 rc = { 8 * dx, i*dy, 9 * dx, (i + 1)*dy };
		DrawText(hdc, &str[i], 1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	DeleteObject(SelectObject(hdc,hf));
}
MainWindow::MainWindow() : color(RGB(0, 0, 0))
{
	::ZeroMemory(&lf,sizeof(lf));
	_tcscpy(lf.lfFaceName,_T("Arial"));

	HDC hdc = GetDC(0);
	lf.lfHeight = -16 * GetDeviceCaps(hdc, LOGPIXELSY) / 72;
	lf.lfCharSet = EASTEUROPE_CHARSET;
		ReleaseDC(0,hdc);

}
void MainWindow::OnCommand(int id) {
	
	switch(id){
	case ID_FONT:
		GetFont(*this, lf,color);
		InvalidateRect(*this, NULL, true);
		break;

	case ID_TEXT:
	{
		MyDialog dlg;
		dlg.text = str;
		if (dlg.DoModal(NULL, *this) == IDOK) {
			this->str = dlg.text;
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
