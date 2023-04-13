#include "wx/wx.h"
#include "ContactForm.h"
#include "MainFrame.h"
#include "App.h"
#include <string>

ContactForm::ContactForm(const wxString &title, tryb choice) : wxFrame(nullptr, wxID_ANY, title)
{
	Tryb = choice;
	form = new wxFrame(nullptr, wxID_ANY, title);
	form->SetClientSize(500, 400);
	form->Center();
	form->Show();
	CreateControls();
	BindEventHandlers();
}

ContactForm::ContactForm(const wxString &title, tryb choice, int Row) : wxFrame(nullptr, wxID_ANY, title)
{
	Tryb = choice;
	editableRow = Row;
	form = new wxFrame(nullptr, wxID_ANY, title);
	form->SetClientSize(500, 400);
	form->Center();
	form->Show();
	if (wxGetApp().mainFrame->isSearchGridVisible)
	{
		CreateControls3();
	}
	else CreateControls2();
	BindEventHandlers();
}

ContactForm::~ContactForm()
{
	form->Destroy();

}

void ContactForm::CreateControls()
{
	panel = new wxPanel(form, wxID_ANY, wxPoint(0, 0), wxSize(500, 400));

	imie = new wxTextCtrl(panel, wxID_ANY, "Imie", wxPoint(10, 20), wxSize(200, 20));
	imietxt = new wxStaticText(panel, wxID_ANY, "Imie", wxPoint(220, 20));

	nazwisko = new wxTextCtrl(panel, wxID_ANY, "Nazwisko", wxPoint(10, 50), wxSize(200, 20));
	nazwiskotxt = new wxStaticText(panel, wxID_ANY, "Nazwisko", wxPoint(220, 50));

	numerTel = new wxTextCtrl(panel, wxID_ANY, "Numer Telefonu", wxPoint(10, 80), wxSize(200, 20));
	numerteltxt = new wxStaticText(panel, wxID_ANY, "Numer Telefonu", wxPoint(220, 80));

	adres = new wxTextCtrl(panel, wxID_ANY, "Adres", wxPoint(10, 110), wxSize(200, 20));
	adrestxt = new wxStaticText(panel, wxID_ANY, "Adres", wxPoint(220, 110));

	kodPocz = new wxTextCtrl(panel, wxID_ANY, "Kod Pocztowy", wxPoint(10, 140), wxSize(200, 20));
	kodpocztxt = new wxStaticText(panel, wxID_ANY, "Kod Pocztowy", wxPoint(220, 140));

	email = new wxTextCtrl(panel, wxID_ANY, "Email", wxPoint(10, 170), wxSize(200, 20));
	emailtxt = new wxStaticText(panel, wxID_ANY, "Email", wxPoint(220, 170));

	opis = new wxTextCtrl(panel, wxID_ANY, "Opis", wxPoint(10, 200), wxSize(450, 180), wxTE_MULTILINE);

	ok = new wxButton(panel, wxID_ANY, "Ok", wxPoint(400, 20), wxSize(60, 23));
}

void ContactForm::CreateControls2()
{
	panel = new wxPanel(form, wxID_ANY, wxPoint(0, 0), wxSize(500, 400));

	imie = new wxTextCtrl(panel, wxID_ANY,
						  wxGetApp().mainFrame->contactTable->GetCellValue(editableRow, 0), wxPoint(10, 20), wxSize(200, 20));
	imietxt = new wxStaticText(panel, wxID_ANY, "Imie", wxPoint(220, 20));

	nazwisko = new wxTextCtrl(panel, wxID_ANY,
							  wxGetApp().mainFrame->contactTable->GetCellValue(editableRow, 1), wxPoint(10, 50), wxSize(200, 20));
	nazwiskotxt = new wxStaticText(panel, wxID_ANY, "Nazwisko", wxPoint(220, 50));

	numerTel = new wxTextCtrl(panel, wxID_ANY,
							  wxGetApp().mainFrame->contactTable->GetCellValue(editableRow, 2), wxPoint(10, 80), wxSize(200, 20));
	numerteltxt = new wxStaticText(panel, wxID_ANY, "Numer Telefonu", wxPoint(220, 80));

	adres = new wxTextCtrl(panel, wxID_ANY,
						   wxGetApp().mainFrame->contactTable->GetCellValue(editableRow, 3), wxPoint(10, 110), wxSize(200, 20));
	adrestxt = new wxStaticText(panel, wxID_ANY, "Adres", wxPoint(220, 110));

	kodPocz = new wxTextCtrl(panel, wxID_ANY,
							 wxGetApp().mainFrame->contactTable->GetCellValue(editableRow, 4), wxPoint(10, 140), wxSize(200, 20));
	kodpocztxt = new wxStaticText(panel, wxID_ANY, "Kod Pocztowy", wxPoint(220, 140));

	email = new wxTextCtrl(panel, wxID_ANY,
						   wxGetApp().mainFrame->contactTable->GetCellValue(editableRow, 5), wxPoint(10, 170), wxSize(200, 20));
	emailtxt = new wxStaticText(panel, wxID_ANY, "Email", wxPoint(220, 170));

	opis = new wxTextCtrl(panel, wxID_ANY,
						  wxGetApp().mainFrame->contactTable->GetCellValue(editableRow, 6), wxPoint(10, 200), wxSize(450, 180), wxTE_MULTILINE);

	ok = new wxButton(panel, wxID_ANY, "Ok", wxPoint(400, 20), wxSize(60, 23));
}

