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
// TODO: Define what happens when no scores are entered
// TODO: Clean up the identation of the output


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
    size_t student_iterator = 0;
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
                students[student_iterator].last_name = foo;
                break;

            } else {
                cout << "Neteisingai įvesta pavardė, bandykite dar kartelį: ";
            }

        } while (true);



        //---------------------------------------------------------------------
        // Inputting student scores


        cout << "\nAr norite sugeneruoti pažymius atsitiktinai?(y/n): ";
        string selection;
        cin >> selection;
        while (selection != "y" && selection != "n") {
            cout << "Bandykite dar kartą.\n";
            cout << " - ";
            cin.clear();
            cin.ignore(10000, '\n');

            cin >> selection;
        }

        if (selection == "y") {
            

            cout << "Kiek norite skaičių sugeneruoti (max 10)?";
            cout << " - "; 


            unsigned amount;
            while (!(cin >> amount) || (1 > amount && amount <= 10)) {

                cout << "Neteisingai įvestas kiekis.\n";
                cout << " - ";
                cin.clear();
                cin.ignore(10000, '\n');
            }  
             
            generate_random_scores(students[student_iterator], amount);
            students[student_iterator].score_count = amount - 1;
        } 

        else {

            cout << endl << "Jei norite baigti įvedimą įveskite '-1'\n";
            cout << "Įveskite namu darbų rezultatus:\n";

            int score;
            size_t score_count = 0;
            while (true) {
                

                cout << " - ";
                while (!(cin >> score)) {

                    cout << "Neteisingai įvestas pažymys.\n";
                    cout << " - ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }  

                if (score == -1) {
                    break;
                }
                else if (0 < score && score <= 10) {
                    students[student_iterator].scores[score_count++] = score;
                }
                else {

                    cout << "Neteisingai įvestas pažymys.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
            students[student_iterator].score_count = score_count;

            cout << endl << "Įveskite egzamino rezultatą: ";
            while (true) {

                cout << " - ";
                while (!(cin >> score) || !(0 < score && score <= 10)) {

                    cout << "Neteisingai įvestas pažymys.\n";
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
        student_iterator++;
        cout << endl;
    } 

    //------------------------------------------------------------------------
    // Calculating averages

    cout << "Ar norite skaičiuoti vidurkį(1) ar medianą(2)?\n";
    cout << " - ";
    unsigned option;
    while (!(cin >> option)) {
        cout << "Įveskite arba 1 arba 2.\n";
        cout << " - ";        
        cin.clear();
        cin.ignore(10000, '\n');
    }

    calculate_scores(students, student_iterator, option);
    print_students(students, student_iterator, option);

    return 0;
}
