/*
 * main.cpp
 * CS 15 Project 4: gerp
 * Eleanor Elkus (eelkus01) and Talia Tepper (tteppe01)
 * Date Created: 4/18/23
 *
 * Purpose: Process the command line arguments, ensure they're valid, and run
 *          the gerp program
 *
 */

#include "gerp.h"

using namespace std;

/* name:        main
 * purpose:     process command line arguments and run gerp
 * arguments:   argc and argv
 * returns:     0
 * effects:     makes a Gerp object and runs gerp
 */
int main(int argc, char *argv[]) {
    //make sure correct number of arguments are given
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        exit(EXIT_FAILURE);
    }
    
    //pass in directory and output file into runGerp
    Gerp gerp;
    gerp.runGerp(argv[1], argv[2]);

    return 0;
}