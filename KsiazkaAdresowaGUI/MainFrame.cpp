#include "wx/wx.h"
#include "wx/grid.h"
#include "MainFrame.h"
#include "Contact.h"
#include "ContactForm.h"
#include "wx/image.h"
#include "App.h"
#include <wx/filename.h>
#include <iostream>
#include <vector>
#include <string>
#include <iostream>

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	BindEventHandlers();
	AddSavedContacts();

	statusBar = CreateStatusBar();
}

void MainFrame::CreateControls()
{
	panel = new wxPanel(this);

	inputField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(540, 15), wxSize(300, 23), wxTE_PROCESS_ENTER);
	Szukaj = new wxButton(panel, wxID_ANY, "Szukaj", wxPoint(470, 14), wxSize(60, 25));
	prevSearchButton = new wxButton(panel, wxID_ANY, "Poprzedni", wxPoint(850, 14), wxSize(60, 25));
	nextSearchButton = new wxButton(panel, wxID_ANY, "Nastepny", wxPoint(920, 14), wxSize(60, 25));
	resetSearchButton = new wxButton(panel, wxID_ANY, "Reset", wxPoint(990, 14), wxSize(60, 25));
	foundCount = new wxStaticText(panel, wxID_ANY, "  - znalezionych kontaktow", wxPoint(1070, 18));

	wxArrayString choices;
	choices.Add("Imie");
	choices.Add("Nazwisko");
	choices.Add("NumerTel");
	choices.Add("Adres");
	choices.Add("KodPocz");
	choices.Add("Email");
	choices.Add("Opis");
	choice = new wxChoice(panel, wxID_ANY, wxPoint(360, 15), wxSize(100, 25), choices);
	choice->Select(0);

	contactTable = new wxGrid(panel, wxID_ANY, wxPoint(10, 50), wxSize(1480, 350));
	contactTable->CreateGrid(0, 7);
	contactTable->DisableCellEditControl();
	contactTable->SetRowLabelSize(20);
	contactTable->SetColLabelValue(0, "Imie");
	contactTable->SetColLabelValue(1, "Nazwisko");
	contactTable->SetColLabelValue(2, "NumerTel");
	contactTable->SetColLabelValue(3, "Adres");
	contactTable->SetColLabelValue(4, "KodPocz");
	contactTable->SetColLabelValue(5, "Email");
	contactTable->SetColLabelValue(6, "Opis");
	long num_cols = contactTable->GetNumberCols();
	long width = contactTable->GetRowLabelSize();
	for (int col = 0; col < num_cols - 1; col++)
	{
		wxGridCellAttr *attrRO = new wxGridCellAttr;
		attrRO->SetReadOnly();
		contactTable->SetColSize(col, 900 / (num_cols - 1));
		width += contactTable->GetColSize(col);
		contactTable->SetColAttr(col, attrRO);
	}

	if (num_cols > 0)
	{
		wxGridCellAttr *attrRO = new wxGridCellAttr;
		attrRO->SetReadOnly();
		width = 1480 - width - 1;
		contactTable->SetColSize(num_cols - 1, width);
		contactTable->SetColAttr(num_cols - 1, attrRO);
	};
	contactTable->SetCellHighlightPenWidth(0);
	contactTable->SetCellHighlightROPenWidth(0);

	contactSearchTable = new wxGrid(panel, wxID_ANY, wxPoint(10, 50), wxSize(1480, 350));
	contactSearchTable->CreateGrid(0, 7);
	contactSearchTable->DisableCellEditControl();
	contactSearchTable->SetRowLabelSize(20);
	contactSearchTable->SetColLabelValue(0, "Imie");
	contactSearchTable->SetColLabelValue(1, "Nazwisko");
	contactSearchTable->SetColLabelValue(2, "NumerTel");
	contactSearchTable->SetColLabelValue(3, "Adres");
	contactSearchTable->SetColLabelValue(4, "KodPocz");
	contactSearchTable->SetColLabelValue(5, "Email");
	contactSearchTable->SetColLabelValue(6, "Opis");
	long search_num_cols = contactSearchTable->GetNumberCols();
	long search_width = contactSearchTable->GetRowLabelSize();
	for (int col = 0; col < search_num_cols - 1; col++)
	{
		wxGridCellAttr* attrRO = new wxGridCellAttr;
		attrRO->SetReadOnly();
		contactSearchTable->SetColSize(col, 900 / (search_num_cols - 1));
		search_width += contactSearchTable->GetColSize(col);
		contactSearchTable->SetColAttr(col, attrRO);
	}

	if (search_num_cols > 0)
	{
		wxGridCellAttr* attrRO = new wxGridCellAttr;
		attrRO->SetReadOnly();
		search_width = 1480 - search_width - 1;
		contactSearchTable->SetColSize(search_num_cols - 1, search_width);
		contactSearchTable->SetColAttr(search_num_cols - 1, attrRO);
	}
	contactSearchTable->SetCellHighlightPenWidth(0);
	contactSearchTable->SetCellHighlightROPenWidth(0);
	contactSearchTable->Hide();

	addAContact = new wxButton(panel, wxID_ANY, "Dodaj", wxPoint(30, 410), wxSize(60, 23));
	editAContact = new wxButton(panel, wxID_ANY, "Edytuj", wxPoint(95, 410), wxSize(60, 23));
	deleteAContact = new wxButton(panel, wxID_ANY, "Usun", wxPoint(160, 410), wxSize(60, 23));

	
	wxImage::AddHandler(new wxPNGHandler);
	wxImage image;
	wxString filePath = wxFileName::GetCwd() + wxFileName::GetPathSeparator() + "contact.png";
	if (image.LoadFile(filePath, wxBITMAP_TYPE_PNG)) {
		wxBitmap bitmap(image);
		if (!bitmap.IsOk()) {
			wxLogError("Nie uda³o siê utworzyæ bitmapy.");
		}
		wxStaticBitmap* staticBitmap = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(30, 470));
	}
	else {
		wxLogError("Nie uda³o siê wczytaæ pliku graficznego.");
		return;
	}

	filePath = wxFileName::GetCwd() + wxFileName::GetPathSeparator() + "telefon.png";
	if (image.LoadFile(filePath, wxBITMAP_TYPE_PNG)) {
		wxBitmap bitmap(image);
		if (!bitmap.IsOk()) {
			wxLogError("Nie uda³o siê utworzyæ bitmapy.");
		}
		wxStaticBitmap* staticBitmap = new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(30, 470));
	}
	else {
		wxLogError("Nie uda³o siê wczytaæ pliku graficznego.");
		return;
	}


	displayedRow = -1;
	prevContact = new wxButton(panel, wxID_ANY, "<", wxPoint(300, 410), wxSize(23, 23));
	id = new wxTextCtrl(panel, wxID_ANY, std::to_string(displayedRow+1), wxPoint(325,411), wxSize(23,21), wxTE_PROCESS_ENTER);
	nextContact = new wxButton(panel, wxID_ANY, ">", wxPoint(350, 410), wxSize(23,23));

	imie = new wxStaticText(panel, wxID_ANY, "Imie: ", wxPoint(300, 460), wxSize(100, 20) , wxALIGN_RIGHT);
	nazwisko = new wxStaticText(panel, wxID_ANY, "Nazwisko: ", wxPoint(300, 490), wxSize(100, 20), wxALIGN_RIGHT);
	numerTel = new wxStaticText(panel, wxID_ANY, "Numer Telefonu: ", wxPoint(300, 520), wxSize(100, 20), wxALIGN_RIGHT);
	adres = new wxStaticText(panel, wxID_ANY, "Adres: ", wxPoint(300, 550), wxSize(100, 20), wxALIGN_RIGHT);
	kodPocz = new wxStaticText(panel, wxID_ANY, "Kod Pocztowy: ", wxPoint(300, 580), wxSize(100, 20), wxALIGN_RIGHT);
	email = new wxStaticText(panel, wxID_ANY, "Email: ", wxPoint(300, 610), wxSize(100, 20), wxALIGN_RIGHT);
	opis = new wxStaticText(panel, wxID_ANY, "Opis: ", wxPoint(650, 460), wxSize(100, 20), wxALIGN_LEFT);

	contactImie = new wxStaticText(panel, wxID_ANY, "", wxPoint(410, 460), wxSize(100, 20), wxALIGN_LEFT);
	contactNazwisko = new wxStaticText(panel, wxID_ANY, "", wxPoint(410, 490), wxSize(100, 20), wxALIGN_LEFT);
	contactNumerTel = new wxStaticText(panel, wxID_ANY, "", wxPoint(410, 520), wxSize(100, 20), wxALIGN_LEFT);
	contactAdres = new wxStaticText(panel, wxID_ANY, "", wxPoint(410, 550), wxSize(100, 20), wxALIGN_LEFT);
	contactKodPocz = new wxStaticText(panel, wxID_ANY, "", wxPoint(410, 580), wxSize(100, 20), wxALIGN_LEFT);
	contactEmail = new wxStaticText(panel, wxID_ANY, "", wxPoint(410, 610), wxSize(150, 20), wxALIGN_LEFT);
	contactOpis = new wxStaticText(panel, wxID_ANY, "", wxPoint(700, 460), wxSize(400, 180));
	
}

