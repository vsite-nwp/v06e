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
	RECT rect;
	GetClientRect(*this, &rect);
	/*for (int i = 0; i < text.size(); i++) {
		for (int j = 0; j < 8; j++) {

			HRGN x = CreateRectRgn(6, 3, 6, 3);
			if (j % 2 == 0)
				FillRgn(hdc, x, (HBRUSH) GetStockObject(BLACK_BRUSH));
		}
	}*/
}

void MainWindow::OnCommand(int id) {
	switch (id) {
	case ID_FONT:
		break;
	case ID_TEXT:
		{MyDialog text;
		text.text = wintext;
		if (text.DoModal(0, *this) == IDOK)
			wintext = text.text;
		break;}
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
