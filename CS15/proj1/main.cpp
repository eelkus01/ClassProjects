/*
 * main.cpp
 * CS 15 Project 1: Metro Simulation
 * Eleanor Elkus (eelkus01)
 * Date Created: 2/10/23
 *
 * Purpose: Handle simple driver functions in order to open, read in, and close
 *          files necessary to run the MetroSim game.
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "MetroSim.h"

using namespace std;

//functions
void abort(string errorMessage);
template<typename streamtype>
void openOrDie(streamtype &stream, string fileName);
MetroSim readStations(string stationFile);

int main(int argc, char *argv[]) {
    // make sure correct number of arguments are given
    if (not ((argc == 3) or (argc == 4))) {
        abort("Usage: ./MetroSim stationsFile outputFile [commandsFile]");
    } else if (argc == 3) {
        //make the game and read in the stations
        MetroSim game = readStations(argv[1]);
        //run MetroSim with cin and outputFile
        ofstream outstream;
        openOrDie(outstream, argv[2]);
        game.run(cin, outstream);
        outstream.close();
    } else {
        //make the game and read in the stations
        MetroSim game = readStations(argv[1]);
        //declare file streams
        ofstream outstream;
        openOrDie(outstream, argv[2]);
        ifstream instream;
        openOrDie(instream, argv[3]);
        //run MetroSim with file streams
        game.run(instream, outstream);
        instream.close();
        outstream.close();
    }
    return 0;
}

/*
 * name:        abort
 * purpose:     print out the given error message and exit the program
 * arguments:   the error message to print
 * returns:     none
 * effects:     aborts the program and prints the given message
 */
void abort(string errorMessage) {
    cerr << errorMessage << endl;
    exit(EXIT_FAILURE);
}

/*
 * name:        openOrDie
 * purpose:     try to open the given file and abort on failure
 * arguments:   the filestream and filename to open
 * returns:     none
 */
template<typename streamtype>
void openOrDie(streamtype &stream, string fileName) {
    stream.open(fileName);
    if (not stream.is_open()) {
        abort("Error: could not open file " + fileName);
    }
}

/*
 * name:        readStations
 * purpose:     read in the stations file and pass to MetroSim
 * arguments:   none
 * returns:     the MetroSim game that is created with the stations
 * effects:     creates MetroSim game, opens, reads and closes stations file
 */
MetroSim readStations(string stationFile) {
    MetroSim game;
    ifstream stationStream;
    openOrDie(stationStream, stationFile);
    game.makeStations(stationStream);
    stationStream.close();

    return game;
}
