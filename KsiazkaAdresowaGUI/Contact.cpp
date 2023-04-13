#include "Contact.h"
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>

void SaveContactsToFile(const std::vector<Contact> &contacts, const std::string &fileName)
{
    std::ofstream ostream(fileName);
    ostream << contacts.size();

    for (const Contact &contact : contacts)
    {
        std::string imie = contact.imie;
        std::string nazwisko = contact.nazwisko;
        std::string numerTelefonu = contact.numerTelefonu;
        std::string adres = contact.adres;
        std::string kodPocz = contact.kodPocz;
        std::string email = contact.email;
        std::string opis = contact.opis;
        std::replace(imie.begin(), imie.end(), ' ', '_');
        std::replace(nazwisko.begin(), nazwisko.end(), ' ', '_');
        std::replace(numerTelefonu.begin(), numerTelefonu.end(), ' ', '_');
        std::replace(adres.begin(), adres.end(), ' ', '_');
        std::replace(kodPocz.begin(), kodPocz.end(), ' ', '_');
        std::replace(email.begin(), email.end(), ' ', '_');
        std::replace(opis.begin(), opis.end(), ' ', '_');

        ostream << '\n'
                << imie << ' ' << nazwisko << ' ' << numerTelefonu << ' ' << adres << ' ' << kodPocz << ' ' << email << ' ' << opis;
    }
    ostream.close();
}

std::vector<Contact> loadContactsFromFile(const std::string &fileName)
{
    if (!std::filesystem::exists(fileName))
    {
        return std::vector<Contact>();
    }

    std::vector<Contact> contacts;
    std::ifstream istream(fileName);

    int n;
    istream >> n;

    for (int i = 0; i < n; i++)
    {
        std::string imie;
        std::string nazwisko;
        std::string numerTelefonu;
        std::string adres;
        std::string kodPocz;
        std::string email;
        std::string opis;

        istream >> imie >> nazwisko >> numerTelefonu >> adres >> kodPocz >> email >> opis;
        std::replace(imie.begin(), imie.end(), '_', ' ');
        std::replace(nazwisko.begin(), nazwisko.end(), '_', ' ');
        std::replace(numerTelefonu.begin(), numerTelefonu.end(), '_', ' ');
        std::replace(adres.begin(), adres.end(), '_', ' ');
        std::replace(kodPocz.begin(), kodPocz.end(), '_', ' ');
        std::replace(email.begin(), email.end(), '_', ' ');
        std::replace(opis.begin(), opis.end(), '_', ' ');
        contacts.push_back(Contact{imie, nazwisko, numerTelefonu, adres, kodPocz, email, opis});
    }
    istream.close();
    return contacts;
}
