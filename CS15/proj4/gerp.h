/*
 * gerp.h
 * CS 15 Project 4: gerp
 * Eleanor Elkus (eelkus01) and Talia Tepper (tteppe01)
 * Date Created: 4/18/23
 *
 * Purpose: Interface of the gerp class; the gerp program can be run using the
 *          directory and output file passed in
 *
 */

#ifndef GERP_H
#define GERP_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include "DirNode.h"

using namespace std;


class Gerp {
public:

    void runGerp(string directoryToIndex, string outputFileName);
    Gerp();
    ~Gerp();


private:
    //private member variables
    float loadFactor;
    float size;
    int capacity;

    struct Info {
        //index to reference the file path
        int filePath;

        int fileLineNum;

        //index to reference the line text
        int vectorLineNum;

        string word;
    };

    //vector to hold each line in each file
    vector<string> lineText;

    //vector to hold each file path
    vector<string> filePathVect;

    //hash table (array of vectors of vectors)
    vector<vector <Info>> *hashTable;

    //functions for the struct
    Info newInfo(int &path, int &lineNum, int &index, string &word);
    
    //functions for hashing
    float calculateLoadFactor();
    void processFile(ifstream &fileName, string &filePath);
    void traverseDirectory(string &directoryToIndex);
    void traverseTree(DirNode *curr, string &path);
    bool isCollision(string &word, int &index);
    bool isEqual(string &a, string &b);
    string lowercase(string &word);
    void handleCollision( Info &info, int &index);
    int findIndex(int &hashIndex, string &word);
    void handleHash(Info &info);
    void handleRehash();

    //functions for testing
    void printHash();
    void printText();
    void printPath();

    //query functions
    void queryLoop(istream &input, ofstream &outputFile);
    void handleOutputChange(ofstream &outputFile, string &filename);
    void handleAnyString(string &anyString, bool insensitive, 
                         ofstream &outputFile);
    void printResult(bool insensitive, string word, ofstream &outputFile,
                     bool found, vector<Info> foundInfo);
    void printToOutput(ofstream &outputFile, vector <Info> foundInfo);

};

#endif
