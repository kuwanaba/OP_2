/*
 * =====================================================================================
 *
 *       Filename:  student_scores_arrays.cpp
 *
 *    Description:  Functions defined for the students scores program
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

#include "../include/student_task_lib.hpp"


bool is_valid_string(const std::string& foo)
{
    bool valid = true;    

    if (foo.length() == 0)
        return false;

    for (std::size_t i{}; i < foo.length() && valid; i++) {
       if (!(std::isalnum(foo[i]) || std::isspace(foo[i]))) {
              valid = false; 
       }
    } 
    
    return valid;
}


bool is_digit(const std::string& foo)
{
    bool valid = true;
    for (std::size_t i{}; i < foo.length() && valid; i++) {
       if (!isdigit(foo[i]))
           valid = false;
    }

    return valid;
}



bool is_valid_score(int grade)
{
    if (0 < grade && grade <= 10)
        return true;

    return false;
}


void print_students_vector(const vector<Student> &students)
{
    cout << std::setw(20) << std::left << "Pavarde" 
        << std::setw(20) << std::left << "Vardas";
    for (decltype(students.size()) i{}; i < students.begin()->scores.size(); i++) {
        cout << std::left << std::setw(10) << "ND" + std::to_string(i + 1);
    }

    cout << std::left << std::setw(20) << "Egzaminas";
    cout << std::left << std::setw(20) << "Galutinis (Vid.)";
    cout << std::left << std::setw(20) << "Galutinis (Med.)";
    cout << endl;


    for (auto &student : students) {

        cout << std::setw(20) << std::left << student.last_name;
        cout << std::setw(20) << std::left << student.first_name;

       for (auto &score : student.scores) {
            cout << std::left << std::setw(10) << score;
       }

        cout << std::left << std::setw(20) << student.test_score;
        cout << std::left << std::setw(20) << std::setprecision(2) << student.final_score_avg;
        cout << std::left << std::setw(20) << std::setprecision(2) << student.final_score_med;
        cout << endl;
    }
}


void print_students_list(const list<Student> &students)
{
    cout << std::setw(20) << std::left << "Pavarde" 
        << std::setw(20) << std::left << "Vardas";
    for (decltype(students.size()) i{}; i < students.begin()->scores.size(); i++) {
        cout << std::left << std::setw(10) << "ND" + std::to_string(i + 1);
    }

    cout << std::left << std::setw(20) << "Egzaminas";
    cout << std::left << std::setw(20) << "Galutinis (Vid.)";
    cout << std::left << std::setw(20) << "Galutinis (Med.)";
    cout << endl;


    for (auto &student : students) {

        cout << std::setw(20) << std::left << student.last_name;
        cout << std::setw(20) << std::left << student.first_name;

       for (auto &score : student.scores) {
            cout << std::left << std::setw(10) << score;
       }

        cout << std::left << std::setw(20) << student.test_score;
        cout << std::left << std::setw(20) << std::setprecision(2) << student.final_score_avg;
        cout << std::left << std::setw(20) << std::setprecision(2) << student.final_score_med;
        cout << endl;
    }
}


void print_students_deque(const deque<Student> &students)
{
    cout << std::setw(20) << std::left << "Pavarde" 
        << std::setw(20) << std::left << "Vardas";
    for (decltype(students.size()) i{}; i < students.begin()->scores.size(); i++) {
        cout << std::left << std::setw(10) << "ND" + std::to_string(i + 1);
    }

    cout << std::left << std::setw(20) << "Egzaminas";
    cout << std::left << std::setw(20) << "Galutinis (Vid.)";
    cout << std::left << std::setw(20) << "Galutinis (Med.)";
    cout << endl;


    for (auto &student : students) {

        cout << std::setw(20) << std::left << student.last_name;
        cout << std::setw(20) << std::left << student.first_name;

       for (auto &score : student.scores) {
            cout << std::left << std::setw(10) << score;
       }

        cout << std::left << std::setw(20) << student.test_score;
        cout << std::left << std::setw(20) << std::setprecision(2) << student.final_score_avg;
        cout << std::left << std::setw(20) << std::setprecision(2) << student.final_score_med;
        cout << endl;
    }
}


void calculate_finals(Student &student)
{
    // Calculating using average
    float average = 0;
    for (const auto &score : student.scores) average += score;

    average /= student.scores.size();
    student.final_score_avg = 0.4 * average + 0.6 * student.test_score;

    // Rounding final score to two decimal places
    //student.final_score_avg = (float)((int)(student.final_score_avg * 100 + 0.5) / 100);


    // Calculating using median
    float median;
    auto mid = student.scores.begin() + student.scores.size() / 2;
    std::sort(student.scores.begin(), student.scores.end());
    if (student.scores.size() % 2 == 0) {
        auto mid = student.scores.begin() + student.scores.size() / 2;
        median = ((float)*mid + (float)*(mid - 1)) / 2;
    }            
    else {
            median = *mid;
    }
    student.final_score_med = 0.4 * median + 0.6 * student.test_score;

    // Rounding final score to two decimal places
    //student.final_score_med = (float)(((int)(student.final_score_med * 100 + 0.5)) / 100);
}


int generate_random_score()
{
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(1, 10);

    return dist(mt);
}


Student generate_random_student(int num_of_scores)
{
    Student student;

    student.first_name = "Vardas";
    student.last_name = "Pavarde";

    for (int i{}; i < num_of_scores; i++) {
        student.scores.push_back(generate_random_score());
    }

    student.test_score = generate_random_score();
    student.final_score_avg = 0;
    student.final_score_med = 0;

    return student;
}


void generate_student_vector(vector<Student> &students, int student_amount, int num_of_scores)
{
    for (int i{}; i < student_amount; i++) {

        Student student = generate_random_student(num_of_scores);
        student.first_name += std::to_string(i + 1);
        student.last_name += std::to_string(i + 1);
        students.push_back(student);
    }


    // Calculate the final_scores
    for (auto &student : students) {
        calculate_finals(student);
    }
}

void generate_student_list(list<Student> &students, int student_amount, int num_of_scores)
{
    for (int i{}; i < student_amount; i++) {

        Student student = generate_random_student(num_of_scores);
        student.first_name += std::to_string(i + 1);
        student.last_name += std::to_string(i + 1);
        students.push_back(student);
    }


    // Calculate the final_scores
    for (auto &student : students) {
        calculate_finals(student);
    }
}


void generate_student_deque(deque<Student> &students, int student_amount, int num_of_scores)
{
    for (int i{}; i < student_amount; i++) {

        Student student = generate_random_student(num_of_scores);
        student.first_name += std::to_string(i + 1);
        student.last_name += std::to_string(i + 1);
        students.push_back(student);
    }


    // Calculate the final_scores
    for (auto &student : students) {
        calculate_finals(student);
    }
}


bool compare_by_first_letter(const Student &a, const Student &b)
{
    return a.last_name < b.last_name;
}


bool compare_by_final_avg(const Student &a, const Student &b)
{
    return a.final_score_avg < b.final_score_avg;
}

bool compare_by_final_med(const Student &a, const Student &b)
{
    return a.final_score_med < b.final_score_med;
}


void read_students_vector_from_file(vector<Student>& students, string file_name)
{
    ifstream student_file;

    try {
        student_file.open(file_name);
    }
    catch (ifstream::failure e) {
        std::cerr << "Exception opening file.\n";
    }


    if (student_file.is_open()) {
        

        string line;
        
        // Skip the first line
        getline(student_file, line);

        while (getline(student_file, line) && !line.empty()) {


            std::istringstream ss(line);

            Student student;
            ss >> student.first_name;
            ss >> student.last_name;

            
            float score;
            vector<float>scores;
            while (ss >> score) {
                scores.push_back(score);
            }

            student.final_score_med = scores.back();
            scores.pop_back();

            student.final_score_avg = scores.back();
            scores.pop_back();

            student.test_score = scores.back();
            scores.pop_back();

            while (!scores.empty()) {
                student.scores.push_back(scores.front());
                scores.erase(scores.begin());
            }
            students.push_back(student); 
        }

        student_file.close();
    }
}


void read_students_list_from_file(list<Student>& students, string file_name)
{
    ifstream student_file;

    try {
        student_file.open(file_name);
    }
    catch (ifstream::failure e) {
        std::cerr << "Exception opening file.\n";
    }


    if (student_file.is_open()) {
        

        string line;
        
        // Skip the first line
        getline(student_file, line);

        while (getline(student_file, line) && !line.empty()) {


            std::istringstream ss(line);

            Student student;
            ss >> student.first_name;
            ss >> student.last_name;

            
            float score;
            vector<float>scores;
            while (ss >> score) {
                scores.push_back(score);
            }

            student.final_score_med = scores.back();
            scores.pop_back();

            student.final_score_avg = scores.back();
            scores.pop_back();

            student.test_score = scores.back();
            scores.pop_back();

            while (!scores.empty()) {
                student.scores.push_back(scores.front());
                scores.erase(scores.begin());
            }
            students.push_back(student); 
        }

        student_file.close();
    }
}


void read_students_deque_from_file(deque<Student>& students, string file_name)
{
    ifstream student_file;

    try {
        student_file.open(file_name);
    }
    catch (ifstream::failure e) {
        std::cerr << "Exception opening file.\n";
    }


    if (student_file.is_open()) {
        

        string line;
        
        // Skip the first line
        getline(student_file, line);

        while (getline(student_file, line) && !line.empty()) {


            std::istringstream ss(line);

            Student student;
            ss >> student.first_name;
            ss >> student.last_name;

            
            float score;
            vector<float>scores;
            while (ss >> score) {
                scores.push_back(score);
            }

            student.final_score_med = scores.back();
            scores.pop_back();

            student.final_score_avg = scores.back();
            scores.pop_back();

            student.test_score = scores.back();
            scores.pop_back();

            while (!scores.empty()) {
                student.scores.push_back(scores.front());
                scores.erase(scores.begin());
            }
            students.push_back(student); 
        }

        student_file.close();
    }
}


void write_students_vector_to_file(const vector<Student>& students, string file_name)
{
    ofstream student_file;

    try {
        student_file.open(file_name);
    }
    catch (ofstream::failure e) {
        std::cerr << "Exception opening file.\n";
    }


    if (student_file.is_open()) {
        
        std::ostringstream ss;
        ss << std::setw(20) << std::left << "Pavarde" 
            << std::setw(20) << std::left << "Vardas";
        for (decltype(students.size()) i{}; i < students.begin()->scores.size(); i++) {
            ss << std::left << std::setw(10) << "ND" + std::to_string(i + 1);
        }

        ss << std::left << std::setw(20) << "Egzaminas";
        ss << std::left << std::setw(20) << "Galutinis (Vid.)";
        ss << std::left << std::setw(20) << "Galutinis (Med.)";
        ss << endl;
        student_file << ss.str();


        for (auto &student : students) {

            std::ostringstream ss;
            ss << std::setw(20) << std::left << student.last_name;
            ss << std::setw(20) << std::left << student.first_name;

           for (auto &score : student.scores) {
                ss << std::left << std::setw(10) << score;
           }

            ss << std::left << std::setw(20) << student.test_score;
            ss << std::left << std::setw(20) << std::setprecision(2) << student.final_score_avg;
            ss << std::left << std::setw(20) << std::setprecision(2) << student.final_score_med;
            ss << endl;
            student_file << ss.str();
        }


        student_file.close();
    }
}


void write_students_list_to_file(const list<Student>& students, string file_name)
{
    ofstream student_file;

    try {
        student_file.open(file_name);
    }
    catch (ofstream::failure e) {
        std::cerr << "Exception opening file.\n";
    }


    if (student_file.is_open()) {
        
        std::ostringstream ss;
        ss << std::setw(20) << std::left << "Pavarde" 
            << std::setw(20) << std::left << "Vardas";
        for (decltype(students.size()) i{}; i < students.begin()->scores.size(); i++) {
            ss << std::left << std::setw(10) << "ND" + std::to_string(i + 1);
        }

        ss << std::left << std::setw(20) << "Egzaminas";
        ss << std::left << std::setw(20) << "Galutinis (Vid.)";
        ss << std::left << std::setw(20) << "Galutinis (Med.)";
        ss << endl;
        student_file << ss.str();


        for (auto &student : students) {

            std::ostringstream ss;
            ss << std::setw(20) << std::left << student.last_name;
            ss << std::setw(20) << std::left << student.first_name;

           for (auto &score : student.scores) {
                ss << std::left << std::setw(10) << score;
           }

            ss << std::left << std::setw(20) << student.test_score;
            ss << std::left << std::setw(20) << std::setprecision(2) << student.final_score_avg;
            ss << std::left << std::setw(20) << std::setprecision(2) << student.final_score_med;
            ss << endl;
            student_file << ss.str();
        }


        student_file.close();
    }
}


void write_students_deque_to_file(const deque<Student>& students, string file_name)
{
    ofstream student_file;

    try {
        student_file.open(file_name);
    }
    catch (ofstream::failure e) {
        std::cerr << "Exception opening file.\n";
    }


    if (student_file.is_open()) {
        
        std::ostringstream ss;
        ss << std::setw(20) << std::left << "Pavarde" 
            << std::setw(20) << std::left << "Vardas";
        for (decltype(students.size()) i{}; i < students.begin()->scores.size(); i++) {
            ss << std::left << std::setw(10) << "ND" + std::to_string(i + 1);
        }

        ss << std::left << std::setw(20) << "Egzaminas";
        ss << std::left << std::setw(20) << "Galutinis (Vid.)";
        ss << std::left << std::setw(20) << "Galutinis (Med.)";
        ss << endl;
        student_file << ss.str();


        for (auto &student : students) {

            std::ostringstream ss;
            ss << std::setw(20) << std::left << student.last_name;
            ss << std::setw(20) << std::left << student.first_name;

           for (auto &score : student.scores) {
                ss << std::left << std::setw(10) << score;
           }

            ss << std::left << std::setw(20) << student.test_score;
            ss << std::left << std::setw(20) << std::setprecision(2) << student.final_score_avg;
            ss << std::left << std::setw(20) << std::setprecision(2) << student.final_score_med;
            ss << endl;
            student_file << ss.str();
        }


        student_file.close();
    }
}
