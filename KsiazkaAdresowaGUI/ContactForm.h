#pragma once
#include "wx/wx.h"

enum tryb
{
	Edit = 0,
	Add = 1
};

class ContactForm : public wxFrame
{
public:
	ContactForm(const wxString &title, tryb choice);
	ContactForm(const wxString &title, tryb choice, int Row);

	int editableRow;
	tryb Tryb;
	wxString imiegrid;
	wxString nazwiskogrid;
	wxString numerTelgrid;
	wxString adresgrid;
	wxString kodPoczgrid;
	wxString emailgrid;
	wxString opisgrid;

	~ContactForm();

private:
	void CreateControls();
	void CreateControls2();
	void CreateControls3();

	void BindEventHandlers();
	void PassInputToMainFrame(wxCommandEvent &evt);

	bool is_number(std::string s);

	void OnWindowClosed(wxCloseEvent &evt);

	wxFrame *form;
	wxPanel *panel;

	wxTextCtrl *imie;
	wxStaticText *imietxt;

	wxTextCtrl *nazwisko;
	wxStaticText *nazwiskotxt;

	wxTextCtrl *numerTel;
	wxStaticText *numerteltxt;

	wxTextCtrl *adres;
	wxStaticText *adrestxt;

	wxTextCtrl *kodPocz;
	wxStaticText *kodpocztxt;

	wxTextCtrl *email;
	wxStaticText *emailtxt;

	wxTextCtrl *opis;

	wxButton *ok;
};
