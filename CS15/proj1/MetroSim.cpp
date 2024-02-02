/*
 * MestroSim.cpp
 * CS 15 Project 1: Metro Simulation
 * Eleanor Elkus (eelkus01)
 * Date Created: 2/10/23
 *
 * Purpose: Implement a version of the MetroSim class; implementing from the
 *          MetroSim.h header file. Here, the train can be moved, stations and
 *          passengers can be made, and passengers can be moved to and from the
 *          train.
 *
 */

#include "MetroSim.h"
#include <sstream>
#include <stdexcept>

using namespace std;

/*
 * name:        MetroSim constructor
 * purpose:     initialize the MetroSim game with the necessary starting values
 * arguments:   none
 * returns:     none
 * effects:     numStations and trainIndex to 0, passID to 1 (starting ID)
 */
MetroSim::MetroSim() {
    numStations = 0;
    passID = 1;
    trainIndex = 0;
}

/*
 * name:        newStation
 * purpose:     initialize a new Station within the MetroSim class
 * arguments:   the passenger queue, station name, and bool to add to station
 * returns:     the new Station
 * effects:     sq, stationName, and trianHere contain the given info; new
 *              Station is created
 */
MetroSim::Station MetroSim::newStation(PassengerQueue sq, 
                                        string stationName, bool trainHere) {
    Station new_station;
    new_station.sq = sq;
    new_station.stationName = stationName;
    new_station.trainHere = trainHere;
    return new_station;
}

/*
 * name:        makeStations
 * purpose:     read in the station file and make a station corresponding to
 *              each name
 * arguments:   the filestream to read from
 * returns:     none
 * effects:     makes the stations, updates numStations, makes onTrain the
 *              correct size
 */
void MetroSim::makeStations(std::istream &stationStream) {
    string temp;
    while (not getline(stationStream, temp).fail()) {
        PassengerQueue empty;
        Station newStat = newStation(empty, temp, false);
        //add to station vector
        station.push_back(newStat);
        numStations++;
        //add to train vector (for size purposes)
        onTrain.push_back(newStat.sq);
    }

    //set trainHere for first station to true
    station.front().trainHere = true;
}

/*
 * name:        print
 * purpose:     print the Stations and their PassengerQueues; should be run
 *              after each command in order to print the new screen
 * arguments:   none
 * returns:     none
 * effects:     prints the screen
 */
void MetroSim::print() {
    //print passengers on train
    cout << "Passengers on the train: {";
    for (int i = 0; i < numStations; i++) onTrain.at(i).print(cout);
    cout << "}" << endl;

    //print stations
    for (int i = 0; i < numStations; i++) {
        //if train is at the station, print TRAIN
        if (station.at(i).trainHere == true) {
            cout << "TRAIN: ";
        //otherwise, print 7 spaces
        } else {
            cout << "       ";
        }
        //print station index and name
        cout << "[" << i << "] " << station.at(i).stationName << " ";

        //print station's passenger queue and new line
        cout << "{";
        station.at(i).sq.print(cout);
        cout << "}" << endl;
    }

    cout << "Command? ";
}

/*
 * name:        run
 * purpose:     actually run the MetroSim game on the given move
 * arguments:   the input stream to read from and the output stream to print to
 * returns:     none
 * effects:     plays the MetroSim simulation
 */
void MetroSim::run(std::istream &input, std::ostream &output) {
    //reset the screen
    print();
    //read in the move
    std::string move, command;
    int arrive, depart;
    bool gameDone = false;
    input >> move;
    //query loop
    while ((not input.fail()) and (not gameDone)) {
        //move train or end game
        if (move == "m") {
            input >> command;
            if (command == "m") {
                moveTrain(output);
            } else if (command == "f") {
                gameDone = true;
            }
        //add passenger
        } else if (move == "p") {
            input >> arrive >> depart;
            addPassenger(arrive, depart);
        }
        //read in next move
        if (command != "f") input >> move;
    }
    cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
}

/*
 * name:        moveTrain
 * purpose:     move the train to the next station, collect passengers, drop
 *              passengers off
 * arguments:   the output stream to print to if passengers depart
 * returns:     none
 */
void MetroSim::moveTrain(std::ostream &output) {
    trainIndex = (trainIndex + 1) % numStations;
    //change where train is
    Station curr = station.at(trainIndex);
    Station prev;
    if (trainIndex == 0) {
        prev = station.back();
    } else {
        prev = station.at(trainIndex - 1);
    }
    prev.trainHere = false;
    curr.trainHere = true;
    //move passengers from previous station to train
    prev = emptyStation(prev);
    //dequeue from onTrain if applicable
    while (onTrain.at(trainIndex).size() != 0) {
        //print statement to output file
        output << "Passenger " << onTrain.at(trainIndex).front().id;
        output << " left train at station " << curr.stationName << endl;
        //remove passenger
        onTrain.at(trainIndex).dequeue();
    }
    station.at(trainIndex) = curr;
    if (trainIndex == 0) {
        station.back() = prev;
    } else {
        station.at(trainIndex - 1) = prev;
    }
    print();
}

/*
 * name:        addPassenger
 * purpose:     add the new passenger to the specified station queue
 * arguments:   the passenger's start and end station
 * returns:     none
 * effects:     new passenger created and added to station; passID incremented
 */
void MetroSim::addPassenger(int arrive, int depart) {
    //make new passenger with necessary info
    Passenger newPass(passID, arrive, depart);

    //add passenger to its arrival station's queue
    station.at(arrive).sq.enqueue(newPass);
    passID++;

    //reset screen
    print();
}

/*
 * name:        emptyStation
 * purpose:     put all passengers at the previous station on the train and
 *              remove them from the station
 * arguments:   the previous station
 * returns:     the updated previous station
 * effects:     enqueues to onTrain and dequeues prev
 */
MetroSim::Station MetroSim::emptyStation(Station prev) {
    //enqueue to onTrain any passengers at prev station
    while (prev.sq.size() != 0) {
        for (int i = 0; i < prev.sq.size(); i++) {
            //get the departure station of the passenger
            int index = prev.sq.front().to;
            //add passenger to train
            onTrain.at(index).enqueue(prev.sq.front());
            //remove passenger from station
            prev.sq.dequeue();
        }
    }
    return prev;
}
