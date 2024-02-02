/*
 * PassengerQueue.cpp
 * CS 15 Project 1: Metro Simulation
 * Eleanor Elkus (eelkus01)
 * Date Created: 2/10/23
 *
 * Purpose: Implement a version of the PassengerQueue class; implementing from
 *          the PassengerQueue.h header file. Passengers can be added or
 *          removed from the queue and the queue can be printed to the given
 *          output stream.
 *
 */
#include "PassengerQueue.h"
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;

/*
 * name:        front
 * purpose:     return the passenger at the front of the queue
 * arguments:   none
 * returns:     the passenger at the front of the queue
 * effects:     none
 */
Passenger PassengerQueue::front() {
    return queue.front();
}

/*
 * name:        dequeue
 * purpose:     remove the passenger at the front of the queue
 * arguments:   none
 * returns:     none
 * effects:     removes the first passenger
 */
void PassengerQueue::dequeue() {
    queue.erase(queue.begin());
}

/*
 * name:        enqueue
 * purpose:     insert the new passenger at the end of the queue
 * arguments:   the address of the new passenger to add
 * returns:     none
 * effects:     adds the new passenger to the end of the queue
 */
void PassengerQueue::enqueue(const Passenger &passenger) {
    queue.push_back(passenger);
}

/*
 * name:        size
 * purpose:     return the number of elements in the queue
 * arguments:   none
 * returns:     the number of elements in the queue
 * effects:     none
 */
int PassengerQueue::size() {
    return queue.size();
}

/*
 * name:        print
 * purpose:     print each passenger in the queue to the output stream from
 *              front to back
 * arguments:   the output stream to print to
 * returns:     none
 * effects:     none
 */
void PassengerQueue::print(std::ostream &output) {
    int size = queue.size();
    for (int i = 0; i < size; i++) {
        queue.at(i).print(output);
    }
}
