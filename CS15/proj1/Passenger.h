/*
 * Passenger.h
 * CS 15 Project 1: Metro Simulation
 * Eleanor Elkus (eelkus01)
 * Date Created: 2/10/23
 *
 * Purpose: Class definition for the Passenger class. New passengers can be
 *          created with an ID, arrival station, and departure station. They
 *          can then be printed to a given output stream.
 *
 */


#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

struct Passenger
{

        int id, from, to;
        
        Passenger()
        {
                id   = -1;
                from = -1;
                to   = -1;
        }

        Passenger(int newId, int arrivalStation, int departureStation)
        {
                id   = newId;
                from = arrivalStation;
                to   = departureStation;
        }

        // TODO: implement the print function in Passenger.cpp
        void print(std::ostream &output);

};

#endif
