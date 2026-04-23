#include <cstdio>
#include <iostream>
#include "cvs_reader.h"
/*
#include <chrono>
using namespace std::chrono;
using sc = steady_clock;
*/
using namespace std;

int main(int argc, char* argv[]) {
	string filename = "";

	if(argc > 1) {
		filename = argv[1];
	}
	else filename = "data/student_dropout_dataset_v3.csv";
	


	cout << "Loading data from: " << filename << "...\n";

	vector<Student> students = read_cvs(filename);

	if (students.empty()) {
		cout << "Failed.\n";
		return 1;
	}

	cout << "Successfully loaded " << students.size() << " valid students!\n\n";

	int n_of_drop = 0;
	int total_students = 0;
	int non_drop_students = 0;	

	int count_f = 0;
	int count_m = 0;

	double total_stress_drop = 0;
	double total_stress_all = 0;
	double total_stress_non = 0;

	double total_gpa_drop = 0;
	double total_gpa_all = 0;
	double total_gpa_non = 0;
	//sc::duration total_time = sc::duration::zero();
	//auto start = sc::now();
	for(Student& st: students){
		total_students++;	
		total_stress_all+=st.stress_index;
		total_gpa_all+=st.gpa;
		if(st.dropout == 1){
			++n_of_drop;
			total_stress_drop+=st.stress_index;
			total_gpa_drop+=st.gpa;

			if(st.gender == "Male"){
				++count_m;
			}else {
				++count_f;
			}

		}	
		else {
			total_stress_non+=st.stress_index;
			total_gpa_non+=st.gpa;
			non_drop_students++;
		}
	}	
	//auto end = sc::now();
	//total_time += (end - start);
	cout << "--- Data ---\n";

	cout << "Total Number of student: " << total_students << "\n";
	cout << "Total Number of student dropouts: " << n_of_drop << "\n";

	cout << "Dropouts %: " << (static_cast<float>(n_of_drop) / total_students) * 100 << "\n";

	cout << "------------------------------------------\n";

	cout << "Male dropout n: " << count_m << "\n";
	cout << "Female dropout n: " << count_f << "\n";
	if(n_of_drop < 1){
		cout << "Male dropout %: " << 0 << "\n";
		cout << "Female dropout %: " << 0 << "\n";
	}else {
		cout << "Male dropout %: " << (static_cast<float>(count_m) / n_of_drop) * 100 << "\n";
		cout << "Female dropout %: " << (static_cast<float>(count_f) / n_of_drop) * 100 << "\n";
	}

	cout << "------------------------------------------\n";

	cout << "Avg stress_index for a all student: " << total_stress_all / total_students << "\n";
	cout << "Avg stress_index for a non-dropout student: " << total_stress_non / non_drop_students<< "\n";
	if(n_of_drop < 1){
		cout << "Avg stress_index for a dropout student: None\n";
	}else {
		cout << "Avg stress_index for a dropout student: " << total_stress_drop / n_of_drop << "\n";
	}


	cout << "------------------------------------------\n";

	cout << "Avg GPA for a all student: " << total_gpa_all / total_students << "\n";
	cout << "Avg GPA for a non-dropout student: " << total_gpa_non / non_drop_students<< "\n";

	if(n_of_drop < 1){
		cout << "Avg GPA for a dropout student: None \n";
	}else {
		cout << "Avg GPA for a dropout student: " << total_gpa_drop / n_of_drop << "\n";
	}

	cout << "------------------------------------------\n";

	cout << "Finding high-risk pairs (Similar profiles, different outcomes)...\n";

	double similarity_threshold = 0.15;
	int high_risk_pairs = 0;
	//start = sc::now();

	for (size_t i = 0; i < students.size(); ++i) {
		for (size_t j = i + 1; j < students.size(); ++j) {

			if (students[i].dropout != students[j].dropout) {

				double gpa_diff = students[i].gpa - students[j].gpa;
				double stress_diff = students[i].stress_index - students[j].stress_index;
				double distance = (gpa_diff * gpa_diff + stress_diff * stress_diff);

				if (distance < similarity_threshold) {
					high_risk_pairs++;
				}
			}
		}
	}
	
	//end = sc::now();
	//total_time += (end - start);
	cout << "Total High-Risk Similar Pairs found: " << high_risk_pairs << "\n";

	cout << "------------------------------------------\n";


	int trio_count = 0;

	int limit = students.size();
	if(limit > 4000) limit = 4000;

	cout << "Range 0 - " << limit << endl;
	cout << "Searching for trios of dropouts with identical GPAs (First " << limit << " students)...\n";

	//start = sc::now();
	for (int i = 0; i < limit; ++i) {
		for (int j = i + 1; j < limit; ++j) {
			for (int k = j + 1; k < limit; ++k) {

				if (students[i].dropout == 1 && students[j].dropout == 1 && students[k].dropout == 1) {

					if (students[i].gpa == students[j].gpa && students[j].gpa == students[k].gpa) {
						trio_count++;
					}
				}
			}
		}
	}
	
	cout << "Total Identical Dropout Trios found: " << trio_count << "\n";

	int newLimit = students.size();
	if(newLimit > 8000) newLimit = 8000;

	cout << "Range " << limit << " - " << newLimit << endl;
	cout << "Searching for trios of dropouts with identical GPAs (First " << limit << " students)...\n";

	for (int i = limit; i < newLimit; ++i) {
		for (int j = i + 1; j < newLimit; ++j) {
			for (int k = j + 1; k < newLimit; ++k) {

				if (students[i].dropout == 1 && students[j].dropout == 1 && students[k].dropout == 1) {

					if (students[i].gpa == students[j].gpa && students[j].gpa == students[k].gpa) {
						trio_count++;
					}
				}
			}
		}
	}
	//end = sc::now();
	//total_time += (end - start);
	//cout << "loop_time " << (duration<double>(total_time)).count() << endl;

	cout << "Total Identical Dropout Trios found: " << trio_count << "\n";

	return 0;
}

