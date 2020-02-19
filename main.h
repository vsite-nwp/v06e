#include "nwpwin.h"
#include "nwpdlg.h"
#include <vector>

class MyDialog : public Dialog {
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
	
	std::vector <std::string> vektor;
	void pushaj(std::string s) {
		vektor.push_back(s);
	}
	void clearaj() {
		vektor.clear();
	}
public:
	std::vector<std::string>::iterator begin() {
		if (vektor.begin() != vektor.end()) {
			return vektor.begin();
		}
		else { return vektor.end(); }
	}
	std::vector<std::string>::iterator end() {
		return vektor.end();
	}
	tstring str;
	bool isempty() {
		return vektor.empty();
	}
	HWND mainwin;
};

class MainWindow : public Window {
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
	CHOOSEFONT cf;
	LOGFONT logi;
	bool flag = false;
	tstring str;
	std::vector <std::string> vektor;
	MyDialog* md=new MyDialog();
	HWND mainwin;
public:
	void kopiraj() {
		if (!md->isempty()) {
			for (std::vector<std::string>::iterator it = md->begin(); it != md->end(); ++it) {
				vektor.push_back(*it);
			}
			str = md->str;
		}
	}
	char vratiVrijednost(int i, int j) {
		return vektor[i][j];
	}
	void init(HWND h) {
		mainwin = h;
		md->mainwin = mainwin;
	}
};
