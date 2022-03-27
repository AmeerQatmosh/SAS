//Ameer Qatmosh 11923652

#include<iostream>
#include<stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_set> 
using namespace std;

struct StudentInfo {
	int St_no;
	string St_full_name;
	double St_grade_1;
	double St_grade_2;
	double St_grade_3;
};


void getFileContent(string, StudentInfo[], int);
void displayFileContent(StudentInfo[], int);
void printChoices();
void getStudentTotalGrade(StudentInfo[], int, int);
void getAvarageGradeForExam(StudentInfo[], int, int);
void getAvarageForAllStudents(StudentInfo[], int);
void updateStudentInfo(StudentInfo[], int, int);
void updateFileContent(StudentInfo[], int, string);
void sortGradesInDescendingOrder(StudentInfo[], int);
bool gradeSortingDescending(const StudentInfo& r1, const StudentInfo& r2);
int countNumberInRange(StudentInfo[], int, int, int);
void printHistogram(StudentInfo[], int);

int main() {
	// As given in the project document, we have 20 students in the file. 
	const int size = 20;
	StudentInfo St[size];

	getFileContent("course.csv", St, size);

	int choice;
	//Ask user to enter one of the choices
	printChoices();
	cin >> choice;
	while (choice != 10) {
		switch (choice) {
		case 1:
			displayFileContent(St, size);
			break;
		case 2:
			int id;
			cout << "Enter student id" << endl;
			cin >> id;
			getStudentTotalGrade(St, size, id);
			break;
		case 3:
			int examNo;
			cout << "Please enter exam number (1,2,3): ";
			cin >> examNo;
			getAvarageGradeForExam(St, size, examNo);
			break;
		case 4:
			getAvarageForAllStudents(St, size);
			break;
		case 5:
			int studentId;
			cout << "Please enter student ID:" << endl;
			cin >> studentId;
			updateStudentInfo(St, size, studentId);
			break;
		case 6:
			//please make sure that "course.csv" should not be opened by another application 
			updateFileContent(St, size, "course.csv");
			break;
		case 7:
			getFileContent("course.csv", St, size);
			cout << "Content of the file reloaded" << endl;
			break;
		case 8:
			sortGradesInDescendingOrder(St, size);
			cout << endl;
			break;
		case 9:
			printHistogram(St, size);
			break;
		default:
			cout << "Invalid choice,please enter choice number from 1 to 10" << endl;
		}

		printChoices();
		//cout << "Please Enter your choise:";
		cin >> choice;
	}
	return 0;
}


void getFileContent(string file_path, StudentInfo st[], int size) {
	string str = "";
	string line = "";
	ifstream myReadFile;
	myReadFile.open(file_path);
	int  i = 0;
	string id, name, grade1, grade2, grade3;
	if (myReadFile.is_open()) {
		while (getline(myReadFile, line) && i < size) {
			stringstream ss1(line);
			getline(ss1, id, ',');
			getline(ss1, name, ',');
			getline(ss1, grade1, ',');
			getline(ss1, grade2, ',');
			getline(ss1, grade3, ',');
			st[i].St_no = stod(id);
			st[i].St_full_name = name;
			st[i].St_grade_1 = stod(grade1);
			st[i].St_grade_2 = stod(grade2);
			st[i].St_grade_3 = stod(grade3);
			i++;
		}
	}
	myReadFile.close();
}

//1
void displayFileContent(StudentInfo st[], int size) {
	for (int i = 0; i < size; i++) {
		cout << st[i].St_no << " " << st[i].St_full_name << " " << st[i].St_grade_1
			<< " " << st[i].St_grade_2 << " " << st[i].St_grade_3 << endl;
	}

}

void printChoices() {
	cout << '\t' << '\t' << '\t' << '\t' << "Student Assessment System" << endl;
	cout << "The application provides the following services: " << endl;
	cout << "    1. print the content of the file on screen." << endl;
	cout << "    2. print the total grade of a student in an exam." << endl;
	cout << "    3. Print the average grade in a certain exam." << endl;
	cout << "    4. Print the average of total grade for all students." << endl;
	cout << "    5. Update student information." << endl;
	cout << "    6. Store the updated content of the array into the file." << endl;
	cout << "    7. Reload the content of the file." << endl;
	cout << "    8. display records according to the total grade in descending order." << endl;
	cout << "    9. draw a histogram for total grades." << endl;
	cout << "    10. Exit." << endl;
	cout << "Please Enter your Choice: " << endl;
	cout << ">> ";

}

//2
void getStudentTotalGrade(StudentInfo st[], int size, int id) {
	StudentInfo student;
	bool isFound = false;
	for (int i = 0; i < size; i++) {
		if (st[i].St_no == id) {
			student = st[i];
			isFound = true;
			break;
		}
	}
	if (isFound) {
		double total = student.St_grade_1 + student.St_grade_2 + student.St_grade_3;
		cout << "Total Grade = " << total << endl;
	}
	else {
		cout << "Student not found" << endl;
	}
}

//3
void getAvarageGradeForExam(StudentInfo st[], int size, int examNo) {
	if (examNo < 1 || examNo > 3) {
		cout << "Exam number invalid" << endl;
	}
	else {
		double  sum = 0;
		for (int i = 0; i < size; i++) {
			if (examNo == 1) {
				sum += st[i].St_grade_1;
			}
			else if (examNo == 2) {
				sum += st[i].St_grade_2;
			}
			else if (examNo == 3) {
				sum += st[i].St_grade_3;
			}
		}
		cout << "Avarage grade for  exam number  " << examNo << " = " << sum / size << endl;
	}
}

