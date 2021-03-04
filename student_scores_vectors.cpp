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
using std::vector;


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



void calculate_scores(vector<Students>& students, unsigned option)
{
    for (auto &student : students) {

        if (student.scores.empty())
            continue;

        // Calculating average
        if (option == 1) {

            float average = 0;
            for (auto &score : student.scores) {
                average += score;    
            }
            average /= student.scores.size();

            student.final_score = 0.4 * average + 0.6 * student.test_score;
        }
        // Calculating median
        else {

            float median;
            auto mid = student.scores.begin() + student.scores.size() / 2;
            std::sort(student.scores.begin(), student.scores.end());
            if (student.scores.size() % 2 == 0) {
                //unsigned mid = student.scores.size() / 2;
                //median = ((float)student.scores[mid] + (float)student.scores[mid - 1]) / 2;
                auto mid = student.scores.begin() + student.scores.size() / 2;
                median = ((float)*mid + (float)*(mid - 1)) / 2;
            }            
            else {
                    median = *mid;
            }
            student.final_score = 0.4 * median + 0.6 * student.test_score;
        }
    }
}


void print_students(const vector<Students>& students, int option)
{
    printf("\n%-20s%-20s%-20s\n", "Pavarde", "Vardas", 
            (option == 1) ? "Galutinis (Vid.)" : "Galutinis (Med.)");

    string temp(55, '-');
    cout << temp << endl;
    for (const auto& student : students) {

        if (student.scores.empty())
            continue;

        printf("%-20s%-20s%-20.2f\n", student.last_name.c_str(), student.first_name.c_str(),
                                        student.final_score);
    }

    cout << endl;
}


unsigned generate_random_score()
{
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(1, 10);

    return dist(mt);
}
