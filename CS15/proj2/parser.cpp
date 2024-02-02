/*
 * parser.cpp
 * CS 15 Project 2: CalcYouLater
 * Eleanor Elkus (eelkus01)
 * Date Created: 2/27/23
 *
 * Purpose: Contains the definition of the parseRString function which
 *          creates an rstring from the info in the provided input stream.
 *
 */

#include "parser.h"
#include "Datum.h"

/*
 * name:        parseRString
 * purpose:     read input from the given stream and create an rstring from the
 *              stream's info
 * arguments:   the input stream to read from
 * returns:     an rstring of what was in the stream (within braces)
 * effects:     none
 */
std::string parseRString(std::istream &input) {
    //make the rstring and include the first opening brace
    std::string str = "{";

    //counters to keep track of brace count
    int backCount = 0;
    int frontCount = 1;

    //read in from stream and add to rstring until end of stream
    std::string toAdd;
    input >> toAdd;
    while (not input.fail() and frontCount != backCount) {
        if (toAdd == "}") backCount++;
        if (toAdd == "{") frontCount++;
        str = str + " " + toAdd;
        input >> toAdd;
    }

    //check for valid brace configuration
    if (backCount == 0) {
        throw std::runtime_error("invalid_input");
    }

    return str;
}