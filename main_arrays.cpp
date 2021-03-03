/*
 * =====================================================================================
 *
 *       Filename:  main_arrays.cpp
 *
 *    Description:  Program to input student names with scores and calculate
 *    their finals
 *
 *        Version:  0.1v
 *        Created:  2021-03-02 20:03:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dominykas Makūnas
 *
 * =====================================================================================
 */

// TODO: Finish up the data input
#include <iostream>


#include "student_scores.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;




int main(void)
{
     
    Students students[10];
    
    bool inputing_data = true;
    unsigned student_iterator = 0;
    while (inputing_data) {

        cout << "Jei norite baigti įvedimą įveskite 'x'\n";
        cout << "Įveskite studento vardą: "; 

        do {
            string foo;
            getline(cin, foo);

            if (is_valid_string(foo)) {

                // Checking to see if user indicate end of student input
                if (tolower(foo[0]) == 'x') {
                    inputing_data = false;
                    break;
                }
                students[student_iterator].first_name = foo;
                break;

            } else {
                cout << "Neteisingai įvestas vardas, bandykite dar kartelį: ";
            }

        } while (true);


        // End of student info input
        if (!inputing_data)
            break;

        cout << "Įveskite studento pavardę: "; 
        do {
            string foo;
            getline(cin, foo);

            if (is_valid_string(foo)) {
                students[student_iterator++].last_name = foo;
                break;

            } else {
                cout << "Neteisingai įvesta pavardė, bandykite dar kartelį: ";
            }

        } while (true);



        //---------------------------------------------------------------------
        // Inputting studet scores


        
    } 

    print_students(students, student_iterator);

    return 0;
}
