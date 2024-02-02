/*
 * RPNCalc.h
 * CS 15 Project 2: CalcYouLater
 * Eleanor Elkus (eelkus01)
 * Date Created: 2/25/23
 *
 * Purpose: Interface of the RPNCalc class. The calculator can be run.
 *
 */

#ifndef RPNCALC_H_
#define RPNCALC_H_

#include "DatumStack.h"
#include "parser.h"
#include <iostream>

class RPNCalc {
public:
    //constructor
    RPNCalc();

    //destructor
    ~RPNCalc();

    void run();

private:
    //all other functions and variables here
    DatumStack stack;
    void readMove(std::istream &input);
    bool got_int(std::string s, int *resultp);
    void do_bool(std::string val);
    void do_not();
    void do_swap();
    void do_arith_ops(std::string op);
    void do_comp_ops(std::string op);
    void do_equal();
    void do_rstring(std::istream &input);
    void do_if();
    void do_exec();
    void do_file();
    void check_size(int size);
    Datum get_top();
    void pop_and_print(int num, std::string message);

};

#endif