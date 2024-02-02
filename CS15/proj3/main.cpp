/*
 * main.cpp
 * CS 15 Project 3: zap
 * Eleanor Elkus (eelkus01)
 * Date Created: 4/4/23
 *
 * Purpose: Process the command line arguments, ensure they're valid, and call
 *          either the encoder or decoder function of the HuffmanCoder class.
 *
 */

#include "HuffmanCoder.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]) {
    //make sure correct number of arguments are given
    if (not (argc == 4 and (strcmp(argv[1], "zap") == 0 or 
        strcmp(argv[1], "unzap") == 0))) {
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile" << endl;
        exit(EXIT_FAILURE);
    }

    //run encoder or decoder
    HuffmanCoder run;
    if (strcmp(argv[1], "zap") == 0) {
        run.encoder(argv[2], argv[3]);
    } else {
        run.decoder(argv[2], argv[3]);
    }

    return 0;
}