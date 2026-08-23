#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <thread>
#include <chrono> 

std::string parseCSV(std::string filename) {
    std::ifstream input{filename};
    std::string words;
    
    if (!input.is_open()) {
        std::cerr << "Fichier csv illisible..." << "\n";
        return {{""}};
    }

    std::vector<std::vector<std::string>> csvRows;

    


    for (std::string line; std::getline(input, line);) {
        std::istringstream ss{line};

        std::vector<std::string> row;

        if (!csvRows.empty()) {
            row.reserve(csvRows.front().size());
        }

        for (std::string s ; std::getline(ss,s,',');) {
            row.push_back(std::move(s));
        }

        csvRows.push_back(std::move(row));
    }

    for (const std::vector<std::string>& val : csvRows) {
        for (const std::string word : val) {
            words+=word;
            words+=' ';
        }
    }

    

    return words;

}

int randomNumber() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(1, 100000);

    return dist(gen);
}

std::vector<std::string> split_string(std::string f) {
    std::vector<std::string> wordz;
    std::string u{""};
    for (char c : f) {
        if (c!=' ') {
            u+=c;
        } else {
            wordz.push_back(u);
            u = "";
        }
    }

    return wordz;
}

int main() {

    std::string filename{"words_list.csv"};
    std::string word_list = parseCSV(filename);
    std::vector<std::string> unique_word_list = split_string(word_list);

    int count = 0;
    while(count<301) {
        int x = randomNumber();

        std::cout << unique_word_list[x]<< " ";
        count++;
        std::this_thread::sleep_for(std::chrono::duration<double>(0.5));
    }

}