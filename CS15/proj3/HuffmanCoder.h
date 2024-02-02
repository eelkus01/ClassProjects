/*
 * HuffmanCoder.h
 * CS 15 Project 3: zap
 * Eleanor Elkus (eelkus01)
 * Date Created: 4/4/23
 *
 * Purpose: Interface of the HuffmanCoder class; the text file can be encoded
 *          (compressed) or decoded (decompressed) depending on how the program
 *          is run.
 *
 */

#ifndef __HUFFMANCODER_H__
#define __HUFFMANCODER_H__

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
#include "HuffmanTreeNode.h"

using namespace std;

class HuffmanCoder {
public:
    void encoder(const string &input_file, const string &output_file);
    void decoder(const string &input_file, const string &output_file);

    //Constructor and destructor
    HuffmanCoder();
    ~HuffmanCoder();

private:
    //encoder helper functions
    template<typename streamtype>
    void openFile(streamtype &stream, string fileName);
    void countFreqs(istream &text);
    HuffmanTreeNode *buildTree();
    void deleteTree(HuffmanTreeNode *node);
    void makeCodes(HuffmanTreeNode *node, string code);
    string encodeText(istream &text);
    string serializeTree(HuffmanTreeNode *root);

    //decoder helper functions
    HuffmanTreeNode *deserializeTree(string serial_tree);
    HuffmanTreeNode *deserializeHelper(istream &tree);
    string decode(string encoding, HuffmanTreeNode *node);

    //a map of chars to ints to store the frequency of chars in a text
    map<char, int> freqMap;

    //a map of chars to strings to store the character codes for a tree
    map<char, string> codeMap;

    //the minheap priority queue to store the HuffmanTreeNodes
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>,
                   NodeComparator> mypq;
};

#endif