void MainFrame::BindEventHandlers()
{
	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnWindowClosed, this);

	contactTable->Bind(wxEVT_GRID_CELL_LEFT_CLICK, &MainFrame::RowSelection, this);
	contactSearchTable->Bind(wxEVT_GRID_CELL_LEFT_CLICK, &MainFrame::RowSelection, this);

	Szukaj->Bind(wxEVT_BUTTON, &MainFrame::SearchContacts, this);
	inputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::SearchContacts, this);
	prevSearchButton->Bind(wxEVT_BUTTON, &MainFrame::prevSearchContacts, this);
	nextSearchButton->Bind(wxEVT_BUTTON, &MainFrame::nextSearchContacts, this);
	resetSearchButton->Bind(wxEVT_BUTTON, &MainFrame::resetSearchContacts, this);

	addAContact->Bind(wxEVT_BUTTON, &MainFrame::AddContactFromButton, this);
	deleteAContact->Bind(wxEVT_BUTTON, &MainFrame::DeleteContactFromButton, this);
	editAContact->Bind(wxEVT_BUTTON, &MainFrame::EditContactFromButton, this);

	prevContact->Bind(wxEVT_BUTTON, &MainFrame::PrevContact, this);
	id->Bind(wxEVT_TEXT_ENTER, &MainFrame::ChooseContact, this);
	nextContact->Bind(wxEVT_BUTTON, &MainFrame::NextContact, this);
}

