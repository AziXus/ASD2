/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Util.h"

bool stringToLower(std::string& str){
    for(char &c : str){
        if(isdigit(c)){
            return false;
        }
        c = tolower(c);
    }
    return true;
}