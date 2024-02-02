/*
 * gerp.cpp
 * CS 15 Project 4: gerp
 * Eleanor Elkus (eelkus01) and Talia Tepper (tteppe01)
 * Date Created: 4/18/23
 *
 * Purpose: Implement a version of the Gerp class; implementing from the gerp.h
 *          header file. The given directory can be indexed and the user can
 *          interactively ask whether a word is contained in any of the files
 *          within the directory; output of such queries is saved to the given
 *          output file, which can also be interactively changed to a different
 *          file.
 *
 */

#include <iostream>
#include <ostream>
#include <fstream>
#include <functional>
#include <stdio.h>
#include <ctype.h>
#include "gerp.h"
#include "FSTree.h"
#include "stringProcessing.h"

using namespace std;


/* name:        Gerp
 * purpose:     constructor
 * arguments:   none
 * returns:     none
 * effects:     size to 0, capacity to 100, initialize hashTable
 */
Gerp::Gerp(){
    size = 0;
    capacity = 100;
    hashTable = new vector<vector <Info>>[capacity];
}

/* name:        Gerp destructor
 * purpose:     recycle any heap allocated memory
 * arguments:   none
 * returns:     none
 * effects:     deletes hash table and sets it to nullptr
 */
Gerp::~Gerp(){
    delete [] hashTable;
    hashTable = nullptr;
}

/* name:        runGerp
 * purpose:     start the program by traversing the given directory, making
 *              an output stream from the given output file, and running the
 *              query loop
 * agruments:   the directory to index and the output file to save info to
 * returns:     none
 * effects:     call the functions to traverse the directory and start the
 *              query loop
 */
void Gerp::runGerp(string directoryToIndex, string outputFileName) {
    //make hashtable
    traverseDirectory(directoryToIndex);

    //call query loop 
    ofstream outstream;
    outstream.open(outputFileName);
    queryLoop(cin, outstream);
}

/* name:        queryLoop
 * purpose:     prompt user for query until either end of file is reached or
 *              the user prompts for quit
 * arguments:   the input stream and the output file to write to
 * returns:     none
 * effects:     prompts for query and prints goodbye message after program has
 *              ended
 */
void Gerp::queryLoop(istream &input, ofstream &outputFile) {
    bool quit = false;
    bool insensitive = false;
    //prompt query
    string query;
    cout << "Query? ";
    input >> query;
    while ((not quit) and (not input.eof())) {
        if (query == "@i" or query == "@insensitive") {
            //read in word
            string queryWord;
            input >> queryWord;
            insensitive = true;
            handleAnyString(queryWord, insensitive, outputFile);
            insensitive = false;
        } else if (query == "@q" or query == "@quit") {
            quit = true;
        } else if (query == "@f") {
            //read in filename
            string filename;
            input >> filename;
            handleOutputChange(outputFile, filename);
        } else {
            handleAnyString(query, insensitive, outputFile);
        }
        if (not quit) {
            cout << "Query? ";
            input >> query;
        }
    }
    cout << "Goodbye! Thank you and have a nice day.\n";
}


/* name:        handleOutputChange
 * purpose:     handles changing the output stream to a specified output file
 * arguments:   the output filestream and the new filename to print to
 * returns:     none
 * effects:     closes previous file and reopens stream with the new file
 */
void Gerp::handleOutputChange(ofstream &outputFile, string &filename) {
    //close old output file
    outputFile.close();

    //open and proccesses new output file
    outputFile.open(filename);
}

/* name:        handleAnyString
 * purpose:     handles searching for and processing AnyString
 * arguments:   the word we are looking for in the files, a bool that is true
 *              the word should be searched insensitively and false if not, and
 *              the output stream to print results to
 * returns:     none
 * effects:     traverses hashTable for instances of the given word, passing
 *              results into the necessary functions
 */
void Gerp::handleAnyString(string &anyString, bool insensitive, 
                            ofstream &outputFile) {
    anyString = stripNonAlphaNum(anyString);
    bool found = false;
    vector <Info> foundInfo;
    //search for instances of that word
    if (anyString != "") {
        for (int i = 0; i < capacity; i++) {
            int outerNumVecs = hashTable[i].size();
            for (int j = 0; j < outerNumVecs; j++) {
                int innerNumVecs = hashTable[i].at(j).size();
                for (int k = 0; k < innerNumVecs; k++) {
                    string compWord = hashTable[i].at(j).at(k).word;
                    if (insensitive) {
                        if (isEqual(compWord, anyString)) {
                            found = true;
                            foundInfo.push_back(hashTable[i].at(j).at(k));
                        }
                    } else {
                        if (anyString.compare(compWord) == 0) {
                            found = true;
                            foundInfo.push_back(hashTable[i].at(j).at(k));
                        }
                    }
                }
            }
        }
    }
    printResult(insensitive, anyString, outputFile, found, foundInfo);
}

