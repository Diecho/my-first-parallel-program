#include "cvs_reader.h"
#include <fstream>
#include <sstream>

std::vector<Student> read_cvs(const std::string& filename) {
	std::vector<Student> students;
	std::ifstream file(filename);
	std::string line;

	std::getline(file, line); 

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string token;
		Student s;

		s.is_valid = true;

		std::getline(ss, token, ',');
		std::getline(ss, token, ',');
		std::getline(ss, token, ',');
		if(token ==  ""){
			s.is_valid = false;
			continue;
		}
		s.gender= token;

		std::getline(ss, token, ',');
		std::getline(ss, token, ',');
		std::getline(ss, token, ',');
		std::getline(ss, token, ',');

		if(token == ""){
			s.is_valid = false;
			continue;
		}
		s.attendance_rate= std::stod(token);

		std::getline(ss, token, ',');
		std::getline(ss, token, ',');
		std::getline(ss, token, ',');
		std::getline(ss, token, ',');
		std::getline(ss, token, ',');

		if(token == ""){
			s.is_valid = false;
			continue;
		}
		s.stress_index= std::stod(token);

		std::getline(ss, token, ',');

		if(token == ""){
			s.is_valid = false;
			continue;
		}
		s.gpa = std::stod(token);


		std::getline(ss, token, ',');
		std::getline(ss, token, ',');
		std::getline(ss, token, ',');
		std::getline(ss, token, ',');
		std::getline(ss, token, ',');
		std::getline(ss, token, ',');

		if(token == ""){
			s.is_valid = false;
			continue;
		}
		s.dropout= std::stoi(token);

		if (s.is_valid) {
			students.push_back(s);
		}
	}
	return students;
}
