/*
 * =====================================================================================
 *
 *       Filename:  student_scores.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021-03-02 20:14:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dominykas Makūnas
 *
 * =====================================================================================
 */

#ifndef STUDENT_SCORES_HPP
#define STUDENT_SCORES_HPP


#include <vector>
#include <string>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdio>
#include <random>
#include <chrono>


struct Students {                                                               
    std::string first_name;                                                          
    std::string last_name;                                                           

    std::vector<unsigned> scores;

    // Egzam score
    unsigned test_score;

    // Final score of the whole subject
    float final_score;
}; 


bool is_valid_string(const std::string& foo);
void print_students(const std::vector<Students>& students, int option);
bool is_valid_score(int grade);
void calculate_scores(std::vector<Students>& students, unsigned option);
unsigned generate_random_score();


#endif