void MainFrame::SearchContacts(wxCommandEvent& evt)
{
	if (inputField->GetValue().Strip() == "")
	{
		wxMessageDialog dialog(this, "Szukana wartosc nie moze byc pusta", "Zla wartosc", wxOK);
		int result = dialog.ShowModal();
	}
	else {
		wxString value;
		vectorIndex = 0;
		foundRowIndexes.clear();
		for (int row = 0; row < contactTable->GetNumberRows(); row++)
		{
			value = contactTable->GetCellValue(row, choice->GetSelection());
			if (PatternInCell(inputField->GetValue().Strip().Lower(), value.Lower())) foundRowIndexes.push_back(row);
		}
		if (foundRowIndexes.size() == 0)
		{
			wxMessageDialog dialog(this, "Nie znaleziono kontaktow o podanych parametrach", "Nie znaleziono", wxOK);
			int result = dialog.ShowModal();
			foundCount->SetLabel("0 - znalezionych kontaktow");
		}else
		{
			contactTable->Hide();
			contactSearchTable->ClearGrid();
			if(contactSearchTable->GetNumberRows() > 0) contactSearchTable->DeleteRows(0, contactSearchTable->GetNumberRows());
			contactSearchTable->Show();
			isSearchGridVisible = true;

			for (unsigned int i = 0; i < foundRowIndexes.size(); i++)
			{
				int gridSize = contactSearchTable->GetNumberRows();
				contactSearchTable->AppendRows(1);
				contactSearchTable->SetCellValue(gridSize, 0, contactTable->GetCellValue(foundRowIndexes[i], 0));
				contactSearchTable->SetCellValue(gridSize, 1, contactTable->GetCellValue(foundRowIndexes[i], 1));
				contactSearchTable->SetCellValue(gridSize, 2, contactTable->GetCellValue(foundRowIndexes[i], 2));
				contactSearchTable->SetCellValue(gridSize, 3, contactTable->GetCellValue(foundRowIndexes[i], 3));
				contactSearchTable->SetCellValue(gridSize, 4, contactTable->GetCellValue(foundRowIndexes[i], 4));
				contactSearchTable->SetCellValue(gridSize, 5, contactTable->GetCellValue(foundRowIndexes[i], 5));
				contactSearchTable->SetCellValue(gridSize, 6, contactTable->GetCellValue(foundRowIndexes[i], 6));
			}

			foundCount->SetLabel(std::to_string(foundRowIndexes.size()) + " - znalezionych kontaktow");
		}
	}
}

