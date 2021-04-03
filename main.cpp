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
     

    bool inputing_data = true;
    size_t student_iterator = 0;


    cout << "\nAr norite sugeneruoti penkis atsitiktinius studentų sąrašus?(y/n)\n";
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

    cout << endl << endl;
    // Generating a random student list
    if (selection == "y") {

        int student_amount = 100;
        for (int i{}; i < 5; i++) {

            student_amount *= 10;
            
            vector<Student> students_random; 
            vector<Student> students;
            vector<Student> students_low;

            
            auto start = std::chrono::high_resolution_clock::now();

            generate_random_list(students_random, student_amount); 
            write_students_to_file(students_random, "test.txt");

            auto time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = time - start;
            auto stop = time;
            cout << student_amount 
                << " elementų failą sukurt užtruko: " << diff.count() << "s\n";
            
            
            read_students_from_file(students, "test.txt");
            time = std::chrono::high_resolution_clock::now();
            diff = time - stop;
            stop = time;
            cout << student_amount 
                << " elementų nuskaityti iš failo užtruko: " << diff.count() << "s\n";


            calculate_scores(students, 1);
            std::sort(students.begin(), students.end(), compare_by_final_score);


            while (students.begin()->final_score < 5) {
                
                students_low.push_back(*students.begin());
                students.erase(students.begin());
            }

            time = std::chrono::high_resolution_clock::now();
            diff = time - stop;
            stop = time;
            cout << student_amount 
                << " elementų surūšiuoti į dvi grupes užtruko: " << diff.count() << "s\n";
             

            write_students_to_file(students_low, "vargšiukai.txt");
            write_students_to_file(students, "kietiakiai.txt");


            time = std::chrono::high_resolution_clock::now();
            diff = time - stop;
            cout << student_amount 
                << " surūšiuotų studentų išvedimas į du failus užtruko: " << diff.count() << "s\n";

            diff = time - start;
            cout << endl << student_amount 
                << " studentų skaičiaus testas užtruko: " << diff.count() << "s\n";
            cout << endl << endl;
        }


        return 0;
    }


    cout << "\nAr norite nuskaityti duomenis iš failo?(y/n)\n";
    cout << " - ";

    cin >> selection;
    while ( selection != "y" && selection != "n") {
        cout << "\nBandykite dar kartą.\n";
        cout << " - ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> selection;
    }


    vector<Student> students;
    if (selection == "y") {
        
            read_students_from_file(students, "studentai.txt");

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

            students.clear();
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
