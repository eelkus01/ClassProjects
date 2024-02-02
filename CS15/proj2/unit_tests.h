/*
 * unit_tests.h
 * CS 15 Project 2: CalcYouLater
 * Eleanor Elkus (eelkus01)
 * Date Created: 2/25/23
 *
 * Purpose: A file containing all of the tests used to check the functionality
 *          and correctness of the various classes involved in the CalcYouLater
 *          program.
 *
 */

#include "DatumStack.h"
#include "Datum.h"
#include "parser.h"
#include <cassert>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;


/* DATUMSTACK TESTS */

/*
 * DatumStack default constructor test
 * Make sure no fatal errors/memory leaks in default constructor for DatumStack
 */
void dsConstructorTest() {
    DatumStack test;
    assert(test.size() == 0);
}

/*
 * DatumStack destructor test
 * Destructor called implicitly; make sure no fatal errors
 */
void dsDestructorTest() {
    DatumStack test;
}

/*
 * DatumStack array constructor test
 * Make sure no fatal error/memory leaks in array constructor (and check
 * elements are correct)
 */
void dsArrConstrucTest() {
    Datum data[2] = { Datum(5), Datum(true) };
    DatumStack test(data, 2);
    assert(test.size() == 2);
    //assert(test.print() == "#t5");
}

/*
 * DatumStack size test
 * Make sure size returns the correct number
 */
void dsSizeTest() {
    DatumStack test;
    assert(test.size() == 0);
    // add elements and retest size
    Datum data(67);
    Datum moreData(890);
    Datum lastData(4);
    test.push(data);
    test.push(moreData);
    test.push(lastData);
    assert(test.size() == 3);
}

/*
 * DatumStack isEmpty test
 * Make sure isEmpty returns true only on an empty stack
 */
void dsEmptyTest() {
    DatumStack test;
    assert(test.isEmpty());
    //add elements and make sure it returns false
    Datum data(2);
    test.push(data);
    assert(not test.isEmpty());
}

//MADE PRIVATE AFTER TESTING BC IT'S A PRIVATE FUNCTION//
//NOTE: ALL OTHER CALLS TO PRINT WERE MADE PRIVATE TOO//
// /*
//  * DatumStack print test
//  * Test that print works correctly; print function only made for testing
//  */
// void dsPrintTest() {
//     DatumStack test;
//     Datum data(12);
//     test.push(data);
//     assert(test.print() == "12");
//     Datum moreData(57);
//     test.push(moreData);
//     assert(test.print() == "5712");
//     Datum more(3);
//     test.push(more);
//     assert(test.print() == "35712");
// }

/*
 * DatumStack push test
 * Test push; size should increase by 1; stack should be updated properly
 */
void dsPushTest() {
    DatumStack test;
    Datum data(4);
    Datum data2(3);
    Datum data3(2);
    test.push(data);
    test.push(data2);
    test.push(data3);
    assert(test.size() == 3);
    //assert(test.print() == "234");
}

/*
 * DatumStack top test
 * Test that top returns the correct element
 */
void dsTopTest() {
    DatumStack test;
    Datum data(1);
    Datum data2(2);
    test.push(data);
    test.push(data2);
    assert(test.top().toString() == "2");
}

/*
 * DatumStack top empty test
 * Test that top throws the correct error message when called on empty stack
 */
void dsTopEmptyTest() {
    DatumStack test;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try {
        test.top();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

/*
 * DatumStack pop test
 * Test that pop correctly removes the top element
 */
void dsPopTest() {
    DatumStack test;
    Datum data(1);
    Datum data2(2);
    test.push(data);
    test.push(data2);
    test.pop();
    assert(test.top().toString() == "1");
    assert(test.size() == 1);
}

/*
 * DatumStack pop empty test
 * Test that pop throws the correct error message when called on empty stack
 */
void dsPopEmptyTest() {
    DatumStack test;
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try {
        test.pop();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

/*
 * DatumStack clear test
 * Test that clear correctly makes the stack empty
 */
void dsClearTest() {
    DatumStack test;
    Datum data(1);
    Datum data2(2);
    test.push(data);
    test.push(data2);
    test.clear();
    assert(test.isEmpty());
    //assert(test.print() == "");
}


/* PARSERSTRING TESTS */

/*
 * parseRString test 1
 * Test passing in simple valid input to parseRString
 */
void parseTest1() {
    //make a string to pass into the stream
    //assume first { was already read in
    std::string str(" 1 2 + }");
    istringstream my_stream(str);

    //make sure function returns expected string and spacing
    assert(parseRString(my_stream) == "{ 1 2 + }");
}

/*
 * parseRString test 2
 * Test passing in simple invalid input to parseRString (test error throwing)
 */
void parseTest2() {
    //make a string to pass into the stream
    //assume first { was read, but make an invalid brace arrangement
    std::string str(" 1 2 + ");
    istringstream my_stream(str);
    //CATCH ERROR
    bool runtime_error_thrown = false;
    std::string error_message = "";
    try {
        parseRString(my_stream);
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "invalid_input");
}

/*
 * parseRString test 3
 * Test passing in more complicated valid input to parseRString
 */
void parseTest3() {
    //make a string to pass into the stream
    //assume first { was already read in
    std::string str(" 1 { 4 2 / } / }");
    istringstream my_stream(str);

    //make sure function returns expected string and spacing
    assert(parseRString(my_stream) == "{ 1 { 4 2 / } / }");
}

/*
 * parseRString test 4
 * Test passing in more complicated input to parseRString (should delete
 * anything after final closing brace)
 */
void parseTest4() {
    //make a string to pass into the stream
    //assume first { was already read in
    std::string str(" 1 1 + } 42 ");
    istringstream my_stream(str);

    //make sure function returns expected string and spacing
    assert(parseRString(my_stream) == "{ 1 1 + }");
}

/*
 * parseRString test 5
 * Test passing in more complicated input to parseRString (should delete
 * anything after final closing brace)
 */
void parseTest5() {
    //make a string to pass into the stream
    //assume first { was already read in
    std::string str(" 1 1 + } } } } } ");
    istringstream my_stream(str);

    //make sure function returns expected string and spacing
    assert(parseRString(my_stream) == "{ 1 1 + }");
}