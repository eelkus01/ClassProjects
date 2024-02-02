/*
 * HuffmanCoder.cpp
 * CS 15 Project 3: zap
 * Eleanor Elkus (eelkus01)
 * Date Created: 4/4/23
 *
 * Purpose: Implement a version of the HuffmanCoder class; impelementing from
 *          the HuffmanCoder.h header file. The given input file can be
 *          compressed or decompressed using the Huffman coding algorithm and
 *          the result saved to the given output file.
 *
 */

#include "HuffmanCoder.h"
#include "BinaryIO.h"
#include <utility>
#include <sstream>

using namespace std;

/* name:        constructor
 * purpose:     initialize the HuffmanCoder object
 * arguments:   none
 * returns:     none
 */
HuffmanCoder::HuffmanCoder() {
}

/* name:        destructor
 * purpose:     initialize the HuffmanCoder object
 * arguments:   none
 * returns:     none
 */
HuffmanCoder::~HuffmanCoder() {
}

/* name:        encoder
 * purpose:     compress the given input file and store the result in the given
 *              output file
 * arguments:   the input and output files to read from and to respectively
 * returns:     none
 */
void HuffmanCoder::encoder(const string &input_file, const string &output_file){
    //open the input file and count character frequencies
    ifstream instream;
    openFile(instream, input_file);
    countFreqs(instream);
    instream.close();

    //build the tree
    HuffmanTreeNode *root = buildTree();

    //generate character codes
    string charCode = "";
    makeCodes(root, charCode);

    //reopen the input file and encode the text
    ifstream stream;
    openFile(stream, input_file);
    string encoding = encodeText(stream);
    stream.close();

    //serialize the tree
    string serial = serializeTree(root);

    //save to output file
    BinaryIO write;
    write.writeFile(output_file, serial, encoding);

    //print message and recycle memory
    cout << "Success! Encoded given text using ";
    cout << encoding.size() << " bits.\n";
    deleteTree(root);
}

/* name:        decoder
 * purpose:     decompress the given input file and store the result in the
 *              given output file
 * arguments:   the input and output files to read from and to respectively
 * returns:     none
 */
void HuffmanCoder::decoder(const string &input_file, const string &output_file){
    //read the input file
    BinaryIO read;
    pair<string, string> info = read.readFile(input_file);
    string serialTree = info.first;
    string encoding = info.second;

    //deserialize the tree
    HuffmanTreeNode *root = deserializeTree(serialTree);

    //use the tree to decode the string
    string message = decode(encoding, root);

    //save text to output file
    ofstream outstream;
    openFile(outstream, output_file);
    outstream << message;
    outstream.close();

    //recycle memory
    deleteTree(root);

}

/* name:        openFile
 * purpose:     try to open the given file and abort on failure
 * arguments:   the filestream and filename to open
 * returns:     none
 */
template<typename streamtype>
void HuffmanCoder::openFile(streamtype &stream, string fileName) {
    stream.open(fileName);
    if (not stream.is_open()) {
        throw runtime_error("Unable to open file " + fileName);
    }
}

/* name:        countFreqs
 * purpose:     read in the entire stream, count the number of occurrences of
 *              every character, and print the results to cout
 * arguments:   a reference to an istream to read from
 * returns:     none
 */
void HuffmanCoder::countFreqs(istream &text) {
    char c;
    while(text.get(c)) {
        //check if char has already been read
        if (freqMap.count(c) > 0) {

            //increase existing count
            freqMap[c] += 1;

        } else {

            //add char to map
            freqMap[c] = 1;
        }
    }
}

/* name:        buildTree
 * purpose:     build the Huffman Tree from the characters and their frequency
 * arguments:   none
 * returns:     the root of the tree created
 */
HuffmanTreeNode *HuffmanCoder::buildTree() {
    //make nodes for all characters in freqMap
    map<char, int>::iterator it = freqMap.begin();
    while (it != freqMap.end()) {
        HuffmanTreeNode *curr = new HuffmanTreeNode(it->first, it->second);
        //push node on priority queue
        mypq.push(curr);

        ++it;
    }

    //join 2 min frequency elements until 1 elem is left in pq
    while (mypq.size() > 1) {
        HuffmanTreeNode *first = mypq.top();
        mypq.pop();
        HuffmanTreeNode *sec = mypq.top();
        mypq.pop();
        int freqSum = first->get_freq() + sec->get_freq();

        //make parent that stores sum of freqs
        HuffmanTreeNode *par = new HuffmanTreeNode('\0', freqSum, first, sec);

        //push parent on pq and recycle memory
        mypq.push(par);
    }
    return mypq.top();
}