/* name:        printResult
 * purpose:     prints to the output file whether or not a word is found; if
 *              found, it prints all information pertaining to the word
 * arguments:   a bool that is true if the search was insensitive and false
 *              otherwise, the word that was searched for, and the outputfile
 *              to print to, and a bool saying whether or not the word was
 *              found
 * returns:     none
 * effects:     prints the search result to the output file
 */
void Gerp::printResult(bool insensitive, string word, ofstream &outputFile,
                       bool found, vector<Info> foundInfo) {
    if (not found) {
        if (insensitive) {
            outputFile << word << " Not Found." << endl;
        } else {
            outputFile << word;
            outputFile << " Not Found. Try with @insensitive or @i." << endl;
        }
    } else {
        printToOutput(outputFile, foundInfo);
    }
}

/* name:        printToOutput
 * purpose:     print the necessary information to the given output file
 * arguments:   the output file to print to and the info struct containing the
 *              information to print
 * returns:     none
 * effects:     prints all information pertaining to the instance of the word
 *              to the output file
 */
void Gerp::printToOutput(ofstream &outputFile, vector <Info> foundInfo) {
    //parse through vector and remove duplicates
    int vectSize = foundInfo.size();
    if (vectSize > 1) {
        vector<Info>::iterator it;
        int i = 0;
        for (it = foundInfo.begin(); it != foundInfo.end(); it++) {
            //move iterator forward if at beginning
            if (it == foundInfo.begin()) it++;
            Info prev = foundInfo.at(i);
            Info curr = foundInfo.at(i + 1);
            //if same line text and file path, remove one
            if ((prev.fileLineNum == curr.fileLineNum) and 
                (prev.filePath == curr.filePath)) {
                foundInfo.erase(it--);
            } else {
                i++;
            }
        }
    }

    //print everything to output file
    int newVectSize = foundInfo.size();
    for (int i = 0; i < newVectSize; i++) {
        outputFile << filePathVect.at(foundInfo.at(i).filePath) << ":";
        outputFile << foundInfo.at(i).fileLineNum << ": ";
        outputFile << lineText.at(foundInfo.at(i).vectorLineNum) << endl;
    }
}

/* name:        newInfo
 * purpose:     intialize the variables of an Info object
 * arguments:   the file path, line num, line index, and key word of the Info
 *              to construct
 * returns:     the new Info object
 * effects:     filePath to path, fileLineNum to lineNum, vectorLineNum to
 *              index, word to keyWord
 */
Gerp::Info Gerp::newInfo(int &path, int &lineNum, 
                         int &index, string &keyWord) {
    Info new_info;
    new_info.filePath = path;
    new_info.fileLineNum = lineNum;
    new_info.vectorLineNum = index;
    new_info.word = keyWord;
    return new_info;
}

/* name:        processFile
 * purpose:     process each line and string in the given filestream
 * arguments:   the filestream to read from and the string file path
 * returns:     none
 * effects      ??
 */
void Gerp::processFile(ifstream &fileName, string &filePath) {
    string line;
    //variable to count the file line we are on
    int fileIndex = 1;

    //add filePath to its vector
    filePathVect.push_back(filePath);
    int filePathIndex = filePathVect.size() - 1;

    while(getline(fileName, line)) {
        //add line text to vector
        //check if line is just newline/empty string
        int vectorIndex;
        if (line != "") {
            lineText.push_back(line);
            vectorIndex = lineText.size() - 1;
        }

        //make stringstream of line and process each string in line
        stringstream stream(line);
        string word;

        while (stream >> word) {
            //remove leading and trailing nonalphanumeric chars
            word = stripNonAlphaNum(word);

            //make struct element for word
            Info info = newInfo(filePathIndex, fileIndex, vectorIndex, word);

            //add to hash table
            handleHash(info);
        }
        fileIndex++;
    }
}

