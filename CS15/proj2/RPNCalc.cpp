/*
 * RPNCalc.cpp
 * CS 15 Project 2: CalcYouLater
 * Eleanor Elkus (eelkus01)
 * Date Created: 2/25/23
 *
 * Purpose: Implementat a version of the RPNCalc class; implementing from the
 *          RPNCalc.h header file. The calculator can be run and provided
 *          calculation commands can be handled.
 *
 */

#include "RPNCalc.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* 
 * name:        default constructor
 * purpose:     initialize the RPNCalc object
 * arguments:   none
 * returns:     none
 * effects:     
 */
RPNCalc::RPNCalc() {
}

/* 
 * name:        default destructor
 * purpose:     destroy heap-allocated memory associated with RPNCalc objects
 * arguments:   none
 * returns:     none
 */
RPNCalc::~RPNCalc() {
}

/* 
 * name:        run
 * purpose:     call the function to start reading in commands and print the
 *              closing statement to cerr; catch any thrown errors
 * arguments:   none
 * returns:     none
 */
void RPNCalc::run() {
    try {
        readMove(cin);
        cerr << "Thank you for using CalcYouLater." << endl;
    }
    catch (const runtime_error &e) {
        cerr << "Error: " << e.what() << endl;
        run();
    }
}

/*
 * name:        readMove
 * purpose:     read in commands from cin and call necessary functions to
 *              handle the commands; do this until end of input is reached or
 *              until "quit" is read in
 * arguments:   the input stream to read from
 * returns:     none
 */
void RPNCalc::readMove(std::istream &input) {
    std::string move;
    int value;
    input >> move;
    while ((not input.fail()) and move != "quit") {
        if (got_int(move, &value)) {
            stack.push(Datum(value));
        } else if (move == "#t" or move == "#f") {
            do_bool(move);
        } else if (move == "print") {
            cout << stack.top().toString() << endl;
        } else if (move == "not") {
            do_not();
        } else if (move == "drop") {
            stack.pop();
        } else if (move == "clear") {
            stack.clear();
        } else if (move == "dup") {
            stack.push(Datum(stack.top()));
        } else if (move == "swap") {
            do_swap();
        } else if (move == "+" or move == "-" or move == "*"
                   or move == "/" or move == "mod") {
            do_arith_ops(move);
        } else if (move == "<" or move == ">" or move == "<=" or move == ">="){
            do_comp_ops(move);
        } else if (move == "==") {
            do_equal();
        } else if (move == "{") {
            do_rstring(input);
        } else if (move == "if") {
            do_if();
        } else if (move == "exec") {
            do_exec();
        } else if (move == "file") {
            do_file();
        } else {
            cerr << move << ": unimplemented\n";
        }
        //read in next move
        input >> move;
    }
}

/* 
 * name:        got_int
 * purpose:     determine whether a string can be interpreted as an integer
 * arguments:   the string to check and the place to put the value (if it is an
 *              integer)
 * returns:     a bool that is true if the string is an int and false if not
 * note:        function was copied from got_int.cpp
 */
