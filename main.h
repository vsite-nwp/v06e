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
protected:
	
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
