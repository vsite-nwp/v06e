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
	tstring wintext;
	MainWindow() : wintext("Luka Sever") {}
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
