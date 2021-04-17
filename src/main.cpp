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

#include "../include/student_task_lib.hpp"
#include <fstream>


using std::cin;
using std::string;


int main(void)
{
    
    vector<Student> students_v;


    cout << "Studentų informacinė programa.\n\n";
    cout << "Meniu:\n"
        << " 1 - Sugeneruoti penkis atistiktinius studentų failus\n"
        << "   11 - atlikti testus naudojant vektorių\n"
        << "   12 - atlikti testus naudojant sąrašą\n"
        << "   13 - atlikti testus naudojant deką\n"
        << "2 - Įvesti duomenis apie studentą\n"
        << "3 - Suskaičiuoti galutinius pažymius\n"
        << "4 - Nuskaityti studentus iš failo \"studentai.txt\"\n"
        << "p - Atspausdinti studentų sąrašą\n"

        << "5 - Pakartoti meniu\n"
        << "Norėdami baigį programą įveskite x\n";

    int menu_selection;

    bool files_generated = false;
    while (1) {


        /*
        cout << endl << endl; 
        cout << "> ";
        while (!(cin >> menu_selection)) {

            cout << "\nNeteisingas pasirinkimas.\n";
            cout << " - ";
        }  
        */
        
        cout << endl << endl;
        cout << "> ";
        string foo;
        do {
            getline(cin, foo);

            if (is_valid_string(foo)) {
                
                if (foo.size() == 1) {
                    
                    if (std::isdigit(foo[0])) {
                        menu_selection = stoi(foo);
                        break;
                    }

                    if (foo[0] == 'p') {
                        menu_selection = 55;
                        break;
                    }

                    if (foo[0] == 'x') {
                        menu_selection = -1;
                        break;
                    }
                }
                
                if (foo.size() == 2 && is_digit(foo)) {
                    menu_selection = stoi(foo);
                    break;
                }
            }

        } while (true);


        switch (menu_selection) {

            case 1: {
                
                int student_amount = 100;
                for (int i{}; i < 3; i++) {
                    student_amount *= 10;
                    generate_student_vector(students_v, student_amount, 5);
                    write_students_vector_to_file(students_v, 
                            "studentai" + std::to_string(student_amount) + ".txt");
                    
                    cout << "Sukurtas failas: studentai" << student_amount << ".txt" << endl;
                }
                files_generated = true;
                break;
            }

            case 11: {


                if (!files_generated) {
                    cout << "Sugeneruokite failus (1) meniu punktu\n";
                    break;
                }


                cout << "Pasirinkite realizacijos metodą:\n"
                    << " 1 - naudojant du konteinerius\n"
                    << " 2 - naudojant vieną konteinerį\n";
                cout << "> ";

                int implementation_option;
                while (!(cin >> implementation_option)) {
                    cout << "Klaida: įveskite skaičių (1/2):";
                    cout << "> ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }

                
                int student_amount = 100;


                for (int i{}; i < 5; i++) {

                    student_amount *= 10;

                    string file_name("studentai");
                    file_name += std::to_string(student_amount);
                    file_name += ".txt";


                    auto start = std::chrono::high_resolution_clock::now(); 
                    read_students_vector_from_file(students_v, file_name);
                    auto time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = time - start;
                    auto stop = time;
                    cout << student_amount 
                        << " elementų vektorių nuskaityti iš failo užtruko: " << diff.count() << "s\n";


                    vector<Student> students_low;
                    vector<Student> students_high;


                    switch (implementation_option) {
                        case 1: {

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
                            break;
                        }

                        case 2: {
                            
                            std::sort(students_v.begin(), students_v.end(), compare_by_final_med_reverse);
                            for (decltype(students_v.size()) i; i < students_v.size(); i++) {
                                if (students_v[i].final_score_avg >= 5)
                                    break;

                                students_low.push_back(students_v[i]);
                                students_v.pop_back();
                            }
                            break;
                        }

                        default:
                            break;
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
            case 12: {

                if (!files_generated) {
                    cout << "Sugeneruokite failus (1) meniu punktu\n";
                    break;
                }


                cout << "Pasirinkite realizacijos metodą:\n"
                    << " 1 - naudojant du konteinerius\n"
                    << " 2 - naudojant vieną konteinerį\n";
                cout << "> ";

                int implementation_option;
                while (!(cin >> implementation_option)) {
                    cout << "Klaida: įveskite skaičių (1/2):";
                    cout << "> ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }
                
                int student_amount = 100;


                list<Student> student_list;
                for (int i{}; i < 5; i++) {

                    student_amount *= 10;
                    string file_name("studentai");
                    file_name += std::to_string(student_amount);
                    file_name += ".txt";

                    
                    auto start = std::chrono::high_resolution_clock::now(); 
                    read_students_list_from_file(student_list, file_name);
                    auto time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = time - start;
                    auto stop = time;
                    cout << student_amount 
                        << " elementų sąrašą nuskaityti iš failo užtruko: " << diff.count() << "s\n";


                    list<Student> students_low;
                    list<Student> students_high;
                    student_list.sort(compare_by_final_med);


                    switch (implementation_option) {

                        case 1: {
                                
                            auto beg = student_list.begin();
                            for (;;beg++) {
                                if ((*beg).final_score_avg >= 5)
                                    break;

                                students_low.push_back(*beg);
                            }

                            for (; beg != student_list.end(); beg++) {
                                students_high.push_back(*beg);
                            }
                            break;
                        }

                        case 2: {

                            for (decltype(student_list.size()) i; i < student_list.size(); i++) {
                                if (student_list.front().final_score_avg >= 5)
                                    break;

                                students_low.push_back(student_list.front());
                                student_list.pop_front();
                            }
                            break;
                        }

                        default:

                            break;
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
            case 13: {


                if (!files_generated) {
                    cout << "Sugeneruokite failus (1) meniu punktu\n";
                    break;
                }


                cout << "Pasirinkite realizacijos metodą:\n"
                    << " 1 - naudojant du konteinerius\n"
                    << " 2 - naudojant vieną konteinerį\n";
                cout << "> ";

                int implementation_option;
                while (!(cin >> implementation_option)) {
                    cout << "Klaida: įveskite skaičių (1/2):";
                    cout << "> ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }
                
                int student_amount = 100;


                deque<Student> student_deque;
                for (int i{}; i < 5; i++) {

                    student_amount *= 10;
                    string file_name("studentai");
                    file_name += std::to_string(student_amount);
                    file_name += ".txt";


                    auto start = std::chrono::high_resolution_clock::now(); 
                    read_students_deque_from_file(student_deque, file_name);
                    auto time = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> diff = time - start;
                    auto stop = time;
                    cout << student_amount 
                        << " elementų deką nuskaityti iš failo užtruko: " << diff.count() << "s\n";


                    deque<Student> students_low;
                    deque<Student> students_high;
                    std::sort(student_deque.begin(), student_deque.end(), compare_by_final_med);

                    
                    switch (implementation_option) {
                        
                        case 1: {

                            auto beg = student_deque.begin();
                            for (;;beg++) {
                                if ((*beg).final_score_avg >= 5)
                                    break;

                                students_low.push_back(*beg);
                            }

                            for (; beg != student_deque.end(); beg++) {
                                students_high.push_back(*beg);
                            }
                            break;
                        }

                        case 2: {

                            auto beg = student_deque.begin();
                            for (;;beg++) {
                                if ((*beg).final_score_avg >= 5)
                                    break;

                                students_low.push_back(*beg);
                                student_deque.erase(beg);
                            }
                            break;
                        }

                        default: {

                            break;
                        }
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


            case 2: {
               

                cout << "Įveskite studento vardą.\n"; 
                cout << "> ";

                Student student;
                do {
                    string foo;
                    getline(cin, foo);

                    if (is_valid_string(foo)) {

                        student.first_name = foo;
                        break;

                    } else {
                        cout << "\nNeteisingai įvestas vardas, bandykite dar kartelį.\n";
                        cout << " - ";
                    }

                } while (true);


                cout << "\nĮveskite studento pavardę\n"; 
                cout << "> ";
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

                

                //-----------------------------------------------------------------------------
                // Inputting scores
                
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


                    int amount;
                    while (!(cin >> amount) || !(1 <= amount && amount <= 10)) {

                        cout << "\nNeteisingai įvestas kiekis.\n";
                        cout << " - ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }  
                    
                    cout << "\nNamu darbų pažymiai: "; 
                    int score;
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


                students_v.push_back(student);

                cin.clear();
                cin.ignore(10000, '\n');
                cout << endl;

                break;
            }


            case 3: {
                
                if (students_v.empty()) {
                    cout << "\nNeįvestas nei vienas studentas.\n";
                    break;
                }

                
                for (auto &student : students_v) {
                    
                    calculate_finals(student);
                }
                break;
            }


            case 4: {

                read_students_vector_from_file(students_v, "studentai.txt");
                break;
            }

            case 55: {

                if (students_v.empty()) {
                    cout << "Studentų sąrašas tuščias\n";
                    break;
                }
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

                cout << "Studentų informacinė programa.\n\n";
                cout << "Meniu:\n"
                    << " 1 - Sugeneruoti penkis atistiktinius studentų failus\n"
                    << "   11 - atlikti testus naudojant vektorių\n"
                    << "   12 - atlikti testus naudojant sąrašą\n"
                    << "   13 - atlikti testus naudojant deką\n"
                    << "2 - Įvesti duomenis apie studentą\n"
                    << "3 - Suskaičiuoti galutinius pažymius\n"
                    << "4 - Nuskaityti studentus iš failo \"studentai.txt\"\n"
                    << "p - Atspausdinti studentų sąrašą\n"

                    << "5 - Pakartoti meniu\n"
                    << "Norėdami baigį programą įveskite x\n";
                break;
            } 


            case -1: {
                exit(EXIT_SUCCESS);
                break;
            }

            default: {
                
                cout << "Neteisinga įvestis.\n";
                cout << "Jei dar kartą norite pamatyti meniu įveskite \"5\"\n";
                break;
            }
        }
    }

    return 0;
    /* 
    bool inputing_data = true;
    size_t student_iterator = 0;




    cin.clear();
    cin.ignore(10000, '\n');
    while (inputing_data) {




        //---------------------------------------------------------------------
        // Inputting student scores



    //------------------------------------------------------------------------
    // Calculating averages
    


    return 0;
    */
}
