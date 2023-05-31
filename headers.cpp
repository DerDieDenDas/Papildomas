#include "headers.h"

// Funkcija spausdinanti trumpąją rezultatų versiją
void print_short_version(map<string, pair<int, vector<int>>> &repeated_words, string &all_links)
{
    // Spausdinamas skirtingų kartojamų žodžių ir/arba nuorodų skaičius failo viduje
    cout << "Rasti skirtingi kartojami žodžiai ir/arba nuorodos failo viduje: " << repeated_words.size() << endl;
    
    // Spausdinamos nuorodos, rastos faile
    cout << "\nNuorodos rastos faile: " << endl;
    if (all_links.size() > 30) {
        // Jei nuorodų eilutės ilgis didesnis nei 30 simbolių, spausdinama tik pirmi 30 simboliai ir pridedamas "..."
        cout << all_links.substr(0, 30) << "..." << endl;
    } else {
        // Kitu atveju spausdinama visa nuorodų eilutė
        cout << all_links << endl;
    }
    
    // Spausdinamas pranešimas, kad išsamesnė informacija yra rezultatų faile
    cout << "\nPeržiūrėkite išsamesnę informaciją rezultatų faile." << endl;
}

// Funkcija, kuri pašalina specialiuosius simbolius iš teksto eilutės
string remove_special_characters(string file_content)
{
    // Eina per kiekvieną simbolį teksto eilutėje
    for (int i = 0; i < file_content.size(); i++)
    {
        // Tikrinama, ar simbolis yra specialusis simbolis
        if (ispunct(file_content[i]))
        {
            // Jei taip, jis pašalinamas iš eilutės
            file_content.erase(i--, 1);
        }
    }
    return file_content;
}

// Funkcija, kuri randa kartojamus žodžius faile ir jų eilučių numerius
map<string, pair<int, vector<int>>> find_repeated_words(const string &file_content)
{
    // Pašalinami specialieji simboliai iš teksto eilutės
    string text = remove_special_characters(file_content);

    // Sukuriamas žodžių skaičiaus ir eilučių numerių žemėlapis
    map<string, pair<int, vector<int>>> wordCount;

    // Naudodami stringstream daliname tekstą į žodžius
    stringstream ss(text);
    string word, line;

    int line_number = 0;
    // Eina per kiekvieną eilutę tekste
    while (getline(ss, line))
    {
        stringstream ss_line(line);

        // Eina per kiekvieną žodį eilutėje
        while (ss_line >> word)
        {
            // Pašalinami tarpai iš žodžio
            word.erase(remove_if(word.begin(), word.end(), ::isspace), word.end());
            
            // Padidinamas žodžio skaičius ir pridedamas eilutės numeris žemėlapio vektoriui
            wordCount[word].first++;
            wordCount[word].second.push_back(line_number);
        }
        line_number++;
    }
    
    // Pašalinami žodžiai su skaičiumi 1 iš žemėlapio
    for (auto it = wordCount.begin(); it != wordCount.end();)
    {
        if (it->second.first == 1)
            it = wordCount.erase(it);
        else
            ++it;
    }
    
    return wordCount;
}

// Funkcija, kuri randa URL adresus teksto eilutėje
void find_all_links(string file_contents, string &all_links)
{
    // Apibrėžiamas reguliaraus išraiškos šablonas, kuris atitinka URL adresus
    regex link_regex(R"((https?:\/\/)?(www\.)?([a-zA-Z0-9\-]+)(\.(com|org|net|gov|io|co|uk|us|ca|au|de|jp|ru|fr|it|nl|se|es|br|pl|in|cn|mx|za|ch|at|be|dk|no|fi|gr|hu|il|kr|pt|ro|tr|cz))([-\/\w@:%_\+.~#?&//=]*)?)");
    smatch matches;

    // Eina per teksto eilutę, ieškodamas atitikimų su reguliaraus išraiškos šablonu
    while (regex_search(file_contents, matches, link_regex))
    {
        // Jei nuorodos pabaigoje yra taškas, jis pašalinamas
        if (matches[0].str().back() == '.')
        {
            string temp = matches[0].str();
            temp.pop_back();
            all_links += temp;
        }
        else {
            // Pridedama nuoroda prie nuorodų eilutės
            all_links += matches[0];
        }
        all_links += "\n";
        
        // Atnaujinama teksto eilutė, kad būtų galima ieškoti toliau
        file_contents = matches.suffix().str();
    }
}

// Funkcija, kuri nuskaito failo turinį į eilutę
void read_file(string file_name, string &file_contents)
{
    ifstream in_file("source_files/" + file_name + ".txt");
    if (!in_file)
    {
        // Jei failo nepavyksta atidaryti, išspausdinamas klaidos pranešimas ir išeinama iš programos
        cerr << "Nepavyko atidaryti failo\n";
        system("pause");
        exit(0);
    }

    // Nuskaitomas failo turinys į eilutę
    file_contents = string(istreambuf_iterator<char>(in_file), istreambuf_iterator<char>());
    in_file.close();
    cout << "Failas sėkmingai nuskaitytas.\n";
}

// Funkcija, kuri rašo rezultatus į failą
void write_to_file(string &file_name, map<string, pair<int, vector<int>>> &repeated_words, string &all_links)
{
    // Atidaromas rezultatų failas rašymui
    ofstream out_file("result_files/" + file_name + "_results.txt");

    // Rašomos visos nuorodos į rezultatų failą
    out_file << "\nVisos nuorodos: " << endl;
    out_file << all_links << endl;

    // Rašomi kartojami žodžiai ir/arba nuorodos kryžminėje lentelėje į rezultatų failą
    out_file << "\nKartojami žodžiai ir/arba nuorodos kryžminėje lentelėje: " << endl;
    int counter = 0;

    // Eina per kiekvieną įrašą žemėlapyje repeated_words
    for (const auto &entry : repeated_words)
    {
        // Įrašomi žodis, skaičius ir eilutės numeriai į rezultatų failą
        out_file << fixed << setw(15) << entry.first << " : " << fixed << setw(4) << entry.second.first << " : ";
        for (const auto &element : entry.second.second)
        {
            out_file << element << " ";
        }
        out_file << endl;
    }

    // Uždaromas rezultatų failas
    out_file.close();
}
