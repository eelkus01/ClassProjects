/*
 * DatumStack.h
 * CS 15 Project 2: CalcYouLater
 * Eleanor Elkus (eelkus01)
 * Date Created: 2/25/23
 *
 * Purpose: Interface of the DatumStack class. Elements can be added and
 *          removed from the top of a stack.
 *
 */

#ifndef DATUMSTACK_H_
#define DATUMSTACK_H_

#include "Datum.h"
#include <list>

class DatumStack {
public:
    //constructors
    DatumStack();
    DatumStack(Datum arr[], int size);

    //destructor
    ~DatumStack();

    //other functions to implement
    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(Datum elem);

private:
    //put all other functions and variables here
    std::list<Datum> stack;
    std::string print();

};

#endif