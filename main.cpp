#include "main.h"
#include "rc.h"




int MyDialog::IDD(){
	return IDD_DIALOG;
}

bool MyDialog::OnInitDialog(){
	return true;
}

bool MyDialog::OnOK(){
	
	t = GetText(IDC_EDIT1);
	return true;
}


void MainWindow::OnPaint(HDC hdc) {
	
	RECT rc;
	GetClientRect(*this,&rc);
	SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	HFONT hf=(HFONT)SelectObject(hdc, CreateFontIndirect(&lf));
	for (int i = 0; i < t.length(); ++i){
		
		for (int j = 0; j < 8; ++j) {
			if (!(t[i] & (1 << (7 - j)))) {
				
				Rectangle(hdc, j*rc.right / 9, i*rc.bottom / t.length(), (j + 1)*rc.right / 9, (i + 1)*rc.bottom / t.length());
				
			}
			
		TextOut(hdc,i+1*rc.right-100,i*rc.bottom/t.length(),&t[i],1);
			
		}
		
		
		
		
	}
	DeleteObject(hf);
}

void MainWindow::OnCommand(int id) {
	switch(id){
	case ID_FONT:
		CHOOSEFONT cf;
		ZeroMemory(&cf, sizeof(cf));
		cf.lStructSize = sizeof(cf);
		cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
		cf.lpLogFont = &lf;
		ChooseFont(&cf);
		InvalidateRect(*this, NULL, true);
		break;
	case ID_TEXT:
	{
		MyDialog dlg;
		dlg.t = t;
		if (dlg.DoModal(NULL, *this) == IDOK) {
			this->t = dlg.t;
		}
	}
		InvalidateRect(*this, NULL, true);
		break;
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
