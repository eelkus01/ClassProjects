/*
 * phaseOne.h
 * CS 15 Project 3: zap
 * Eleanor Elkus (eelkus01)
 * Date Created: 3/28/23
 *
 * Purpose: Contains the declaration of functions that can count the frequency
 *          of characters in a string and serialize or deserialize a Huffman
 *          Tree.
 *
 */

#include <string>
#include <iostream>
#include "HuffmanTreeNode.h"

void count_freqs(std::istream &text);
std::string serialize_tree(HuffmanTreeNode *root);
HuffmanTreeNode *deserialize_tree(std::string serial_tree);
HuffmanTreeNode *deserialize_helper(std::istream &tree);