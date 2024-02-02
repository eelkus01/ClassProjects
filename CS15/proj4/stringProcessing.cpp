/*
 * stringProcessing.cpp
 * CS 15 Project 4: gerp
 * Eleanor Elkus (eelkus01) and Talia Tepper (tteppe01)
 * Date Created: 4/13/23
 *
 * Purpose: Implementation of the function declared in stringProcessing.h,
 *          which strips all leading and trailing non alphanumeric characters
 *          from a string
 *
 */

#include "stringProcessing.h"
#include <ctype.h>
#include <iostream>

using namespace std;

/* name:        stripNonAlphaNum
 * purpose:     strip all leading and trailine non alphanumeric characters from
 *              the given string
 * arguments:   the string to strip
 * returns:     the stripped string
 * effects:     none
 */
std::string stripNonAlphaNum(std::string input) {
    //remove leading nonalphanum chars
    while (not isalnum(input.front()) and not input.empty()) {
        input.erase(0, 1);
    }

    //remove trailing nonalphanum chars
    while (not isalnum(input.back()) and not input.empty()) {
        input.pop_back();
    }

    return input;
}