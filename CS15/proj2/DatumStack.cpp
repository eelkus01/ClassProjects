/*
 * DatumStack.cpp
 * CS 15 Project 2: CalcYouLater
 * Eleanor Elkus (eelkus01)
 * Date Created: 2/25/23
 *
 * Purpose: Implement a version of the DatumStack class; implementing from the
 *          DatumStack.h header file. Datum elements can be added or removed
 *          from the top of a stack.
 *
 */

#include "DatumStack.h"
#include <stdexcept>
#include <string>
#include <sstream>

using namespace std;

/* 
 * name:        default constructor
 * purpose:     initialize an empty DatumStack
 * arguments:   none
 * returns:     none
 * effects:     empty stack is initialized; because using std::list, nothing
 *              needs to actually be done here
 */
DatumStack::DatumStack() {
}

/*
 * name:        array constructor
 * purpose:     create a stack initialized with the elements of the array
 * arguments:   an array of Datum elements and the size of the array
 * returns:     none
 * effects:     the stack is created with the given elements
 */
DatumStack::DatumStack(Datum arr[], int size) {
    for (int i = 0; i < size; i++) {
        stack.push_front(arr[i]);
    }
}

/* 
 * name:        destructor
 * purpose:     free any heap allocated memory created by the DatumStack class
 * arguments:   none
 * returns:     none
 * effects:     frees/recycles heap allocated memory
 */
DatumStack::~DatumStack() {
}

/* 
 * name:        size
 * purpose:     return the number of Datum elements on the stack
 * arguments:   none
 * returns:     the number of Datum elements on the stack
 * effects:     none
 */
int DatumStack::size() {
    return stack.size();
}

/* 
 * name:        isEmpty
 * purpose:     determine if a DatumStack is empty or not
 * arguments:   none
 * returns:     true if the stack is empty and false otherwise
 * effects:     none
 */
bool DatumStack::isEmpty() {
    return (stack.size() == 0);
}

/* 
 * name:        push
 * purpose:     put given Datum element on top of the stack
 * arguments:   the Datum element to add to the top of the stack
 * returns:     none
 * effects:     adds the element to the top of the stack (size should increase)
 */
void DatumStack::push(Datum elem) {
    stack.push_front(elem);
}

/* 
 * name:        print
 * purpose:     print the DatumStack for testing purposes
 * arguments:   none
 * returns:     none
 * effects:     none
 */
std::string DatumStack::print() {
    //using stringstream and iterator
    std::stringstream ss;
    for (auto const &v : stack) {
        ss << v.toString();
    }
    return ss.str();
}

/* 
 * name:        clear
 * purpose:     make the current stack empty
 * arguments:   none
 * returns:     none
 * effects:     the current stack is made empty
 */
void DatumStack::clear() {
    while (not isEmpty()) {
        pop();
    }
}

/* 
 * name:        top
 * purpose:     return the top element on the stack; throw error if called on
 *              empty stack
 * arguments:   none
 * returns:     the top element
 * effects:     none
 */
Datum DatumStack::top() {
    if (isEmpty()) {
        throw runtime_error("empty_stack");
    }
    return stack.front();
}

/* 
 * name:        pop
 * purpose:     remove the top element on the stack; throw an error if called
 *              on an empty stack
 * arguments:   none
 * returns:     none
 * effects:     the top element on the stack is removed
 */
void DatumStack::pop() {
    if (isEmpty()) {
        throw runtime_error("empty_stack");
    }
    stack.pop_front();
}
