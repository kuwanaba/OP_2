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


#include <list>
#include <deque>
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
using std::list;
using std::deque;


struct Student {                                                               
    string first_name;                                                          
    string last_name;                                                           

    vector<int> scores;

    // Egzam score
    int test_score;

    // Final score of the whole subject
    float final_score_avg;
    float final_score_med;
}; 


bool is_valid_string(const string& foo);
bool is_valid_score(int grade);


void calculate_finals(Student &student);
int generate_random_score();
Student generate_random_student(int num_of_scores);


void generate_student_vector(vector<Student> &students, int student_amount, int num_of_scores);
void generate_student_list(list<Student> &students, int student_amount, int num_of_scores);
void generate_student_deque(deque<Student> &students, int student_amount, int num_of_scores);


bool compare_by_final_avg(const Student &a, const Student &b);
bool compare_by_final_med(const Student &a, const Student &b);


void print_students_vector(const vector<Student> &students);
void print_students_list(const list<Student> &students);
void print_students_deque(const deque<Student> &students);


void read_students_vector_from_file(vector<Student>& students, string file_name);
void write_students_vector_to_file(const vector<Student>& students, string file_name);


void read_students_list_from_file(list<Student>& students, string file_name);
void write_students_list_to_file(const list<Student>& students, string file_name);


void read_students_deque_from_file(deque<Student>& students, string file_name);
void write_students_deque_to_file(const deque<Student>& students, string file_name);
#endif
