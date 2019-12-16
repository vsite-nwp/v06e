#include "main.h"
#include "rc.h"
#include <vector>
#include <bitset>
#include<iostream>
CHOOSEFONT cf;
LOGFONT logi;
HWND mainwin;
tstring str;
int width = 0;
int height = 0;

std::vector <std::string> vektor;
MyDialog* md = new MyDialog();
int MyDialog::IDD(){
	return IDD_DIALOG;
}

bool MyDialog::OnInitDialog(){
	return true;
}

bool MyDialog::OnOK(){
	str=md->GetText(IDC_EDIT1);
	vektor.clear();
	for (int i = 0; i < str.length();++i) {
		vektor.push_back((std::bitset<8>(str[i])).to_string());
	}
	InvalidateRect(mainwin, 0, true);
	UpdateWindow(mainwin);
	return true;
}


void MainWindow::OnPaint(HDC hdc) {
	if (&logi != nullptr) {
		SelectFont(hdc, CreateFontIndirect(&logi));
		SetTextColor(hdc, cf.rgbColors);
	}
	RECT r;
	HRGN region;
	GetClientRect(*this,&r);
	width = r.right-r.left;
	height = r.bottom - r.top;
	for (int i = 0; i < str.length(); ++i) {
		for (int j = 0; j < 9; ++j) {
			region=CreateRectRgn((int)j*width / 9,(int) i*height / str.length(),(int) (j + 1)*width / 9,(int) (i + 1)*height / str.length());
			if (j < 8) {
				if (vektor[i][j] == '1') {
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
	mainwin = wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"),
	(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.Run();
}
