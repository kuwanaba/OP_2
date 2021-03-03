/*
 * =====================================================================================
 *
 *       Filename:  student_scores_arrays.cpp
 *
 *    Description:  Functions defined for the students scores program
 *
 *        Version:  1.0
 *        Created:  2021-03-02 22:25:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dominykas Makūnas
 *
 * =====================================================================================
 */

#include "student_scores.h"


#include <string>
#include <cctype>
#include <iostream>
#include <iomanip>


using std::cout;
using std::endl;
using std::setw;
using std::left;


bool is_valid_string(const std::string& foo)
{
    bool valid = true;    

    if (foo.length() == 0)
        return false;

    for (std::size_t i{}; i < foo.length() && valid; i++) {
       if (!(std::isalpha(foo[i]) || std::isspace(foo[i]))) {
              valid = false; 
       }
    } 
    
    return valid;
}



bool is_valid_score(int grade)
{
    if (0 < grade && grade <= 10)
        return true;

    return false;
}


void print_students(const Students students[], std::size_t array_size)
{
    cout << endl;
    cout << setw(15) << left << "Pavardė";
    cout << setw(15) << left << "Vardas";
    cout << "Galutinis (Vid.)" << endl;

    string temp(45, '-');
    cout << temp << endl;
    for (std::size_t i{}; i != array_size; i++) {
        cout << setw(15) << left << students[i].first_name; 
        cout << setw(15) << left << students[i].last_name; 
        cout << setw(15) << left << students[i].final_score;
        cout << endl;
    }

    cout << endl;
}
