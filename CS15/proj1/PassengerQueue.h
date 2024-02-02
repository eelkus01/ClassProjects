/*
 * PassengerQueue.h
 * CS 15 Project 1: Metro Simulation
 * Eleanor Elkus (eelkus01)
 * Date Created: 2/10/23
 *
 * Purpose: Class definition for the PassengerQueue class. This class uses the
 *          C++ vector data structure. Passengers can be added and taken off of
 *          the queue and the queue can be printed to a given output stream.
 *
 */
#ifndef PASSENGER_QUEUE_H
#define PASSENGER_QUEUE_H

#include "Passenger.h"
#include <vector>

class PassengerQueue {
public:
    // functions to implement
    Passenger front();
    void dequeue();
    void enqueue(const Passenger &passenger);
    int size();
    void print(std::ostream &output);

private:
    std::vector<Passenger> queue;

};

#endif