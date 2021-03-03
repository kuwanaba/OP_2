/*
 * =====================================================================================
 *
 *       Filename:  headers.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021-03-02 20:14:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef STUDENT_SCORES_H
#define STUDENT_SCORES_H


#include <string>

using std::string;


struct Students {                                                               
    string first_name;                                                          
    string last_name;                                                           

    int scores[10];                                                             
    int score_count;

    // Egzam score
    int test_score;

    // Final score of the whole subject
    float final_score;
}; 


bool is_valid_string(const std::string& foo);
void print_students(const Students students[], std::size_t array_size, int option);
bool is_valid_score(int grade);
void calculate_scores(Students students[], std::size_t array_size, unsigned option);
void generate_random_scores(Students& student, unsigned num_of_scores);


#endif
