#pragma once
#include "ContactForm.h"
#include "Contact.h"
#include "wx/wx.h"
#include "wx/grid.h"
#include <vector>
#include <string>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString &title);
	void AddToGrid();
	void UpdateGrid(int Row);
	wxGrid *contactTable;
	wxGrid* contactSearchTable;

	bool isSearchGridVisible = false;

private:
	void CreateControls();
	void BindEventHandlers();

	void SearchContacts(wxCommandEvent& evt);
	bool PatternInCell(wxString pattern, wxString text);
	void nextSearchContacts(wxCommandEvent& evt);
	void prevSearchContacts(wxCommandEvent& evt);
	void resetSearchContacts(wxCommandEvent& evt);

	void DeleteContactFromButton(wxCommandEvent &evt);
	void EditContactFromButton(wxCommandEvent &evt);
	void AddContactFromButton(wxCommandEvent &evt);

	void NextContact(wxCommandEvent& evt);
	void ChooseContact(wxCommandEvent& evt);
	void PrevContact(wxCommandEvent& evt);
	void SetLabels();

	void AddSavedContacts();
	void OnWindowClosed(wxCloseEvent &evt);

	ContactForm* form;
	wxPanel* panel;


	wxButton* Szukaj;
	wxTextCtrl* inputField;
	wxButton* nextSearchButton;
	wxStaticText* foundCount;
	wxButton* prevSearchButton;
	wxButton* resetSearchButton;
	wxChoice* choice;

	std::vector<int> foundRowIndexes;
	unsigned int vectorIndex = 0;

	wxButton* addAContact;
	wxButton* deleteAContact;
	wxButton* editAContact;

	wxButton* nextContact;
	wxButton* prevContact;

	wxStaticText* imie;
	wxStaticText* nazwisko;
	wxStaticText* numerTel;
	wxStaticText* adres;
	wxStaticText* kodPocz;
	wxStaticText* email;
	wxStaticText* opis;
	wxTextCtrl* id;

	wxStaticText* contactImie;
	wxStaticText* contactNazwisko;
	wxStaticText* contactNumerTel;
	wxStaticText* contactAdres;
	wxStaticText* contactKodPocz;
	wxStaticText* contactEmail;
	wxStaticText* contactOpis;

	int displayedRow;

	wxImage* contactPhoto;

	wxStatusBar *statusBar;
};
