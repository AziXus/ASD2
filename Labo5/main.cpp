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
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <chrono>
#include <list>
#include <unordered_set>

using namespace std;

std::unordered_set<string> set;

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

void lectureDonnees(string filename){
        std::string line;
        char delim[] = {' ', '-'};
        size_t size = 3;
        std::ifstream s(filename);
        while (std::getline(s, line)) {
            std::vector<string> elements = split(line, ' ');
            for(string element : elements){
                std::vector<string> elements2 = split(element, '-');
                for(string element2 : elements2){
                    for(char &c : element2){
                        if(c != '\'' && !isalpha(c)){
                            if(isdigit(c)){
                                continue;
                            }
                            c = ' ';
                        }
                        c = tolower(c);
                    }
                    set.insert(element2);
                }
            }
        }
        s.close();
}

void lectureDictio(string filename){
        std::string line;
        
        std::ifstream s(filename);
        while (std::getline(s, line)) {
            for(char &c : line){
                c = tolower(c);
            }
            set.insert(line);
        }
        s.close();
}

int main(int argc, char** argv) {
    //lectureDictio("dictionary.txt");
    
    lectureDonnees("input_simple.txt");
    
    for(string s : set){
        cout << s << endl;
    }

    return 0;
}