bool MainFrame::PatternInCell(wxString pattern, wxString text)
{
	int dlt = text.size();
	int dlw = pattern.size();
	int i = 0;
	while (i <= dlt - dlw)
	{
		int j = 0;
		while (j < dlw && pattern[j] == text[i + j])
		{
			j = j + 1;
		}
		if (j == dlw)
		{
			return true;
		}
		i++;
	}
	return false;
}

void MainFrame::nextSearchContacts(wxCommandEvent& evt)
{
	if (foundRowIndexes.size() > 0)
	{
		vectorIndex++;
		if (vectorIndex > foundRowIndexes.size() - 1) vectorIndex = 0;

		displayedRow = foundRowIndexes[vectorIndex];

		SetLabels();
	}
	else {
		wxMessageDialog dialog(this, "Nie znaleziono kontaktow o podanych parametrach", "Nie znaleziono", wxOK);
		int result = dialog.ShowModal();
	}
}

void MainFrame::prevSearchContacts(wxCommandEvent& evt)
{
	if (foundRowIndexes.size() > 0)
	{
		vectorIndex--;
		if (vectorIndex < 0) vectorIndex = foundRowIndexes.size() - 1;

		displayedRow = foundRowIndexes[vectorIndex];

		SetLabels();
	}
	else {
		wxMessageDialog dialog(this, "Nie znaleziono kontaktow o podanych parametrach", "Nie znaleziono", wxOK);
		int result = dialog.ShowModal();
	}
}

void MainFrame::resetSearchContacts(wxCommandEvent& evt)
{
	contactSearchTable->ClearGrid();
	if(contactSearchTable->GetNumberRows() > 0)contactSearchTable->DeleteRows(0, contactSearchTable->GetNumberRows());
	contactSearchTable->Hide();
	isSearchGridVisible = false;
	contactTable->Show();
}

void MainFrame::RowSelection(wxGridEvent& evt)
{
	try {
		if (!isSearchGridVisible)
		{
			contactTable->SelectRow(evt.GetRow());
		}
		else {
			contactSearchTable->SelectRow(evt.GetRow());
		}
	}
	catch (...)
	{
		
	}
}

void MainFrame::AddContactFromButton(wxCommandEvent &evt)
{
	form = new ContactForm("Dodaj kontakt", Add);
	this->Enable(false);
}

void MainFrame::NextContact(wxCommandEvent& evt)
{
	displayedRow++;
	if (displayedRow + 1 > contactTable->GetNumberRows()) displayedRow = 0;

	SetLabels();

}

void MainFrame::ChooseContact(wxCommandEvent& evt)
{
	int row = wxAtoi(id->GetValue()) - 1;
	if (row > 0 && row < contactTable->GetNumberRows())
	{
		displayedRow = wxAtoi(id->GetValue()) - 1;
		SetLabels();
	}
	else
	{
		wxMessageDialog dialog(this, "Numer kontaktu poza zakresem", "Zla wartosc", wxOK);
		int result = dialog.ShowModal();
	}
}

void MainFrame::PrevContact(wxCommandEvent& evt)
{
	displayedRow--;
	if (displayedRow < 0) displayedRow = contactTable->GetNumberRows() - 1;

	SetLabels();
}

void MainFrame::SetLabels()
{
	contactImie->SetLabel(contactTable->GetCellValue(displayedRow, 0));
	contactNazwisko->SetLabel(contactTable->GetCellValue(displayedRow, 1));
	contactNumerTel->SetLabel(contactTable->GetCellValue(displayedRow, 2));
	contactAdres->SetLabel(contactTable->GetCellValue(displayedRow, 3));
	contactKodPocz->SetLabel(contactTable->GetCellValue(displayedRow, 4));
	contactEmail->SetLabel(contactTable->GetCellValue(displayedRow, 5));
	contactOpis->SetLabel(contactTable->GetCellValue(displayedRow, 6));

	contactOpis->Wrap(400);

	id->SetLabel(std::to_string(displayedRow + 1));
}