//4
void getAvarageForAllStudents(StudentInfo st[], int size) {
	double sum = 0;
	for (int i = 0; i < size; i++) {
		sum += st[i].St_grade_1;
		sum += st[i].St_grade_2;
		sum += st[i].St_grade_3;
	}
	cout << "The average of total grade for all students = " << sum / size << endl;

}
//5
void updateStudentInfo(StudentInfo st[], int size, int studentId) {
	StudentInfo student;
	string name;
	double grade1, grade2, grade3;
	int position;
	bool isFound = false;
	for (int i = 0; i < size; i++) {
		if (st[i].St_no == studentId) {
			student = st[i];
			isFound = true;
			position = i;
			break;
		}
	}
	if (isFound) {
		cout << "Student number: " << student.St_no << "  Name: " << student.St_full_name
			<< "  Grade 1: " << student.St_grade_1 << "  Grade 2: " << student.St_grade_2
			<< "  Grade 3: " << student.St_grade_3 << endl;
		cout << "Student Name:" << endl;
		cin.ignore();//to ignore or clear one or more characters from the input buffer.
		getline(cin, name);
		cout << "Grade 1:" << endl;
		cin >> grade1;
		cout << "Grade 2:" << endl;
		cin >> grade2;
		cout << "Grade 3:" << endl;
		cin >> grade3;
		st[position].St_full_name = name;
		st[position].St_grade_1 = grade1;
		st[position].St_grade_2 = grade2;
		st[position].St_grade_3 = grade3;
		cout << "Student Info after update: " << endl;
		cout << "Student number: " << st[position].St_no << "  Name: " << st[position].St_full_name
			<< "  Grade 1: " << st[position].St_grade_1 << "  Grade 2: " << st[position].St_grade_2
			<< "  Grade 3: " << st[position].St_grade_3 << endl;
	}
	else {
		cout << "Student not found" << endl;
	}
}
//6
void updateFileContent(StudentInfo  st[], int size, string file_path) {
	ofstream myFile;
	myFile.open(file_path);
	if (myFile.is_open()) {
		for (int i = 0; i < size; i++) {
			myFile << st[i].St_no << "," << st[i].St_full_name << "," << st[i].St_grade_1
				<< "," << st[i].St_grade_2 << "," << st[i].St_grade_3 << "\n";
		}
	}
	myFile.close();
	cout << "File content updated" << endl;
}

//8
void sortGradesInDescendingOrder(StudentInfo st[], int size) {
	//sort array in descending order
	sort(st, st + size, gradeSortingDescending);
	// after call sort function , st array will be sorted in descending order
	for (int i = 0; i < size; i++) {
		int total = (st[i].St_grade_1 + st[i].St_grade_2 + st[i].St_grade_3);
		cout << st[i].St_no << " " << st[i].St_full_name << " " << st[i].St_grade_1
			<< " " << st[i].St_grade_2 << " " << st[i].St_grade_3 << endl;
	}
}


bool gradeSortingDescending(const StudentInfo& st1, const StudentInfo& st2)
{
	return (st1.St_grade_1 + st1.St_grade_2 + st1.St_grade_3) > (st2.St_grade_1 + st2.St_grade_2 + st2.St_grade_3);
}

//count number of grades in specific range 
//ex: arr = {20,40,43,50,33,70,80} -->  range =  (40,50] --> count = 2
int countNumberInRange(StudentInfo st[], int size, int start, int end) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		int total = (st[i].St_grade_1 + st[i].St_grade_2 + st[i].St_grade_3);
		if (total > start && total <= end) {
			count++;
		}
	}
	return count;
}

//9
void printHistogram(StudentInfo st[], int n)
{
	cout << "The distribution of total grades" << endl << endl;
	int bandwidth = 10;
	// 0 - 100 -->  100 is the maximum grade as given in the project's document 
	// bandwidth given 10 , so we have 10 ranges for grades
	int freq[10] = { 0 };
	//store number of students for each  range 
	for (int i = 0; i < 100; i += 10) {
		freq[i / 10] = countNumberInRange(st, n, i, i + bandwidth);
	}

	// sort array in ascending order
	sort(freq, freq + 10);
	//freq now is sorted in  ascending order


	//get distinct values from freq array  to display them on y-axis
	// Creates an empty hashset 
	unordered_set<int> s;
	for (int i = 9; i >= 0; i--) {
		// If freq[i] not present in s, then put it in s
		if (s.find(freq[i]) == s.end())
		{
			s.insert(freq[i]);
			cout.width(2);//just for style
			cout << right << freq[i] << " | ";////cout<<right : Adjust output to the right
			for (int j = 0; j < 100; j += 10) {
				if (freq[i] == countNumberInRange(st, n, j, j + bandwidth))
					cout << " * ";
				else
					cout << "   ";
			}
			cout << "\n";
		}
	}

	//  last line  ---- 
	for (int i = 0; i < 10 + 3; i++)
		cout << "---";
	cout << "\n";
	cout << "     ";


	for (int i = 10; i <= 100; i += 10) {
		cout.width(2); //just for style
		cout << right << i << " ";//cout<<right : Adjust output to the right
	}
	cout << endl;
}