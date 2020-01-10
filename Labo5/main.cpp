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
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <chrono>
#include <list>
#include <unordered_set>

using namespace std;

std::unordered_set<string> set;

void lectureDonnees(string filename){
        std::string line;
        
        std::ifstream s(filename);
        while (std::getline(s, line)) {
            for(char c : line){
                if(c != '\'' && !isalpha(c)){
                    c = ' ';
                }
                c = tolower(c);
            }
            set.insert(line);
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
    lectureDictio("dictionary.txt");
    
    for(string s : set){
        cout << s << endl;
    }

    return 0;
}