void MainFrame::DeleteContactFromButton(wxCommandEvent &evt)
{
	if (isSearchGridVisible)
	{
		wxArrayInt SelectedRow = contactSearchTable->GetSelectedRows();
		if (SelectedRow != NULL)
		{
			wxMessageDialog dialog(this, "Na pewno chcesz usunac zaznaczone kontakty?", "Usuwanie kontaktow", wxYES_NO | wxCANCEL);
			int result = dialog.ShowModal();
			if (result == wxID_YES)
			{
				int x = SelectedRow.Count() - 1;
				wxLogStatus("Ilosc usunietych kontaktow: %d", x + 1);
				contactTable->ClearSelection();
				contactSearchTable->ClearSelection();
				for (x; x >= 0; x--)
				{
					contactSearchTable->DeleteRows(SelectedRow.Item(x));
					contactTable->DeleteRows(foundRowIndexes[SelectedRow.Item(x)]);
					if (foundRowIndexes[SelectedRow.Item(x)] <= displayedRow) displayedRow--;
				}
			}
		}
	}
	else {
		wxArrayInt SelectedRow = contactTable->GetSelectedRows();
		if (SelectedRow != NULL)
		{
			wxMessageDialog dialog(this, "Na pewno chcesz usunac zaznaczone kontakty?", "Usuwanie kontaktow", wxYES_NO | wxCANCEL);
			int result = dialog.ShowModal();
			if (result == wxID_YES)
			{
				int x = SelectedRow.Count() - 1;
				wxLogStatus("Ilosc usunietych kontaktow: %d", x + 1);
				contactTable->ClearSelection();
				contactSearchTable->ClearSelection();
				for (x; x >= 0; x--)
				{
					contactTable->DeleteRows(SelectedRow.Item(x));
					if (SelectedRow.Item(x) <= displayedRow) displayedRow--;
				}
			}
		}
	}
}

void MainFrame::EditContactFromButton(wxCommandEvent &evt)
{
	if (isSearchGridVisible)
	{
		wxArrayInt SelectedRow = contactSearchTable->GetSelectedRows();
		if (SelectedRow != NULL)
		{
			int x = SelectedRow.Count() - 1;
			if (x + 1 == 1)
			{
				wxMessageDialog dialog(this, "Na pewno chcesz edytowac zaznaczony kontakt?", "Edytowanie kontaktow", wxYES_NO | wxCANCEL);
				int result = dialog.ShowModal();
				if (result == wxID_YES)
				{
					form = new ContactForm("Edytuj kontakt - " + contactSearchTable->GetCellValue(SelectedRow.Item(x), 0) + " "
						+ contactSearchTable->GetCellValue(SelectedRow.Item(x), 1), Edit, SelectedRow.Item(x));
					this->Enable(false);
				}
			}
			else
			{
				wxMessageDialog dialog(this, "Zaznacz jeden kontakt do edytowania", "Zbyt wiele zaznaczonych kontaktow", wxOK);
				int result = dialog.ShowModal();
			}
		}
	}
	else {
		wxArrayInt SelectedRow = contactTable->GetSelectedRows();
		if (SelectedRow != NULL)
		{
			int x = SelectedRow.Count() - 1;
			if (x + 1 == 1)
			{
				wxMessageDialog dialog(this, "Na pewno chcesz edytowac zaznaczony kontakt?", "Edytowanie kontaktow", wxYES_NO | wxCANCEL);
				int result = dialog.ShowModal();
				if (result == wxID_YES)
				{
					form = new ContactForm("Edytuj kontakt - " + contactTable->GetCellValue(SelectedRow.Item(x), 0) + " "
						+ contactTable->GetCellValue(SelectedRow.Item(x), 1), Edit, SelectedRow.Item(x));
					this->Enable(false);
				}
			}
			else
			{
				wxMessageDialog dialog(this, "Zaznacz jeden kontakt do edytowania", "Zbyt wiele zaznaczonych kontaktow", wxOK);
				int result = dialog.ShowModal();
			}
		}
	}
}

void MainFrame::AddToGrid()
{
	int gridSize = contactTable->GetNumberRows();
	contactTable->AppendRows(1);
	contactTable->SetCellValue(gridSize, 0, form->imiegrid);
	contactTable->SetCellValue(gridSize, 1, form->nazwiskogrid);
	contactTable->SetCellValue(gridSize, 2, form->numerTelgrid);
	contactTable->SetCellValue(gridSize, 3, form->adresgrid);
	contactTable->SetCellValue(gridSize, 4, form->kodPoczgrid);
	contactTable->SetCellValue(gridSize, 5, form->emailgrid);
	contactTable->SetCellValue(gridSize, 6, form->opisgrid);
	wxLogStatus("Dodano kontakt: %s %s", form->imiegrid, form->nazwiskogrid);

	if (isSearchGridVisible)
	{
		gridSize = contactSearchTable->GetNumberRows();
		contactSearchTable->AppendRows(1);
		contactSearchTable->SetCellValue(gridSize, 0, form->imiegrid);
		contactSearchTable->SetCellValue(gridSize, 1, form->nazwiskogrid);
		contactSearchTable->SetCellValue(gridSize, 2, form->numerTelgrid);
		contactSearchTable->SetCellValue(gridSize, 3, form->adresgrid);
		contactSearchTable->SetCellValue(gridSize, 4, form->kodPoczgrid);
		contactSearchTable->SetCellValue(gridSize, 5, form->emailgrid);
		contactSearchTable->SetCellValue(gridSize, 6, form->opisgrid);
	}
}

