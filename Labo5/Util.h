/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Util.h
 * Author: stéphane
 *
 * Created on January 14, 2020, 1:19 PM
 */

#ifndef UTIL_H
#define UTIL_H

bool stringToLower(string& element2){
    for(char &c : element2){
        if(isdigit(c)){
            return false;
        }
        c = tolower(c);
    }
    return true;
}

#endif /* UTIL_H */

