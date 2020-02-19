#include "main.h"
#include "rc.h"
#include <vector>
#include <bitset>
#include<iostream>
int MyDialog::IDD(){
	return IDD_DIALOG;
}

bool MyDialog::OnInitDialog(){
	return true;
}

bool MyDialog::OnOK(){
	str=this->GetText(IDC_EDIT1);
	clearaj();
	for (int i = 0; i < str.length();++i) {
		pushaj((std::bitset<8>(str[i])).to_string());
	}
	
	InvalidateRect(mainwin, 0, true);
	UpdateWindow(mainwin);
	return true;
}
void MainWindow::OnPaint(HDC hdc) {
	RECT r;
	HRGN region;
	GetClientRect(*this, &r);
	int width = r.right - r.left;
	int height = r.bottom - r.top;
	kopiraj();
	if (flag) {
		SelectFont(hdc, CreateFontIndirect(&logi));
		SetTextColor(hdc, cf.rgbColors);
	}
	else {
		SelectFont(hdc, CreateFontA(15, 15, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Default Font"));
		SetTextColor(hdc, RGB(0, 0, 0));
	}
	for (int i = 0; i < str.length(); ++i) {
		for (int j = 0; j < 9; ++j) {
			region=CreateRectRgn((int)j*width / 9,(int) i*height / str.length(),(int) (j + 1)*width / 9,(int) (i + 1)*height / str.length());
			if (j < 8) {
				if (vratiVrijednost(i,j) == '1') {
					FillRgn(hdc, region, CreateSolidBrush(RGB(0, 0, 0)));
				}
}
			else {
				TextOut(hdc,(int) (((double)j+0.5)*width / 9),(int)(((double)i+0.5)*height / str.length()),&str[i] , 1);
			}
				
			}
		
		}
	}
void MainWindow::OnCommand(int id) {
	switch(id){
	case ID_FONT:
		cf.lStructSize = sizeof(CHOOSEFONT);
		cf.hwndOwner = mainwin;
		cf.lpLogFont = &logi;
		cf.Flags = CF_SCREENFONTS|CF_EFFECTS;
		cf.rgbColors = RGB(255, 0, 0);
		cf.lCustData = 0L;
		cf.lpfnHook = NULL;
		cf.lpTemplateName = NULL;
		cf.hInstance = NULL;
		cf.lpszStyle = NULL;
		cf.nFontType = SCREEN_FONTTYPE;
		cf.nSizeMin = 24;
		ChooseFont(&cf);
		flag = true;
		InvalidateRect(mainwin, 0, true);
		UpdateWindow(mainwin);
		
		break;
	case ID_TEXT:
		md->DoModal(0,*this);
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
	wnd.init(wnd);
	return app.Run();
}
