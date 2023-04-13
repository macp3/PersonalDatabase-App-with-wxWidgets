#pragma once
#include "MainFrame.h"
#include <string>
#include <vector>
#include <filesystem>

class Contact
{
public:
	std::string imie;
	std::string nazwisko;
	std::string numerTelefonu;
	std::string adres;
	std::string kodPocz;
	std::string email;
	std::string opis;
};

void SaveContactsToFile(const std::vector<Contact> &contacts, const std::string &fileName);
std::vector<Contact> loadContactsFromFile(const std::string &fileName);
