/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Program to input student names with scores and calculate
 *                  their finals
 *
 *        Version:  v0.5
 *        Created:  03/04/2021
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


#include "../include/student_task_lib.hpp"


using std::cin;
using std::string;


int main(void)
{
    
    vector<Student> students_v;


    cout << "Studentų informacinė programa.\n\n";
    cout << "Meniu:\n"
        << " - Sugeneruoti penkis atistiktinius studentų sarašus ir atlikti testus naudojant vektorius\n"
        << "   1 - naudojant vektorių\n"
        << "   2 - naudojant sąrašą\n"
        << "   3 - naudojant deką\n"
        << "4 - Atspausdinti studentų sąrašą\n"
        << "5 - Pakartoti meniu\n"
        << "Norėdami baigį programą įveskite -1\n";


    int menu_selection;
    //int option;
    while (1) {


        cout << endl << endl; 
        cout << "> ";
        while (!(cin >> menu_selection) || !(-1 <= menu_selection && menu_selection <= 5)) {

            cout << "\nNeteisingas pasirinkimas.\n";
            cout << " - ";
            cin.clear();
            cin.ignore(10000, '\n');
        }  


        switch (menu_selection) {

            case 1: {
                
                int student_amount = 100;


                for (int i{}; i < 5; i++) {

                    student_amount *= 10;

                    generate_student_vector(students_v, student_amount, 5);
                    write_students_vector_to_file(students_v, "studentai.txt");
                    students_v.clear();

                    
                    auto start = std::chrono::high_resolution_clock::now(); 
                    read_students_vector_from_file(students_v, "studentai.txt");
                    auto time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = time - start;
                    auto stop = time;
                    cout << student_amount 
                        << " elementų vektorių nuskaityti iš failo užtruko: " << diff.count() << "s\n";


                    vector<Student> students_low;
                    vector<Student> students_high;
                    std::sort(students_v.begin(), students_v.end(), compare_by_final_med);


                    auto beg = students_v.begin();
                    for (;;beg++) {
                        if ((*beg).final_score_avg >= 5)
                            break;

                        students_low.push_back(*beg);
                    }

                    for (; beg != students_v.end(); beg++) {
                        students_high.push_back(*beg);
                    }


                    time = std::chrono::high_resolution_clock::now();
                    diff = time - stop;
                    stop = time;
                    cout << student_amount 
                        << " elementų vektorių surūšiuoti į dvi grupes užtruko: " << diff.count() << "s\n";

                    
                    students_low.clear();
                    students_high.clear();
                    //students_v.clear();
                    cout << endl << endl;
                }

                break;
            }
            case 2: {
                
                int student_amount = 100;

                list<Student> student_list;
                for (int i{}; i < 5; i++) {

                    student_amount *= 10;

                    generate_student_list(student_list, student_amount, 5);
                    write_students_list_to_file(student_list, "studentai_list.txt");
                    student_list.clear();

                    
                    auto start = std::chrono::high_resolution_clock::now(); 
                    read_students_list_from_file(student_list, "studentai_list.txt");
                    auto time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = time - start;
                    auto stop = time;
                    cout << student_amount 
                        << " elementų sąrašą nuskaityti iš failo užtruko: " << diff.count() << "s\n";


                    list<Student> students_low;
                    list<Student> students_high;
                    student_list.sort(compare_by_final_med);


                    auto beg = student_list.begin();
                    for (;;beg++) {
                        if ((*beg).final_score_avg >= 5)
                            break;

                        students_low.push_back(*beg);
                    }

                    for (; beg != student_list.end(); beg++) {
                        students_high.push_back(*beg);
                    }


                    time = std::chrono::high_resolution_clock::now();
                    diff = time - stop;
                    stop = time;
                    cout << student_amount 
                        << " elementų sąrašą surūšiuoti į dvi grupes užtruko: " << diff.count() << "s\n";

                    
                    students_low.clear();
                    students_high.clear();
                    student_list.clear();
                    cout << endl << endl;
                }

                break;
            }
            case 3: {
                
                int student_amount = 100;

                deque<Student> student_deque;
                for (int i{}; i < 5; i++) {

                    student_amount *= 10;

                    generate_student_deque(student_deque, student_amount, 5);
                    write_students_deque_to_file(student_deque, "studentai_deque.txt");
                    student_deque.clear();

                    
                    auto start = std::chrono::high_resolution_clock::now(); 
                    read_students_deque_from_file(student_deque, "studentai_deque.txt");
                    auto time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = time - start;
                    auto stop = time;
                    cout << student_amount 
                        << " elementų deką nuskaityti iš failo užtruko: " << diff.count() << "s\n";


                    deque<Student> students_low;
                    deque<Student> students_high;
                    std::sort(student_deque.begin(), student_deque.end(), compare_by_final_med);


                    auto beg = student_deque.begin();
                    for (;;beg++) {
                        if ((*beg).final_score_avg >= 5)
                            break;

                        students_low.push_back(*beg);
                    }

                    for (; beg != student_deque.end(); beg++) {
                        students_high.push_back(*beg);
                    }


                    time = std::chrono::high_resolution_clock::now();
                    diff = time - stop;
                    stop = time;
                    cout << student_amount 
                        << " elementų deką surūšiuoti į dvi grupes užtruko: " << diff.count() << "s\n";

                    
                    students_low.clear();
                    students_high.clear();
                    student_deque.clear();
                    cout << endl << endl;
                }

                break;
            }

            case 4: {


                print_students_vector(students_v);

                /*
                printf("\n%-20s%-20s", "Pavarde", "Vardas");


                
                // students_v[0] just to check how many scores do students have
                // in that particular list
                for (int i{}; i < students_v[0].scores.size(); i++) {
                    cout << "\tND" << i + 1;
                }
                

                
                cout << left << setw(20) << "Egzaminas";
                cout << left << setw(20) << "Galutinis (Vid.)";
                cout << left << setw(20) << "Galutinis (Med.)";

                cout << endl;
                
                for (const auto &student : students_v) {
                    cout << left << setw(20) << student.last_name; 
                    cout << left << setw(20) << student.first_name;

                    
                    for (const auto &score : student.scores) {
                        cout << "\t" << score;
                    }
                    

                    cout << left << setw(20) << student.test_score;
                    cout << left << setw(20) << student.final_score_avg;
                    cout << left << setw(20) << student.final_score_med;

                    cout << endl;
                }
                */
                break;
            }

            case 5: {

                cout << "Meniu:\n"
                    << "1 - Sugeneruoti studentus atsitiktinai\n"
                    << "2 - Atspausdinti studentų sąrašą\n"
                    << "5 - Pakartoti meniu\n"
                    << "Norėdami baigį programą įveskite -1\n";
                break;
            } 


            case -1: {
                exit(EXIT_SUCCESS);
                break;
            }
        }
    }

    return 0;
    /* 
    bool inputing_data = true;
    size_t student_iterator = 0;


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
    */
}
