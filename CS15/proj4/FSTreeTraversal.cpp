/*
 * FSTreeTraversal.cpp
 * CS 15 Project 4: gerp
 * Eleanor Elkus (eelkus01) and Talia Tepper (tteppe01)
 * Date Created: 4/13/23
 *
 * Purpose: Traverses the directory named upon program call and prints the file
 *          paths of all files contained within the directory.
 *
 */

#include "FSTree.h"
#include <iostream>
#include <queue>

using namespace std;

void traverseTree(DirNode *curr, string &path);

/* name:        main
 * purpose:     process command line arguments and pass them to the
 *              traverseTree function; exit program if wrong number of command
 *              line arguments
 * arguments:   argc and argv
 * returns:     none
 * effects:     none
 */
int main(int argc, char *argv[]) {
    //print error if wrong number of command line args
    if (argc != 2) {
        cerr << "Usage: ./treeTraversal DirectoryName\n";
        exit(EXIT_FAILURE);
    }

    //make a tree of the given directory
    FSTree tree = FSTree(argv[1]);
    DirNode *root = tree.getRoot(); 
    string directory = root->getName();

    //pass tree into function to print file paths
    traverseTree(root, directory);

    return 0;
}

/* name:        traverseTree
 * purpose:     traverse the given tree, printing all possible file paths
 * arguments:   a pointer to the current DirNode (originaly the root of the
 *              tree) and the string of the directory to print
 * returns:     none
 * effects:     prints the file paths of all files in the directory
 */
void traverseTree(DirNode *curr, string &path) {
    //if directory has files, print them
    if (curr->hasFiles()) {
        int numFiles = curr->numFiles();

        //parsing through each file in the directory
        for (int i = 0; i < numFiles; i++) {
            cout << path << "/" << curr->getFile(i) << endl;
        }
    }

    //if directory has subdirectories, call recursively
    if (curr->hasSubDir()) {
        int numSubDirs = curr->numSubDirs();

        //parsing through each subdirectory in the directory
        for (int i = 0; i < numSubDirs; i++) {
            //add to directory string
            path += "/";
            path += curr->getSubDir(i)->getName();

            traverseTree(curr->getSubDir(i), path);

            //erase from directory string
            int length = path.length() - 
                curr->getSubDir(i)->getName().length() - 1;
            path = path.substr(0, length);
        }
    }
}