/* name:        deleteTree
 * purpose:     recursively free any memory allocated when building a tree
 * arguments:   the root of the tree to delete
 * returns:     none
 */
void HuffmanCoder::deleteTree(HuffmanTreeNode *node) {
    if (node == nullptr) {
        return;
    } else {
        deleteTree(node->get_left());
        deleteTree(node->get_right());
        delete node;
    }
}

/* name:        makeCodes
 * purpose:     generate the character codes of the Huffman Tree whose root is
 *              passed in as an argument; store the codes in a map
 * arguments:   the root of the tree to generate codes from and an empty string
 * returns:     none
 * effects:     fills the codeMap with the tree's nodes and their codes
 */
void HuffmanCoder::makeCodes(HuffmanTreeNode *node, string code) {
    if (not node->isLeaf()) {
        //left turn
        code += "0";
        makeCodes(node->get_left(), code);

        //remove most recent char b/c backtracking
        code.pop_back();

        //right turn
        code += "1";
        makeCodes(node->get_right(), code);

    } else {
        //add leaf node's value and code to codeMap
        codeMap[node->get_val()] = code;
    }
}

/* name:        encodeText
 * purpose:     make a binary string of the characters in the given text using
 *              the character codes made previously
 * arguments:   the file to read from
 * returns:     the encoded string
 */
string HuffmanCoder::encodeText(istream &text) {
    string encoding = "";
    char c;
    while(text.get(c)) {
        //lookup character's code in codeMap and add to encoding
        encoding += codeMap[c];
    }
    return encoding;
}

/* name:        serializeTree
 * purpose:     serialize the tree pointed to in the input
 * arguments:   a pointer to a Huffman tree
 * returns:     the serialized version of the tree
 * NOTE:        function copied from phaseOne.cpp
 */
string HuffmanCoder::serializeTree(HuffmanTreeNode *root) {
    //make string to apphend to
    string tree = "";

    //if internal node, add I to string, do left, then right
    if (not root->isLeaf()) {
        tree += "I";
        tree += serializeTree(root->get_left());
        tree += serializeTree(root->get_right());
    } else {
        //node is leaf, so add L and node's value
        tree += "L";
        tree += root->get_val();
    }

    return tree;
}

/* name:        deserializeTree
 * purpose:     given a serialized tree, reconstruct the Huffman tree and
 *              return a pointer to its root by calling a helper function
 * arguments:   the serialized tree to deserialize
 * returns:     a pointer to the deserialized tree's root
 * effects:     deserializes the given tree
 * NOTE:        copied from phaseOne.cpp
 */
HuffmanTreeNode *HuffmanCoder::deserializeTree(string serial_tree) {
    //make serialized string into stringstream
    istringstream stream(serial_tree);

    //call helper funtion
    HuffmanTreeNode *root = deserializeHelper(stream);

    return root;
}

/* name:        deserializeHelper
 * purpose:     reconstruct the Huffman tree from the provided stringstream
 *              containing the tree's serialization
 * arguments:   a reference to a stringstream
 * returns:     a pointer to the tree's root
 * effects:     makes a new Huffman Tree and it's nodes
 * NOTE:        copied from phaseOne.cpp
 */
HuffmanTreeNode *HuffmanCoder::deserializeHelper(istream &tree) {
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
        node->set_left(deserializeHelper(tree));

        //call on right subtree
        node->set_right(deserializeHelper(tree));

    //if leaf node, make the node with the necessary value
    } else {
        tree.get(letter);
        node = new HuffmanTreeNode(letter, FREQ);
    }

    return node;
}

/* name:        decode
 * purpose:     decode the encoded binary string using the Huffman Tree passed
 *              in; return the decoded message
 * arguments:   the encoded binary string and the root to the Huffman Tree
 * returns:     the decoded string
 */
string HuffmanCoder::decode(string encoding, HuffmanTreeNode *node) {
    istringstream stream(encoding);
    char c;
    string message = "";
    HuffmanTreeNode *curr = node;
    while (stream.get(c)) {
        if (c == '0') {
            curr = curr->get_left();
        } else {
            curr = curr->get_right();
        }
        if (curr->isLeaf()) {
            message += curr->get_val();
            curr = node;
        }
    }
    if (curr != node) {
        throw runtime_error("Encoding did not match Huffman tree.");
    }
    return message;
}