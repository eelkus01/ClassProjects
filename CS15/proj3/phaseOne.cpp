/*
 * phaseOne.cpp
 * CS 15 Project 3: zap
 * Eleanor Elkus (eelkus01)
 * Date Created: 3/28/23
 *
 * Purpose: Contains the definition of the functions declared in phaseOne.h,
 *          which count the frequency of characters in a string and serialize
 *          or deserialize a Huffman Tree.
 *
 */

#include "phaseOne.h"
#include <map>
#include <sstream>

/* name:        count_freqs
 * purpose:     read in the entire stream, count the number of occurrences of
 *              every character, and print the results to cout
 * arguments:   a reference to an istream to read from
 * returns:     none
 */
void count_freqs(std::istream &text) {
    //make a map of chars to ints
    std::map<char, int> map;

    char c;
    while(text.get(c)) {
        //check if char has already been read
        if (map.count(c) > 0) {

            //increase existing count
            map[c] += 1;

        } else {

            //add char to map
            map[c] = 1;
        }
    }

    //iterate through the map and print the elements
    std::map<char, int>::iterator it = map.begin();
    while (it != map.end()) {
        std::cout << it->first << ": " << it->second << std::endl;
        ++it;
    }
}

/* name:        serialize_tree
 * purpose:     serialize the tree pointed to in the input
 * arguments:   a pointer to a Huffman tree
 * returns:     the serialized version of the tree
 */
std::string serialize_tree(HuffmanTreeNode *root) {
    //make string to apphend to
    std::string tree = "";

    //if internal node, add I to string, do left, then right
    if (not root->isLeaf()) {
        tree += "I";
        tree += serialize_tree(root->get_left());
        tree += serialize_tree(root->get_right());
    } else {
        //node is leaf, so add L and node's value
        tree += "L";
        tree += root->get_val();
    }

    return tree;
}

/* name:        deserialize_tree
 * purpose:     given a serialized tree, reconstruct the Huffman tree and
 *              return a pointer to its root by calling a helper function
 * arguments:   the serialized tree to deserialize
 * returns:     a pointer to the deserialized tree's root
 * effects:     deserializes the given tree
 */
HuffmanTreeNode *deserialize_tree(std::string serial_tree) {
    //make serialized string into stringstream
    std::istringstream stream(serial_tree);

    //call helper funtion
    HuffmanTreeNode *root = deserialize_helper(stream);

    return root;
}

/* name:        deserialize_helper
 * purpose:     reconstruct the Huffman tree from the provided stringstream
 *              containing the tree's serialization
 * arguments:   a reference to a stringstream
 * returns:     a pointer to the tree's root
 * effects:     makes a new Huffman Tree and it's nodes
 */
HuffmanTreeNode *deserialize_helper(std::istream &tree) {
    const char INTERNAL_NODE_VAL = '\0';
    const int FREQ = 1;
    char c;
    char letter;
    HuffmanTreeNode *node;

    //read in letter
    tree.get(c);

    //if internal node, call on left and then right
    if (c == 'I') {
        node = new HuffmanTreeNode(INTERNAL_NODE_VAL, FREQ);

        //call on left subtree
        node->set_left(deserialize_helper(tree));

        //call on right subtree
        node->set_right(deserialize_helper(tree));

    //if leaf node, make the node with the necessary value
    } else {
        tree.get(letter);
        node = new HuffmanTreeNode(letter, FREQ);
    }

    return node;
}