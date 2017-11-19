#include "nwpwin.h"
#include "nwpdlg.h"

class MyDialog : public Dialog {
public:
	tstring text;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {

public:
	tstring text;
	MyDialog dia;
	LOGFONT lf;
	MainWindow(){
		::ZeroMemory(&lf, sizeof(lf));
		_tcscpy(lf.lfFaceName, _T("Arial"));
	}
protected:
	
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