bool RPNCalc::got_int(std::string s, int *resultp) {
    char extra;
    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/* 
 * name:        do_bool
 * purpose:     push a bool Datum with the given value onto the stack
 * arguments:   the bool to push on the stack
 * returns:     none
 * effects:     stack is updated with given bool Datum on top
 */
void RPNCalc::do_bool(std::string val) {
    if (val == "#t") {
        stack.push(Datum(true));
    } else {
        stack.push(Datum(false));
    }
}

/* 
 * name:        do_not
 * purpose:     read and pop the top element off the stack; if not a bool,
 *              print error; if a bool, make Datum with opposite bool value
 *              and push onto stack
 * arguments:   none
 * returns:     none
 * effects:     puts opposite bool onto stack if applicable
 */
void RPNCalc::do_not() {
    //check if bool
    if ( not stack.top().isBool()) {
        throw runtime_error("datum_not_bool");
    }

    Datum top = get_top();

    //update top value
    if (top.getBool()) {
        Datum f(false);
        top = f;
    } else {
        Datum t(true);
        top = t;
    }
    stack.push(top);
}

/* 
 * name:        do_swap
 * purpose:     swaps the top two elements on the stack; prints error if not
 *              enough elements on stack
 * arguments:   none
 * returns:     none
 */
void RPNCalc::do_swap() {
    //check size of stack
    check_size(2);

    //swap top two elems
    Datum top = get_top();
    Datum next = get_top();
    stack.push(top);
    stack.push(next);
}

/* 
 * name:        do_arith_ops
 * purpose:     pop the top two elements off stack, perform the given operation
 *              and pop the result on the stack; if elements aren't ints, throw
 *              error; if not enough elements on stack, print error
 * arguments:   the operation to perform
 * returns:     none
 * effects:     int result pushed on stack
 */
void RPNCalc::do_arith_ops(std::string op) {
    //check enough elements
    check_size(2);

    //get top two elems
    Datum second = get_top();
    Datum first = get_top();

    //check if ints
    if (not first.isInt() or not second.isInt()) {
        throw runtime_error("datum_not_int");
    }

    //do operation
    if (op == "+") {
        stack.push(Datum(first.getInt() + second.getInt()));
    } else if (op == "-") {
        stack.push(Datum(first.getInt() - second.getInt()));
    } else if (op == "*") {
        stack.push(Datum(first.getInt() * second.getInt()));
    } else if (op == "/") {
        stack.push(Datum(first.getInt() / second.getInt()));
    } else if (op == "mod") {
        stack.push(Datum(first.getInt() % second.getInt()));
    }
}

/* 
 * name:        do_comp_ops
 * purpose:     pop the top two elements off stack, perform the given operation
 *              and pop a Datum bool with result onto stack (elements MUST be
 *              ints for all these comparisons)
 * arguments:   the comparison operation to perform
 * returns:     none
 * effects:     bool pushed on stack
 */
void RPNCalc::do_comp_ops(std::string op) {
    //check enough elements
    check_size(2);

    //get top two elems
    Datum second = get_top();
    Datum first = get_top();

    //check if ints
    if (not first.isInt() or not second.isInt()) {
        throw runtime_error("datum_not_int");
    }

    //do comparison
    if (op == "<") {
        stack.push(Datum(first.getInt() < second.getInt()));
    } else if (op == ">") {
        stack.push(Datum(first.getInt() > second.getInt()));
    } else if (op == "<=") {
        stack.push(Datum(first.getInt() <= second.getInt()));
    } else if (op == ">=") {
        stack.push(Datum(first.getInt() >= second.getInt()));
    }

}

/* 
 * name:        do_equal
 * purpose:     pop the top two elements off stack, check if equal (same type
 *              and value), and pop result on stack
 * arguments:   none
 * returns:     none
 * effects:     bool pushed on stack
 */
void RPNCalc::do_equal() {
    //check enough elements
    check_size(2);

    //perform comparison
    Datum second = get_top();
    Datum first = get_top();
    stack.push(Datum(first.toString() == second.toString()));
}

/* 
 * name:        do_rstring
 * purpose:     make a rstring Datum with the rstring read in and push on stack
 * arguments:   the input stream to read from
 * returns:     none
 * effects:     new rstring Datum pushed on stack
 */
void RPNCalc::do_rstring(std::istream &input) {
    //get the rest of the rstring and store in string
    std::string str;
    std::string toAdd;
    int backCount = 0;
    int frontCount = 1;
    input >> toAdd;
    if (toAdd == "}") backCount++;
    if (toAdd == "{") frontCount++;
    while (not input.fail() and frontCount != backCount) {
        str = str + " " + toAdd;
        input >> toAdd;
        if (toAdd == "}") backCount++;
        if (toAdd == "{") frontCount++;
    }
    str += " }";

    //pass string into parseRString using stringstream
    std::istringstream iss(str);
    stack.push(Datum(parseRString(iss)));
}

/* 
 * name:        do_exec
 * purpose:     processes top element of stack (rstring); if top element isn't
 *              an rstring, send an error
 * arguments:   none
 * returns:     none
 * effects:     pops top element off stack and pushes on result
 */
void RPNCalc::do_exec() {
    //check if rstring
    if (stack.top().isRString()) {
        //get the substring that's within the curly braces
        std::string str = stack.top().getRString();
        str = str.substr(2, str.length() - 4);
        stack.pop();

        //make stringstream
        std::istringstream iss(str);
        while (not iss.fail()) {
            readMove(iss);
        }
    } else {
        cerr << "Error: cannot execute non rstring\n";
    }
}

/* 
 * name:        do_if
 * purpose:     pop an rstring off stack to be executed if condition is false;
 *              pop another rstring off stack to be executed if condition is
 *              true; pop a bool off stack as the condition to test
 * arguments:   none
 * returns:     none
 * effects:     pops off top three elements from stack and pushes on result
 */
void RPNCalc::do_if() {
    std::string falseCase, trueCase;
    bool test;
    //check if stack has enough elements
    check_size(3);
    //get true and false case rstrings and bool test condition
    if (stack.top().isRString()) {
        falseCase = get_top().getRString();
    } else {
        pop_and_print(3, "Error: expected rstring in if branch\n");
        return;
    }
    if (stack.top().isRString()) {
        trueCase = get_top().getRString();
    } else {
        pop_and_print(2, "Error: expected rstring in if branch\n");
        return;
    }
    if (stack.top().isBool()) {
        test = get_top().getBool();
    } else {
        pop_and_print(1, "Error: expected boolean in if test\n");
        return;
    }
    if (test) { //execute trueCase
        stack.push(Datum(trueCase));
        do_exec();
    } else { //execute falseCase
        stack.push(Datum(falseCase));
        do_exec();
    }
}

/* 
 * name:        do_file
 * purpose:     pop top element off stack (print error if not rstring); read
 *              and process name of file in rstring; send error if unable to
 *              open or read file
 * arguments:   none
 * returns:     none
 * effects:     pops top element and processes file (might pop elements on
 *              stack if specified in file)
 */
void RPNCalc::do_file() {
    //make sure top is rstring
    if (stack.top().isRString()) {
        std::string filename = get_top().getRString();

        //update filename to be substring within curly braces
        filename = filename.substr(2, filename.length() - 4);

        //make filestream and open
        ifstream input;
        input.open(filename);

        //check file opened correctly
        if (not input.is_open()) {
            cerr << "Unable to read " << filename << endl;
            return;
        }

        readMove(input);

    } else {
        cerr << "Error: file operand not rstring\n";
    }
}

/* 
 * name:        check_size
 * purpose:     check that the size of the stack is the same as the given size;
 *              if not, throw an error
 * arguments:   the size to compare
 * returns:     none
 */
void RPNCalc::check_size(int size) {
    if (stack.size() < size) {
        stack.clear();
        throw runtime_error("empty_stack");
    }
}

/* 
 * name:        get_top
 * purpose:     pops the top element on the stack and returns it
 * arguments:   none
 * returns:     the top element on the stack
 * effects:     pops top element of stack
 */
Datum RPNCalc::get_top() {
    Datum top = stack.top();
    stack.pop();
    return top;
}

/* 
 * name:        pop_and_print
 * purpose:     pop the specified number of elements off the stack and print a
 *              message to cerr
 * arguments:   the message to print to cerr and the number of elements to pop
 * returns:     none
 * effects:     stack is reduced by specified number
 */
void RPNCalc::pop_and_print(int num, std::string message) {
    for (int i = 0; i < num; i++) {
        stack.pop();
    }
    cerr << message;
}
