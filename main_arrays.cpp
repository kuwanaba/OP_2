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

// TODO: Modify the program to react to empty new lines and output a '-' everytime


#include <iostream>


#include "student_scores.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;




int main(void)
{
     
    Students *students;
    unsigned array_size = 10;
    students = new Students[array_size];

    unsigned score_array_size = 10;
    for (int i{}; i < array_size; i++)
        students[i].scores = new unsigned[score_array_size];
    
    bool inputing_data = true;
    size_t student_iterator = 0;
    while (inputing_data) {

        cout << "Jei norite baigti įvedimą įveskite 'x'\n";
        cout << "Įveskite studento vardą.\n"; 
        cout << " - ";

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
                cout << "\nNeteisingai įvestas vardas, bandykite dar kartelį.\n";
                cout << " - ";
            }

        } while (true);


        // End of student info input
        if (!inputing_data)
            break;

        cout << "\nĮveskite studento pavardę\n"; 
        cout << " - ";
        do {
            string foo;
            getline(cin, foo);

            if (is_valid_string(foo)) {
                students[student_iterator].last_name = foo;
                break;

            } else {
                cout << "\nNeteisingai įvesta pavardė, bandykite dar kartelį.\n";
                cout << " - ";
            }

        } while (true);



        //---------------------------------------------------------------------
        // Inputting student scores


        cout << "\nAr norite sugeneruoti pažymius atsitiktinai?(y/n).\n";
        cout << " - ";
        string selection;
        cin >> selection;
        while (selection != "y" && selection != "n") {
            cout << "\nBandykite dar kartą.\n";
            cout << " - ";
            cin.clear();
            cin.ignore(10000, '\n');

            cin >> selection;
        }

        if (selection == "y") {
            

            cout << "\nKiek norite skaičių sugeneruoti (nuo 1 iki 10)?\n";
            cout << " - "; 


            unsigned amount;
            while (!(cin >> amount) || (1 > amount && amount <= 10)) {

                cout << "\nNeteisingai įvestas kiekis.\n";
                cout << " - ";
                cin.clear();
                cin.ignore(10000, '\n');
            }  
             
            generate_random_scores(students[student_iterator], amount);
            students[student_iterator].score_count = amount - 1;
        } 

        else {

            cout << "\nJei norite baigti įvedimą įveskite '-1'\n";
            cout << "Įveskite namu darbų rezultatus.\n";

            int score;
            size_t score_count = 0;
            while (true) {
                

                cout << " - ";
                while (!(cin >> score)) {

                    cout << "\nNeteisingai įvestas pažymys.\n";
                    cout << " - ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }  

                if (score == -1) {
                    break;
                }
                else if (0 < score && score <= 10) {

                    if (score_count + 1 > score_array_size)
                        students[student_iterator].scores = new unsigned[score_array_size += 10];

                    students[student_iterator].scores[score_count++] = score;
                }
                else {

                    cout << "\nNeteisingai įvestas pažymys.\n";
                    cout << " - ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            students[student_iterator].score_count = score_count;



            // If no values were inputted for a student skip the test score
            if (students[student_iterator].score_count == 0)
                break;

            cout << "\nĮveskite egzamino rezultatą.\n";
            while (true) {

                cout << " - ";
                while (!(cin >> score) || !(0 < score && score <= 10)) {

                    cout << "\nNeteisingai įvestas pažymys.\n";
                    cout << " - ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }  

                students[student_iterator].test_score = score;
                break;
            }
        }


        cin.clear();
        cin.ignore(10000, '\n');
        
        // Dinamically increase the size of the Student array if needed
        if (student_iterator + 1 > array_size)
           students = new Students[array_size += 10]; 
        
        student_iterator++;
        cout << endl;
    } 

    //------------------------------------------------------------------------
    // Calculating averages

    cout << "\nAr norite skaičiuoti vidurkį(1) ar medianą(2)?\n";
    cout << " - ";
    unsigned option;
    while (!(cin >> option)) {
        cout << "\nĮveskite arba 1 arba 2.\n";
        cout << " - ";        
        cin.clear();
        cin.ignore(10000, '\n');
    }
    
    cout << endl;
    calculate_scores(students, student_iterator, option);
    print_students(students, student_iterator, option);

    return 0;
}