/* name:        handleHash
 * purpose:     handles hashing the info into the vector
 * arguments:   the Info struct to be hashed
 * returns:     nothing
 * effects:     updates the hash table with hashed elements
 * notes:       checks for and handles collisions and rehashing
 */
void Gerp::handleHash(Info &info) {
    string word = info.word;

    //find index using hash function
    string key = lowercase(word);
    int index = hash<string>{}(key) % capacity;
    if (not isCollision(word, index)) {
        //push back struct element into vector within the hashTable
        if (hashTable[index].empty()) {
            vector<Info> internalVector;
            internalVector.push_back(info);
            hashTable[index].push_back(internalVector);
        } else {
            //push it into the vector it belongs to
            int vectorIndex = findIndex(index, word);
            hashTable[index].at(vectorIndex).push_back(info);
        }
        size++;
    } else {
        handleCollision(info, index);
        size++;
    }

    //check load factor and rehash if necessary
    if (calculateLoadFactor() > 0.75) {
        handleRehash();
    }
}

/* name:        handleRehash
 * purpose:     handle rehashing
 * arguments:   none
 * returns:     none
 * effects:     changes the hash table to be of twice the capacity 
 *              and rehashing each element into the new hash table
 */
void Gerp::handleRehash() {
    int oldSize = capacity;

    //update the size and capacity and make new bigger hashTable
    capacity = capacity * 2;
    size = 0;

    //store hash table in temp and make a new array of new capacity
    vector<vector <Info>> *temp = hashTable;
    hashTable = new vector<vector <Info>>[capacity];

    //recompute the bucket number for each element (with new table capacity)
    for (int i = 0; i < oldSize; i++) {
        int internalSize = temp[i].size();
        for (int j = 0; j < internalSize; j++) {
            int internalSize2 = temp[i].at(j).size();
            for (int k = 0; k < internalSize2; k++) {
                handleHash(temp[i].at(j).at(k));
            }
        }
    }
    //delete temp (will also delete old hashTable)
    delete [] temp;
}

/* name:        isCollision
 * purpose:     check if there is a collision when inserting a new element into
 *              the hash table
 * arguments:   word to be inserted, index within hash table
 * returns:     true if results in a collision, false otherwise
 * effects:     none
 */
bool Gerp::isCollision(string &word, int &index) {
    bool collides = true;
    if (not hashTable[index].empty()) {
        //check the lowercased versions of the strings
        int numVecs = hashTable[index].size();
        for (int i = 0; i < numVecs; i++) {
            if (isEqual(hashTable[index].at(i).front().word, word)) {
                collides = false;
            }
        }
    } else {
        collides = false;
    }
    return collides;
}

/* name:        handleCollision
 * purpose:     handle the case of a collision using chaining
 * arguments:   the info struct being added, the index in the hash table
 * returns:     nothing
 * effects:     chains -- creates a vector of structs within the hash table
 *              vector
 */
void Gerp::handleCollision (Info &info, int &index) {
    //chaining
    //push back struct into the back of
    //the vector already within the vector
    vector<Info> collisionVector;
    collisionVector.push_back(info);
    hashTable[index].push_back(collisionVector);
}

/* name:        findIndex
 * purpose:     find the index of the internal vector that matches the word
 * arguments:   the index of the hash table, the word to be inserted
 * returns:     returns the correct placement (index) of the internal vector
 * effects:     none
 */
int Gerp::findIndex(int &hashIndex, string &word) {
    //iterate through external vector
    int index = 0;
    int externalVectorSize = hashTable[hashIndex].size();
    for (int i = 0; i < externalVectorSize; i++) {
        //look through each internal vector, checking if the front word = word
        if (hashTable[hashIndex].at(i).front().word == word){
            index = i;
        }
    }
    return index;
}

/* name:        traverseDirectory
 * purpose:     traverse the given directory, making a FSTree, and pass tree
 *              into function to process
 * arguments:   the directory to index
 * returns:     none
 * effects:     none
 */
void Gerp::traverseDirectory(string &directoryToIndex) {
    //make a tree of the given directory
    FSTree tree = FSTree(directoryToIndex);
    DirNode *root = tree.getRoot(); 
    string directory = root->getName();

    //pass tree into function to handle file processing
    traverseTree(root, directory);
}

/* name:        traverseTree
 * purpose:     traverse the given tree, handling all possible file paths
 * arguments:   a pointer to the current DirNode (originaly the root of the
 *              tree) and the string of the directory to index
 * returns:     none
 * effects:     none, but gives us access to reading through files
 */