void MainFrame::UpdateGrid(int Row)
{
	if (isSearchGridVisible)
	{
		contactSearchTable->SetCellValue(Row, 0, form->imiegrid);
		contactSearchTable->SetCellValue(Row, 1, form->nazwiskogrid);
		contactSearchTable->SetCellValue(Row, 2, form->numerTelgrid);
		contactSearchTable->SetCellValue(Row, 3, form->adresgrid);
		contactSearchTable->SetCellValue(Row, 4, form->kodPoczgrid);
		contactSearchTable->SetCellValue(Row, 5, form->emailgrid);
		contactSearchTable->SetCellValue(Row, 6, form->opisgrid);

		contactTable->SetCellValue(foundRowIndexes[Row], 0, form->imiegrid);
		contactTable->SetCellValue(foundRowIndexes[Row], 1, form->nazwiskogrid);
		contactTable->SetCellValue(foundRowIndexes[Row], 2, form->numerTelgrid);
		contactTable->SetCellValue(foundRowIndexes[Row], 3, form->adresgrid);
		contactTable->SetCellValue(foundRowIndexes[Row], 4, form->kodPoczgrid);
		contactTable->SetCellValue(foundRowIndexes[Row], 5, form->emailgrid);
		contactTable->SetCellValue(foundRowIndexes[Row], 6, form->opisgrid);
	}
	else {
		contactTable->SetCellValue(Row, 0, form->imiegrid);
		contactTable->SetCellValue(Row, 1, form->nazwiskogrid);
		contactTable->SetCellValue(Row, 2, form->numerTelgrid);
		contactTable->SetCellValue(Row, 3, form->adresgrid);
		contactTable->SetCellValue(Row, 4, form->kodPoczgrid);
		contactTable->SetCellValue(Row, 5, form->emailgrid);
		contactTable->SetCellValue(Row, 6, form->opisgrid);
		wxLogStatus("Edytowano kontakt");
	}
}

void MainFrame::AddSavedContacts()
{
	std::vector<Contact> contacts = loadContactsFromFile("contacts.csv");
	for (unsigned int i = 0; i < contacts.size(); i++)
	{
		contactTable->AppendRows(1);
		contactTable->SetCellValue(i, 0, wxString::Format("%s", contacts[i].imie));
		contactTable->SetCellValue(i, 1, wxString::Format("%s", contacts[i].nazwisko));
		contactTable->SetCellValue(i, 2, wxString::Format("%s", contacts[i].numerTelefonu));
		contactTable->SetCellValue(i, 3, wxString::Format("%s", contacts[i].adres));
		contactTable->SetCellValue(i, 4, wxString::Format("%s", contacts[i].kodPocz));
		contactTable->SetCellValue(i, 5, wxString::Format("%s", contacts[i].email));
		contactTable->SetCellValue(i, 6, wxString::Format("%s", contacts[i].opis));
	}
}

void MainFrame::OnWindowClosed(wxCloseEvent &evt)
{
	std::vector<Contact> contacts;
	for (int i = 0; i < contactTable->GetNumberRows(); i++)
	{
		Contact contact;
		contact.imie = contactTable->GetCellValue(i, 0);
		contact.nazwisko = contactTable->GetCellValue(i, 1);
		contact.numerTelefonu = contactTable->GetCellValue(i, 2);
		contact.adres = contactTable->GetCellValue(i, 3);
		contact.kodPocz = contactTable->GetCellValue(i, 4);
		contact.email = contactTable->GetCellValue(i, 5);
		contact.opis = contactTable->GetCellValue(i, 6);
		contacts.push_back(contact);
	}
	SaveContactsToFile(contacts, "contacts.csv");
	delete form;
	evt.Skip();
}