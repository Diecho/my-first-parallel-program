#pragma once
#include <string>
#include <vector>
struct Student {
	std::string gender;
    double attendance_rate;
    double stress_index;
    double gpa;
    int dropout; 
    
    bool is_valid; 
};

std::vector<Student> read_cvs(const std::string& filename);
