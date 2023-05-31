#include "headers.h"


int main()
{
    string file_name, file_contents, all_links;

    cout << "Enter file name: ";
    cin >> file_name;

    read_file(file_name, file_contents);

    find_all_links(file_contents, all_links);
    std::map<std::string, std::pair<int, std::vector<int>>> repeated_words = find_repeated_words(file_contents);
    
    print_short_version(repeated_words, all_links);
    write_to_file(file_name, repeated_words, all_links);
}



/* //Alternatyva

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <utility>

void find_all_links(const std::string& file_contents, std::string& all_links) {
    // Implementation of find_all_links
}

std::unordered_map<std::string, std::pair<int, std::vector<int>>> find_repeated_words(const std::string& file_contents) {
    std::unordered_map<std::string, std::pair<int, std::vector<int>>> repeated_words;
    // Implementation of find_repeated_words
    return repeated_words;
}

void print_short_version(const std::unordered_map<std::string, std::pair<int, std::vector<int>>>& repeated_words,
                         const std::string& all_links) {
    // Implementation of print_short_version
}

void write_to_file(const std::string& file_name,
                   const std::unordered_map<std::string, std::pair<int, std::vector<int>>>& repeated_words,
                   const std::string& all_links) {
    // Implementation of write_to_file
}

int main() {
    std::string file_name, file_contents, all_links;

    std::cout << "Enter file name: ";
    std::cin >> file_name;

    std::ifstream input_file(file_name);
    if (input_file.is_open()) {
        // Read the file directly into the necessary variables or data structures
        std::string line;
        while (std::getline(input_file, line)) {
            file_contents += line;
        }

        input_file.close();

        std::unordered_map<std::string, std::pair<int, std::vector<int>>> repeated_words = find_repeated_words(file_contents);
        find_all_links(file_contents, all_links);

        print_short_version(repeated_words, all_links);

        write_to_file(file_name, repeated_words, all_links);
    } else {
        std::cerr << "Failed to open file." << std::endl;
    }

    return 0;
}
*/
