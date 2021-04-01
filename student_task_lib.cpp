/*
 * =====================================================================================
 *
 *       Filename:  student_scores_arrays.cpp
 *
 *    Description:  Functions defined for the students scores program
 *
 *        Version:  1.0
 *        Created:  2021-03-02 22:25:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dominykas Makūnas
 *
 * =====================================================================================
 */

#include "student_task_lib.hpp"



bool is_valid_string(const std::string& foo)
{
    bool valid = true;    

    if (foo.length() == 0)
        return false;

    for (std::size_t i{}; i < foo.length() && valid; i++) {
       if (!(std::isalpha(foo[i]) || std::isspace(foo[i]))) {
              valid = false; 
       }
    } 
    
    return valid;
}



bool is_valid_score(int grade)
{
    if (0 < grade && grade <= 10)
        return true;

    return false;
}



void calculate_scores(vector<Student>& students, unsigned option)
{
    for (auto &student : students) {

        if (student.scores.empty())
            continue;

        // Calculating average
        if (option == 1) {

            float average = 0;
            for (auto &score : student.scores) {
                average += score;    
            }

            average /= student.scores.size();

            student.final_score = 0.4 * average + 0.6 * student.test_score;
        }
        // Calculating median
        else {

            float median;
            auto mid = student.scores.begin() + student.scores.size() / 2;
            std::sort(student.scores.begin(), student.scores.end());
            if (student.scores.size() % 2 == 0) {
                //unsigned mid = student.scores.size() / 2;
                //median = ((float)student.scores[mid] + (float)student.scores[mid - 1]) / 2;
                auto mid = student.scores.begin() + student.scores.size() / 2;
                median = ((float)*mid + (float)*(mid - 1)) / 2;
            }            
            else {
                    median = *mid;
            }
            student.final_score = 0.4 * median + 0.6 * student.test_score;
        }
    }
}


void print_students(const vector<Student>& students, int option)
{
    printf("\n%-20s%-20s%-20s\n", "Pavarde", "Vardas", 
            (option == 1) ? "Galutinis (Vid.)" : "Galutinis (Med.)");

    string temp(55, '-');
    cout << temp << endl;
    for (const auto& student : students) {
    
        
        if (student.scores.empty())
            continue;
        
        
        printf("%-20s%-20s%-20.2f\n", student.last_name.c_str(), student.first_name.c_str(),
                                        student.final_score);
    }

    cout << endl;
}


unsigned generate_random_score()
{
    using hrClock = std::chrono::high_resolution_clock;
    std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(1, 10);

    return dist(mt);
}


void generate_random_list(vector<Student>& students, int amount)
{
    unsigned num_of_scores = generate_random_score();
    for (int i = 0; i < amount; i++) {
        Student student;

        student.first_name = "Vardas";
        student.first_name += std::to_string(i + 1);

        student.last_name = "Pavarde";
        student.last_name += std::to_string(i + 1);


        for (int i{}; i < num_of_scores; i++) {
            student.scores.push_back(generate_random_score());
        }

        student.test_score = generate_random_score();
        student.final_score = 0;

        students.push_back(student);
    }
}

bool compare_by_first_letter(const Student &a, const Student &b)
{
    return a.last_name < b.last_name;
}


bool compare_by_final_score(const Student &a, const Student &b)
{
    return a.final_score < b.final_score;
}


void read_students_from_file(vector<Student>& students, string file_name)
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

        student_file.close();
    }
}


void write_students_to_file(const vector<Student>& students, string file_name)
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
        for (int i{}; i < students[0].scores.size(); i++) {
            ss << "\tND" << i + 1; 
        }
        ss << "\tEgz";

        students[0].final_score == 0 ?  ss << std::endl : ss << "\t\tGalutinis\n";
        student_file << ss.str();


        for (auto &student : students) {

            std::ostringstream ss;
            ss << std::setw(20) << std::left << student.last_name;
            ss << std::setw(20) << std::left << student.first_name;

           for (auto &score : student.scores) {
                ss << "\t" << score;
           }

            ss << "\t" << student.test_score;
            student.final_score == 0 ? ss << endl :
                ss << "\t\t" << std::setprecision(2) << student.final_score << endl;
            student_file << ss.str();
        }


        student_file.close();
    }
}
