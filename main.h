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
		lf.lfHeight = -20;
	}
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};

class Font {
	HFONT h;
public:
	Font(const LOGFONT& lf) {
		h = ::CreateFontIndirect(&lf);
	}
	Font(const TCHAR* name, int height, bool bold = false, bool italic = false, int angle = 0, bool underline = false) : h(NULL) {
		h = ::CreateFont(height, 0, angle * 10, 0, bold ? FW_BOLD : FW_NORMAL, italic, underline, 0, 0, 0, 0, 0, 0, name);
	}
	~Font() { if (h) ::DeleteObject(h); }
	operator HFONT() { return h; }
};
class DCSelObj {
	HDC hdc;
	HGDIOBJ hOld;
public:
	DCSelObj(HDC hdc, HGDIOBJ hObj) :
		hdc(hdc), hOld(::SelectObject(hdc, hObj)) { }
	~DCSelObj() { ::SelectObject(hdc, hOld); }
};
