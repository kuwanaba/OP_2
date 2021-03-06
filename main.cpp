/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Program to input student names with scores and calculate
 *                  their finals
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
// TODO: Explore ways of changing how the program iterates the vectors
// TODO: Explore ways of refactoring the code so that the program doesn't act
//       in a linear way and the user has more control of what and when to do


#include "student_task_lib.hpp"


using std::cin;
using std::string;


int main(void)
{
     
    vector<Student> students;

    bool inputing_data = true;
    size_t student_iterator = 0;


    cout << "\nAr norite nuskaityti duomenis iš failo?(y/n)\n";
    cout << " - ";

    string selection;
    cin >> selection;
    while ( selection != "y" && selection != "n") {
        cout << "\nBandykite dar kartą.\n";
        cout << " - ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> selection;
    }


    if (selection == "y") {
        
        ifstream student_file;
        student_file.exceptions(ifstream::failbit | ifstream::badbit);

        try {
            
            student_file.open("kursiokai.txt");
        }
        catch (ifstream::failure e) {
            
            std::cerr << "Exception opening file.\n";
        }

        if (student_file.is_open()) {

            cout << endl;
            string line;
            
            // Skip the first line
            getline(student_file, line);

            while (getline(student_file, line) && !line.empty()) {


                std::istringstream ss(line);

                Student student;
                ss >> student.first_name;
                ss >> student.last_name;

                
                unsigned score;
                while (ss >> score) {
                    student.scores.push_back(score);
                }

                // After reading all of the scores thaat are present on a line
                // we assign the last one which is acutally the test score
                // to the appropriate member and pop it out of the wrong vector
                student.test_score = score;
                student.scores.pop_back();


                students.push_back(student); 
            }


            cout << "\nAr norite skaičiuoti vidurkį(1) ar medianą(2)?\n";
            cout << " - ";
            unsigned option;
            while (!(cin >> option)) {
                cout << "\nĮveskite arba 1 arba 2.\n";
                cout << " - ";        
                cin.clear();
                cin.ignore(10000, '\n');
            }

            
            calculate_scores(students, option);
            std::sort(students.begin(), students.end(), compare_by_first_letter);
            print_students(students, option);
            student_file.close();
        }
    }


    cin.clear();
    cin.ignore(10000, '\n');
    while (inputing_data) {

        cout << "\nJei norite baigti įvedimą įveskite 'x'\n";
        cout << "Įveskite studento vardą.\n"; 
        cout << " - ";

        Student student;
        do {
            string foo;
            getline(cin, foo);

            if (is_valid_string(foo)) {

                // Checking to see if user indicate end of student input
                if (foo == "x") {
                    inputing_data = false;
                    break;
                }
                student.first_name = foo;
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
                student.last_name = foo;
                break;

            } else {
                cout << "\nNeteisingai įvesta pavardė, bandykite dar kartelį.\n";
                cout << " - ";
            }

        } while (true);



        //---------------------------------------------------------------------
        // Inputting student scores


        cout << "\nAr norite sugeneruoti namų darbų rezultatus atsitiktinai?(y/n).\n";
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
            while (!(cin >> amount) || !(1 <= amount && amount <= 10)) {

                cout << "\nNeteisingai įvestas kiekis.\n";
                cout << " - ";
                cin.clear();
                cin.ignore(10000, '\n');
            }  
            
            cout << "\nNamu darbų pažymiai: "; 
            unsigned score;
            for (int i{}; i < amount; i++) {
                score = generate_random_score();
                student.scores.push_back(score);
                cout << score << " ";
            }
            cout << endl;
        } 

        else {

            cout << "\nJei norite baigti įvedimą įveskite '-1'\n";
            cout << "Įveskite namu darbų rezultatus.\n";

            int score;
            while (true) {
                

                cout << " - ";
                while (!(cin >> score)) {

                    cout << "\nNeteisingai įvestas pažymys.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }  

                if (score == -1) {
                    break;
                }
                else if (0 < score && score <= 10) {
                    student.scores.push_back(score);

                }
                else {

                    cout << "\nNeteisingai įvestas pažymys.\n";
                    cout << " - ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }
        }


        // If no values were inputted for a student skip the test score
        if (student.scores.size() == 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }


        cout << "\nAr norite sugeneruoti egzamino rezultatą atsitiktinai?(y/n).\n";
        cout << " - ";
        cin >> selection;
        while (selection != "y" && selection != "n") {
            cout << "\nBandykite dar kartą\n";
            cout << " - ";
            cin.clear();
            cin.ignore(10000, '\n');

            cin >> selection;
        }

        if (selection == "y") {
            
            student.test_score = generate_random_score();
            cout << "\nEgzamino pažymys: " << student.test_score << endl;
        }
        else {

            cout << "\nĮveskite egzamino rezultatą.\n";
            unsigned score;
            while (true) {

                cout << " - ";
                while (!(cin >> score) || !(1 <= score && score <= 10)) {

                    cout << "\nNeteisingai įvestas pažymys.\n";
                    cout << " - ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }  

                student.test_score = score;
                break;
            }
        }


        students.push_back(student);

        cin.clear();
        cin.ignore(10000, '\n');
        student_iterator++;
        cout << endl;
    } 

    //------------------------------------------------------------------------
    // Calculating averages
    

    if (students.empty()) {
        cout << "\nNeįvestas nei vienas studentas.\n";
        return 0;
    }

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
    calculate_scores(students, option);
    std::sort(students.begin(), students.end(), compare_by_first_letter);
    print_students(students, option);

    return 0;
}