void Gerp::traverseTree(DirNode *curr, string &path) {
    if (curr->hasFiles()) {
        int numFiles = curr->numFiles();
        //parsing through each file in the directory
        for (int i = 0; i < numFiles; i++) {
            //update file path
            path += "/" + curr->getFile(i);
            //make file into filestream and process it
            ifstream filestream(path);
            processFile(filestream, path);
            //erase file name from string
            int length = path.length() - curr->getFile(i).length() - 1;
            path = path.substr(0, length);
        }
    }
    //if directory has subdirectories, call recursively
    if (curr->hasSubDir()) {
        int numSubDirs = curr->numSubDirs();
        //parsing through each subdirectory in the directory
        for (int i = 0; i < numSubDirs; i++) {
            //add to directory string
            path += "/" + curr->getSubDir(i)->getName();
            traverseTree(curr->getSubDir(i), path);
            //erase directory name from directory string
            int length = path.length() - 
                curr->getSubDir(i)->getName().length() - 1;
            path = path.substr(0, length);
        }
    }
}

/* name:        isEqual
 * purpose:     compare two strings and their lowercased versions
 * arguments:   two pointers to two strings
 * returns:     returns true if they are equal, false otherwise
 * effects      none
 */
bool Gerp::isEqual(string &a, string &b) {
    int aSize = a.size();
    int bSize = b.size();
    if (bSize != aSize) {
        return false;
    }
    for (int i = 0; i < aSize; i++) {
        if (tolower(a[i]) != tolower(b[i])) {
            return false;
        }
    }
    return true;
}

/* name:        lowercase
 * purpose:     convert a string to the lowercase version
 * arguments:   a string to convert to lowercase
 * returns:     a lowercase version of the argument string
 * effects:     none
 */
string Gerp::lowercase(string &word) {
    string newWord;
    int wordSize = word.size();
    for (int i = 0; i < wordSize; i++) {
        newWord += tolower(word[i]);
    }
    return newWord;
}

/* name:        calculateLoadFactor
 * purpose:     calculate and update the load factor of the hash table
 * arguments:   none
 * returns:     the new load factor
 * effects:     updates loadFactor to the newly calculated loadFactor
 */
float Gerp::calculateLoadFactor() {
    //change loadFactor to be the new count divided by capacity
    loadFactor = size/capacity;
    return loadFactor;
}

/* name:        printHash
 * purpose:     print the hash table for testing purposes
 * arguments:   none
 * returns:     none
 * effects      none
 * notes:       only used for testing purposes
 */
void Gerp::printHash() {
    cout << "\n\nHASH TABLE:\n";
    cout << "---------------------------------------\n";
    for (int i = 0; i < capacity; i++) {
        //if vector isn't empty, print its vector
        if (not hashTable[i].empty()) {
            cout << i << " | ";
            //print vector
            int outerSize = hashTable[i].size();
            for (int j = 0; j < outerSize; j++) {
                cout << "{";
                int internalSize = hashTable[i].at(j).size();
                for (int k = 0; k < internalSize; k++) {
                    cout << "<";
                    cout << hashTable[i].at(j).at(k).word << ", "
                        << hashTable[i].at(j).at(k).filePath << ", "
                        << hashTable[i].at(j).at(k).vectorLineNum;
                    cout << ">";
                }
                cout << "}";
            }
            cout << endl;
        }
    }
}

/* name:        printText
 * purpose:     print the lineText vector for testing purposes
 * arguments:   none
 * returns:     none
 * effects:     none
  * notes:      only used for testing purposes
 */
void Gerp::printText() {
    cout << "\n\nLINE TEXT VECTOR:\n";
    cout << "---------------------------------------\n";
    int sizeNum = lineText.size();
    for (int i = 0; i < sizeNum; i++) {
        cout << i << " | " << lineText.at(i) << endl;
    }
}

/* name:        printPath
 * purpose:     print the filePath vector for testing purposes
 * arguments:   none
 * returns:     none
 * effects:     none
  * notes:      only used for testing purposes
 */
void Gerp::printPath() {
    cout << "\nFILE PATH VECTOR:\n";
    cout << "---------------------------------------\n";
    int sizeNum = filePathVect.size();
    for (int i = 0; i < sizeNum; i++) {
        cout << i << " | " << filePathVect.at(i) << endl;
    }
}