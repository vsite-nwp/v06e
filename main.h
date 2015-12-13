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
	CHOOSEFONT cf;
	LOGFONT lf;
	tstring t;
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
public:
	MainWindow()  {
		lf.lfHeight = 50;
		lf.lfCharSet = 0;
		lf.lfClipPrecision = 0;
		lf.lfEscapement = 0;
		lf.lfItalic = 0;
		lf.lfOrientation = 0;
		lf.lfQuality = 0;
		lf.lfPitchAndFamily = 0;
		lf.lfStrikeOut = 0;
		lf.lfOutPrecision = 0;
		lf.lfUnderline = 0;
		lf.lfWeight = 0;
		lf.lfWidth = 0;
		cf.rgbColors = CF_EFFECTS;
	};
};
