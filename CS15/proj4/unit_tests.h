/*
 * unit_tests.h
 * CS 15 Project 4: gerp
 * Eleanor Elkus (eelkus01) Talia Tepper (tteppe01)
 * Date Created: 4/13/23
 *
 * Purpose: A file containing all of the tests used to check the functionality
 *          and correctness of the various classes and functions involved in
 *          the gerp program.
 *
 */

#include "stringProcessing.h"
#include <sstream>
#include <cassert>
#include <iostream>

using namespace std;

/* stringTest
 * Test that stringProcessing works on simple input
 */
void stringTest() {
    string str("simple");
    assert(stripNonAlphaNum(str) == "simple");
}

/* stringTest2
 * Test that stringProcessing works on a varied alphanum input
 */
void stringTest2() {
    string str("6969696969gng6969696420");
    assert(stripNonAlphaNum(str) == "6969696969gng6969696420");
}

/* stringTest3
 * Test that stringProcessing works on a input with non alphanum on edges
 */
void stringTest3() {
    string str("$#%^slimjim*(");
    assert(stripNonAlphaNum(str) == "slimjim");
}

/* stringTest4
 * Test that stringProcessing works on a input with non alphanum in middle
 */
void stringTest4() {
    string str("&&&&&4/14/23*(&^^&&");
    assert(stripNonAlphaNum(str) == "4/14/23");
}

/* stringTest5
 * Test that stringProcessing works on a input with only non alphanum
 */
void stringTest5() {
    string str("&&&&&*(&^^&&");
    assert(stripNonAlphaNum(str) == "");
}

/* stringTest6
 * Test that stringProcessing works on a input with only non alphanum
 */
void stringTest6() {
    string str("{.....");
    assert(stripNonAlphaNum(str) == "");
}
