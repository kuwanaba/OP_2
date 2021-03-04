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

#include "student_scores.hpp"


#include <string>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstdio>
#include <random>
#include <chrono>


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


        if (students[i].score_count == 0)
            continue;

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


void print_students(const Students students[], std::size_t array_size, int option)
{
    printf("\n%-20s%-20s%-20s\n", "Pavarde", "Vardas", 
            (option == 1) ? "Galutinis (Vid.)" : "Galutinis (Med.)");

    string temp(55, '-');
    cout << temp << endl;
    for (std::size_t i{}; i != array_size; i++) {

        if (students[i].score_count == 0)
            continue;

        printf("%-20s%-20s%-20.2f\n", students[i].last_name.c_str(), students[i].first_name.c_str(),
                                        students[i].final_score);
    }

    cout << endl;
}


void generate_random_scores(Students& student, unsigned num_of_scores)
{
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(1, 10);

    cout << "\nSugeneruoti pažymiai:\nNamų darbai: ";
    for (int i{}; i < num_of_scores - 1; i++) {
        student.scores[i] = dist(mt);
        cout << student.scores[i] << " ";
    }

    cout << "\nEgzaminas: ";
    student.test_score = dist(mt);
    cout << student.test_score << endl;
}
