/*
 * unit_tests.h
 * CS 15 Project 1: Metro Simulation
 * Eleanor Elkus (eelkus01)
 * Date Created: 2/10/23
 *
 * Purpose: a file containing all of the tests used to check the functionality
 *          and correctness of the Passenger, PassengerQueue, MetroSim, and
 *          all other classes used for the MetroSim program.
 *
 */
#include "Passenger.h"
#include "PassengerQueue.h"
#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/*
 * passenger print test
 * test the print function for the Passenger class
 */
void passengerPrintTest() {
    Passenger pass(1, 3, 19);
    ostringstream my_stream;
    pass.print(my_stream);
    assert(my_stream.str() == "[1, 3->19]");
}

/*
 * passenger queue front test
 * make sure front returns the correct passenger
 */
void queueFrontTest() {
    PassengerQueue pq;
    Passenger p1(1, 2, 3);
    Passenger p2(2, 4, 5);
    pq.enqueue(p1);
    pq.enqueue(p2);
    ostringstream my_stream;
    Passenger front = pq.front();
    front.print(my_stream);
    assert(my_stream.str() == "[1, 2->3]");
}

/*
 * passenger queue front test 2
 * make sure front returns the correct passenger when dequeue is used
 */
void queueFrontTest2() {
    PassengerQueue pq;
    Passenger p1(1, 2, 3);
    Passenger p2(2, 4, 5);
    pq.enqueue(p1);
    pq.enqueue(p2);
    pq.dequeue();
    ostringstream my_stream;
    Passenger front = pq.front();
    front.print(my_stream);
    assert(my_stream.str() == "[2, 4->5]");
}

/*
 * passenger queue size test
 * make sure size returns the correct number
 */
void queueSizeTest() {
    PassengerQueue pq;
    assert(pq.size() == 0);
    Passenger p1(1, 2, 3);
    Passenger p2(2, 4, 5);
    pq.enqueue(p1);
    pq.enqueue(p2);
    assert(pq.size() == 2);
}

/*
 * passenger queue print test
 * test the print function for the PassengerQueue class
 */
void queuePrintTest() {
    PassengerQueue pq;
    Passenger p1(1, 2, 3);
    Passenger p2(2, 4, 5);
    Passenger p3(3, 9, 20);
    pq.enqueue(p1);
    pq.enqueue(p2);
    pq.enqueue(p3);
    ostringstream my_stream;
    pq.print(my_stream);
    assert(my_stream.str() == "[1, 2->3][2, 4->5][3, 9->20]");
}

/*
 * passenger queue enqueue test
 * test the enqueue function for the PassengerQueue class
 */
void queueEnqueueTest() {
    PassengerQueue pq;
    ostringstream my_stream1, my_stream2;
    Passenger p1(1, 2, 3);
    Passenger p2(2, 4, 5);
    Passenger p3(3, 9, 20);
    pq.enqueue(p1);
    pq.print(my_stream1);
    assert(my_stream1.str() == "[1, 2->3]");
    pq.enqueue(p2);
    pq.enqueue(p3);
    pq.print(my_stream2);
    assert(my_stream2.str() == "[1, 2->3][2, 4->5][3, 9->20]");
}

/*
 * passenger queue dequeue test
 * test the dequeue function for the PassengerQueue class
 */
void queueDequeueTest() {
    PassengerQueue pq;
    ostringstream my_stream1, my_stream2;
    Passenger p1(1, 2, 3);
    Passenger p2(2, 4, 5);
    Passenger p3(3, 9, 20);
    pq.enqueue(p1);
    pq.enqueue(p2);
    pq.enqueue(p3);
    pq.print(my_stream1);
    assert(my_stream1.str() == "[1, 2->3][2, 4->5][3, 9->20]");
    pq.dequeue();
    pq.print(my_stream2);
    assert(my_stream2.str() == "[2, 4->5][3, 9->20]");
}