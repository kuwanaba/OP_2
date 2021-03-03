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
}; 


bool is_valid_string(const std::string& foo);
void print_students(const Students students[], std::size_t array_size);
#endif