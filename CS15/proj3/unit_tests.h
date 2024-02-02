/*
 * unit_tests.h
 * CS 15 Project 3: zap
 * Eleanor Elkus (eelkus01)
 * Date Created: 3/28/23
 *
 * Purpose: A file containing all of the tests used to check the functionality
 *          and correctness of the various classes and functions involved in
 *          the zap program.
 *
 */

#include "phaseOne.h"
#include "ZapUtil.h"
#include "HuffmanCoder.h"
#include <sstream>
#include <cassert>

using namespace std;

//PHASE ONE TESTS//
/* countTest
 * test the count_freqs function on some simple input w/ no repeats
 */
void countTest() {
    std::string str("simple");
    istringstream stream(str);
    count_freqs(stream);
}

/* countTest2
 * test the count_freqs function on a more difficult input
 */
void countTest2() {
    std::string str("A more tricky input but not so hard");
    istringstream stream(str);
    count_freqs(stream);
}

/* countTest3
 * test the count_freqs function on a input with new lines and punctuation
 */
void countTest3() {
    std::string str("I'm writing words\n and now more words!!! So many words ");
    str += "that now\n I\n don't\n know\n what\n to\n write, so the ";
    str += "end?&*$%^#$^&$%@#";
    istringstream stream(str);
    count_freqs(stream);
}

/* serializeTest
 * Test that serialize_tree works on a simple Huffman Tree
 * Use ZapUtil functions for testing purposes
 */
void serializeTest() {
    //make a tree using ZapUtil makeFigure1Tree
    const char INTERNAL_NODE_VAL = '\0';
    HuffmanTreeNode *fig1Tree = makeFigure1Tree(INTERNAL_NODE_VAL);
    assert(serialize_tree(fig1Tree) == "IIILaLbILeLfILcLd");

    // NOTE: commented out b/c deleteTree function is private
    // //recycle memory
    // HuffmanCoder code;
    // code.deleteTree(fig1Tree);
}

/* serializeTest2
 * Test serialize_tree function on a different Huffman tree (still simple)
 */
void serializeTest2() {
    HuffmanTreeNode *tree = new HuffmanTreeNode('\0', 36);
    tree->set_left(new HuffmanTreeNode('a', 16));
    tree->set_right(new HuffmanTreeNode('b', 20));
    assert(serialize_tree(tree) == "ILaLb");

    // NOTE: commented out b/c deleteTree function is private
    // //recycle memory
    // HuffmanCoder code;
    // code.deleteTree(tree);
}

/* deserializeTest
 * Test deserialize_tree on a simple tree of 1 parent and 2 children
 */
void deserializeTest() {
    std::string serialized = "ILaLb";
    HuffmanTreeNode *tree1 = deserialize_tree(serialized);

    //make the tree to compare to
    HuffmanTreeNode *tree2 = new HuffmanTreeNode('\0', 2);
    tree2->set_left(new HuffmanTreeNode('a', 1));
    tree2->set_right(new HuffmanTreeNode('b', 1));
    assert(treeEquals(tree1, tree2, false));

    // NOTE: commented out b/c deleteTree function is private
    // //recycle memory
    // HuffmanCoder code;
    // code.deleteTree(tree1);
    // code.deleteTree(tree2);
}

/* deserializeTest2
 * Test deserialize_tree on the serialization of figure one tree
 */
void deserializeTest2() {
    std::string serialized = "IIILaLbILeLfILcLd";
    HuffmanTreeNode *tree1 = deserialize_tree(serialized);

    //make the tree to compare to
    HuffmanTreeNode *tree2 = makeFigure1Tree('\0');
    assert(treeEquals(tree1, tree2, false));

    // NOTE: commented out b/c deleteTree function is private
    // //recycle memory
    // HuffmanCoder code;
    // code.deleteTree(tree1);
    // code.deleteTree(tree2);
}


//PHASE TWO TESTS//
//NOTE: commented out b/c functions were made private
/* buildTreeTest
 * Test that buildTree correctly builds a simple 3 node tree
 */
void buildTreeTest() {
    // HuffmanTreeNode *tree = new HuffmanTreeNode('\0', 2);
    // tree->set_left(new HuffmanTreeNode('a', 1));
    // tree->set_right(new HuffmanTreeNode('b', 1));
    // printTree(tree, '\0');

    // //make stringstream to read from
    // std::string str("ab");
    // istringstream stream(str);

    // //pass into functions
    // HuffmanCoder code;
    // code.countFreqs(stream);
    // HuffmanTreeNode *root = code.buildTree();
    // printTree(root, '\0');

    // assert(treeEquals(tree, root, true));

    // //recycle tree memory
    // delete tree->get_left();
    // delete tree->get_right();
    // delete tree;
}

/* codeTest
 * Test the function to generate character codes from a tree
 */
void codeTest() {
    // std::string code = "";
    // HuffmanCoder coder;
    // HuffmanTreeNode *tree = new HuffmanTreeNode('\0', 36);
    // tree->set_left(new HuffmanTreeNode('a', 16));
    // tree->set_right(new HuffmanTreeNode('b', 20));
    // coder.makeCodes(tree, code);
}

/* codeTest2
 * Test the function to generate character codes from a tree
 */
void codeTest2() {
    // std::string code = "";
    // HuffmanCoder coder;
    // HuffmanTreeNode *fig1 = makeFigure1Tree('\0');
    // coder.makeCodes(fig1, code);
}