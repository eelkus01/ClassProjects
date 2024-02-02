/*
 * Passenger.cpp
 * CS 15 Project 1: Metro Simulation
 * Eleanor Elkus (eelkus01)
 * Date Created: 2/10/23
 *
 * Purpose: Implement a version of the Passenger class. Passengers are printed
 *          to the given output stream.
 *
 */

#include <iostream>
#include <string>
#include "Passenger.h"

/*
 * name:        print
 * purpose:     print the Passengers
 * arguments:   the address of the output stream to print the info to
 * returns:     none
 * effects:     none
 */
void Passenger::print(std::ostream &output)
{
        // TODO: print passenger information to the output stream
        //       as described in the assignment specification
        output << "[" << id << ", " << from << "->" << to << "]";
}