bool ContactForm::is_number(std::string s)
{
	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (i == 0 && s[i] == '+' ) continue;
		if ((int) s[i] < 48 || (int)s[i] > 57) return false;
	}
	return true;
}

void ContactForm::CreateControls3()
{
	panel = new wxPanel(form, wxID_ANY, wxPoint(0, 0), wxSize(500, 400));

	imie = new wxTextCtrl(panel, wxID_ANY,
		wxGetApp().mainFrame->contactSearchTable->GetCellValue(editableRow, 0), wxPoint(10, 20), wxSize(200, 20));
	imietxt = new wxStaticText(panel, wxID_ANY, "Imie", wxPoint(220, 20));

	nazwisko = new wxTextCtrl(panel, wxID_ANY,
		wxGetApp().mainFrame->contactSearchTable->GetCellValue(editableRow, 1), wxPoint(10, 50), wxSize(200, 20));
	nazwiskotxt = new wxStaticText(panel, wxID_ANY, "Nazwisko", wxPoint(220, 50));

	numerTel = new wxTextCtrl(panel, wxID_ANY,
		wxGetApp().mainFrame->contactSearchTable->GetCellValue(editableRow, 2), wxPoint(10, 80), wxSize(200, 20));
	numerteltxt = new wxStaticText(panel, wxID_ANY, "Numer Telefonu", wxPoint(220, 80));

	adres = new wxTextCtrl(panel, wxID_ANY,
		wxGetApp().mainFrame->contactSearchTable->GetCellValue(editableRow, 3), wxPoint(10, 110), wxSize(200, 20));
	adrestxt = new wxStaticText(panel, wxID_ANY, "Adres", wxPoint(220, 110));

	kodPocz = new wxTextCtrl(panel, wxID_ANY,
		wxGetApp().mainFrame->contactSearchTable->GetCellValue(editableRow, 4), wxPoint(10, 140), wxSize(200, 20));
	kodpocztxt = new wxStaticText(panel, wxID_ANY, "Kod Pocztowy", wxPoint(220, 140));

	email = new wxTextCtrl(panel, wxID_ANY,
		wxGetApp().mainFrame->contactSearchTable->GetCellValue(editableRow, 5), wxPoint(10, 170), wxSize(200, 20));
	emailtxt = new wxStaticText(panel, wxID_ANY, "Email", wxPoint(220, 170));

	opis = new wxTextCtrl(panel, wxID_ANY,
		wxGetApp().mainFrame->contactSearchTable->GetCellValue(editableRow, 6), wxPoint(10, 200), wxSize(450, 180), wxTE_MULTILINE);

	ok = new wxButton(panel, wxID_ANY, "Ok", wxPoint(400, 20), wxSize(60, 23));
}

void ContactForm::BindEventHandlers()
{
	ok->Bind(wxEVT_BUTTON, &ContactForm::PassInputToMainFrame, this);
	form->Bind(wxEVT_CLOSE_WINDOW, &ContactForm::OnWindowClosed, this);
}

void ContactForm::PassInputToMainFrame(wxCommandEvent &evt)
{
	imiegrid = imie->GetValue();
	nazwiskogrid = nazwisko->GetValue();
	numerTelgrid = numerTel->GetValue();
	adresgrid = adres->GetValue();
	kodPoczgrid = kodPocz->GetValue();
	emailgrid = email->GetValue();
	opisgrid = opis->GetValue();

	if (is_number(std::string(numerTelgrid.mb_str())))
	{
		if (Tryb == Add)
			wxGetApp().mainFrame->AddToGrid();
		else if (Tryb == Edit)
			wxGetApp().mainFrame->UpdateGrid(editableRow);
		wxGetApp().mainFrame->Enable();

		ContactForm::~ContactForm();
	}
	else {
		wxMessageDialog dialog(this, "Nieprawidlowy numer telefonu", "Zla wartosc", wxOK);
		int result = dialog.ShowModal();
	}
}

void ContactForm::OnWindowClosed(wxCloseEvent &evt)
{
	wxGetApp().mainFrame->Enable();
	evt.Skip();
}
