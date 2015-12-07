#include "nwpwin.h"
#include "nwpdlg.h"

class MyDialog : public Dialog {
public:
	tstring t;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
protected:
	LOGFONT lf;
	tstring t;
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
