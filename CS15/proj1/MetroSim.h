/*
 * MetroSim.h
 * CS 15 Project 1: Metro Simulation
 * Eleanor Elkus (eelkus01)
 * Date Created: 2/10/23
 *
 * Purpose: Interface of the MetroSim class. Passengers can be added to a
 *          station, the train can be moved, and the game can be ended using
 *          the functions laid out below. Various C++ vector data structures
 *          are used.
 *
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include "PassengerQueue.h"
#include <iostream>
#include <fstream>
#include <string>

class MetroSim
{
public:

    void run(std::istream &input, std::ostream &output);
    void makeStations(std::istream &stationStream);
    
    //constructor
    MetroSim();

private:

    //station struct
    struct Station {
        PassengerQueue sq;
        std::string stationName;
        bool trainHere;
    };

    //helper functions and variables
    std::vector<PassengerQueue> onTrain;
    std::vector<Station> station;
    Station newStation(PassengerQueue sq, std::string stationName, 
                        bool trainHere);
    void print();
    void moveTrain(std::ostream &output);
    Station emptyStation(Station prev);
    void addPassenger(int arrive, int depart);
    int numStations;
    int passID;
    int trainIndex;
};

#endif
