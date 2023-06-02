#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <regex>
#include <sstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Funkcija, kuri nuskaito failo turinį ir jį įrašo į 'file_contents' eilutę
void read_file(string file_name, string &file_contents);

// Funkcija, kuri įrašo rezultatus į failą, naudojant 'file_name' pavadinimą, 'repeated_words' žemėlapį ir 'all_links' eilutę
void write_to_file(string &file_name, map<string, pair<int, vector<int>>> &repeated_words, string &all_links);

// Funkcija, kuri randa kartojamus žodžius faile ir juos įrašo į 'repeated_words' žemėlapį
std::map<std::string, std::pair<int, std::vector<int>>> find_repeated_words(const string &file_content);

// Funkcija, kuri randa visus URL adresus faile ir juos įrašo į 'all_links' eilutę
void find_all_links(string file_contents, string &all_links);

// Funkcija, kuri spausdina trumpąją rezultatų versiją, naudojant 'repeated_words' žemėlapį ir 'all_links' eilutę
void print_short_version(map<string, pair<int, vector<int>>> &repeated_words, string &all_links);

#endif
