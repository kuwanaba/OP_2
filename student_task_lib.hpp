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
#include <fstream>


using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::string;


struct Student {                                                               
    string first_name;                                                          
    string last_name;                                                           

    vector<unsigned> scores;

    // Egzam score
    unsigned test_score;

    // Final score of the whole subject
    float final_score;
}; 


bool is_valid_string(const string& foo);
void print_students(const vector<Student>& students, int option);
bool is_valid_score(int grade);
void calculate_scores(vector<Student>& students, unsigned option);
unsigned generate_random_score();
bool compare_by_first_letter(const Student &a, const Student &b);


#endif
