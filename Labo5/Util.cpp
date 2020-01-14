/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Util.h"

bool stringToLower(std::string& element2){
    for(char &c : element2){
        if(isdigit(c)){
            return false;
        }
        c = tolower(c);
    }
    return true;
}