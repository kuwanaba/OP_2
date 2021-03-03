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


bool is_valid_string(const std::string& foo)
{
    bool valid = true;    

    for (std::size_t i{}; i < foo.length() && valid; i++) {
       if (!(std::isalpha(foo[i]) || std::isspace(foo[i]))) {
              valid = false; 
       }
    } 
    
    return valid;
}


void print_students(const Students students[], std::size_t array_size)
{
    for (std::size_t i{}; i != array_size; i++) {
        std::cout << students[i].first_name << " " << students[i].last_name << std::endl;
    }
}
