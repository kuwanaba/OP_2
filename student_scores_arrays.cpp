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
#include <algorithm>


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



void calculate_scores(Students students[], std::size_t array_size, unsigned option)
{
    for (std::size_t i{}; i != array_size; i++) {

        // Calculating average
        if (option == 1) {

            float average = 0;
            for (std::size_t j{}; j != students[i].score_count; j++) {
                average += students[i].scores[j];    
            }
            average /= students[i].score_count;

            students[i].final_score = 0.4 * average + 0.6 * students[i].test_score;
        }
        // Calculating median
        else {

            float median;
            std::sort(students[i].scores, students[i].scores + array_size);
            if (array_size % 2 == 0) {
                median = ((float)students[i].scores[array_size / 2] +
                        (float)students[i].scores[array_size / 2 - 1]) / 2;
            }            
            else {
                    median = students[i].scores[array_size / 2]; 
            }
            students[i].final_score = 0.4 * median + 0.6 * students[i].test_score;
        }
    }
}


void print_students(const Students students[], std::size_t array_size)
{
    cout << endl;
    cout << setw(20) << left << "Pavarde";
    cout << setw(20) << left << "Vardas";
    cout << setw(20) << left << "Galutinis (Vid.)" << endl;

    string temp(55, '-');
    cout << temp << endl;
    for (std::size_t i{}; i != array_size; i++) {
        cout << setw(20) << left << students[i].first_name;
        cout << setw(20) << left << students[i].last_name;
        cout << setw(20) << left << students[i].final_score;
        cout << endl;
    }

    cout << endl;
}
