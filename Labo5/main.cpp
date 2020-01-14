/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: stéphane
 *
 * Created on January 10, 2020, 1:57 PM
 */

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <chrono>
#include <list>
#include <unordered_set>

using namespace std;

std::list<string> donnees;

vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

vector<std::string> splitInterne(const std::string &s, char delim[], size_t size) {
    std::vector<std::string> elems;
    for(int i = 0; i < size; i++){
        split(s, delim[i], elems);
    }
    return elems;
}

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        if(ch == '\'')
            return false;
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        if(ch == '\'')
            return false;
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

void lectureDonnees(string filename){
        std::string line;
        // '—'
        char delims[] = {' ', '-', '[', ']'};
        size_t size = 3;
        bool hasNoDigit = false;
        std::ifstream s(filename);
        while (std::getline(s, line)) {
            std::vector<string> elements = split(line, ' ');
            for(string element : elements){
                trim(element);
                std::vector<string> elements2 = split(element, '-');
                for(string element2 : elements2){
                    hasNoDigit = stringToLower(element2);
                    element2.erase(std::remove_if(element2.begin(), element2.end() 
                    ,[] (char c) { 
                        return c != '\'' && !isalpha(c);
                    }), element2.end());
                    trim(element2);
                    if(element2 == "bb"){
                        cout << "Coucou " << element << endl;
                    }
                    if(hasNoDigit)
                        donnees.push_back(element2);
                    hasNoDigit = true;
                }
            }
        }
        s.close();
}

void lectureDictio(string filename){
        
}

int main(int argc, char** argv) {
    //lectureDictio("dictionary.txt");
    
    lectureDonnees("input_wikipedia.txt");
    
    for(string s : donnees){
        cout << s << endl;
    }

    return 0;
}

