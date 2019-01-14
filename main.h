#include "nwpwin.h"
#include "nwpdlg.h"

class MyDialog : public Dialog {
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
public:
	tstring text;
};

class MainWindow : public Window {
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
public:
	tstring str;
	LOGFONT lf;
	COLORREF color;
	MainWindow();
};
