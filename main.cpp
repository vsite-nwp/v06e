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

void GetFont(HWND master, LOGFONT &fl){
	CHOOSEFONT cf;
	ZeroMemory(&cf, sizeof cf);
	cf.hwndOwner = master;
	cf.lStructSize = sizeof cf;
	cf.Flags = CF_INITTOLOGFONTSTRUCT
		| CF_SCREENFONTS | CF_EFFECTS;
	cf.lpLogFont = &fl;
	ChooseFont(&cf);
	}


void MainWindow::OnPaint(HDC hdc) {
	RECT rect;
	GetClientRect(*this, &rect);
	long x = rect.right / 9;
	long y = rect.bottom / wintext.size();
	HFONT used_font = (HFONT)SelectObject(hdc, CreateFontIndirect(&fl));
	for (int i = 0; i < wintext.size(); i++) {
		for (int j = 0; j < 8; j++) {
			rect = {j*x, i*y, (j + 1)*x, (i + 1)*y};
			if ((wintext[i] & (1 << (7 - j))) == 0)
				FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
		rect = {8*x, i*y, 9*x, (i + 1)*y};
		DrawText(hdc, &wintext[i], 1, &rect, DT_RIGHT-1 | DT_VCENTER | DT_SINGLELINE);
	}
	DeleteObject((HFONT)SelectObject(hdc, used_font));
}

void MainWindow::OnCommand(int id) {
	switch (id) {
	case ID_FONT: {
		GetFont(*this, fl);
		break;
		}	
	case ID_TEXT:{
		MyDialog dlg;
		dlg.text = wintext;
		if (dlg.DoModal(0, *this) == IDOK)
			wintext = dlg.text;
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
