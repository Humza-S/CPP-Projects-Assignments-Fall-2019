/*
	Name: Humza Salman
	NET ID: MHS180007
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

void parseLine(string **arr, string line, int x, int y);
void printArray(string** arr, int x, int y);
string** updateArraySize(string** arr, int newRow, int oldRow, int cols);
double findTestScore(string** key, string** student, int row, int y);
string findLetterGrade(double grade);
void printGrade(string** arr, int rows, int cols, ostream& output);

//constant global variables
int const STUDENT_ARRAY_COLS = 23; // 1 for name, 20 for answers, 1 for grade, 1 for letter grade | 1 + 20 + 1 + 1= 23 total 

int main()
{
	ifstream inputFile;
	ofstream outputFile;

	int r = 0; //always have at least one row in array

	//dyanmic arrays
	string** keyArray = nullptr;
	string** studentArray = new string*[r + 1];
	studentArray[0] = new string[STUDENT_ARRAY_COLS]; //initialize array with expectation of at least one student

	/*for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 1; j++) {
			dynamicArray[i][j] = "C";
		}
	}
	cout << "Initial Array : " << endl;
	printArray(dynamicArray, 1, 1);

	dynamicArray = updateArraySize(dynamicArray, 3, 3, 1);
	
	cout << "Updated Array Size: " << endl;
	
	printArray(dynamicArray, 3, 3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			dynamicArray[i][j] = "A";
		}
	}
	cout << "Updated Array : " << endl;
	printArray(dynamicArray, 3, 3);*/


	inputFile.open("answers.txt");

	if (inputFile) {
		//read in answers to first row
		string answers;
		getline(inputFile, answers);
		keyArray = new string * [1];
		keyArray[0] = new string[answers.length()];
		parseLine(keyArray, answers, r, 0);		

		while (!inputFile.eof()) {
			//gets line from input and stores it
			string line;
			getline(inputFile, line);

			//checks if last line is empty, if true then breaks
			if (line.empty())
				break;

			//updates the rows in the student array to account for next possible student
			studentArray = updateArraySize(studentArray, r + 1, r, STUDENT_ARRAY_COLS);

			//finds gap index between name and student answers
			int gapIndex = line.find(" ");

			//parses student name from the line and stores it into the array
			*(*(studentArray + r) + 0) = line.substr(0, gapIndex);
			
			//parses student answers from the line and then parses those answers
			//and stores them in the student array
			parseLine(studentArray, line.substr(gapIndex + 1), r, 1);

			//finds grade
			double grade = findTestScore(keyArray, studentArray, r, STUDENT_ARRAY_COLS);

			//stores grade and letter grade in student array
			*(*(studentArray + r) + 21) = to_string(grade); //grade
			*(*(studentArray + r) + 22) = findLetterGrade(grade); //letter grade

			//increments rows to have in student array
			r++;
		}
	}
	
	//closes input
	inputFile.close();

	//opens output file and outputs the name, grade, and letter grade;
	//then closes output file
	outputFile.open("graded.txt");
	printGrade(studentArray, r, STUDENT_ARRAY_COLS, outputFile);
	outputFile.close();
}

void parseLine(string** arr, string line, int row, int col)
{
	string* ptr = &arr[row][col]; //give pointer address of first insertion in specified row
	for (char ch : line) {
		*ptr = ch; //dereference pointer to change the value at the pointer address
		ptr++; //increment address of pointer to go to next insertion
	}
}

//function used to print desired array
void printArray(string** arr, int rows, int cols) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			//inside pointer gets row address, then the outside pointer 
			//prints columns
			cout << "[" << *(*(arr + r) + c) << "]";
		}
		cout << endl;
	}
	cout << endl;
}

void printGrade(string** arr, int rows, int cols, ostream& output) {
	output << setprecision(2) << fixed;
	for (int r = 0; r < rows; r++) {
		//alternative method for printing grades
		/*for (int c = 0; c < cols; c++) {
			if(c == 0 || c == 22)
				output << *(*(arr + r) + c);
			if (c == 21)
				output << "	" << (stod(*(*(arr + r) + c))) << "%	";
		}*/

		//prints out name, grade, and letter grade
		output << *(*(arr + r) + 0); //name
		output << "	" << stod(*(*(arr + r) + 21)) << "%" << "	"; //grade
		output << *(*(arr + r) + 22); //letter grade
		output << endl;
	}
}

string** updateArraySize(string** arr, int newRow, int oldRow, int cols) {

	//allocate temporary array
	string** tempArr = new string * [newRow];
	for (int i = 0; i < newRow; i++) {
		tempArr[i] = new string[STUDENT_ARRAY_COLS];
	}
	
	//copy arr to temp
	string* tempPtr = &tempArr[0][0];
	string* arrPtr = &arr[0][0];
	for (int r = 0; r < oldRow; r++) {
		for (int c = 0; c < cols; c++) {
			//gets value at address and copies it 
			//from the old array into new array
			*(*(tempArr + r) + c) = *(*(arr + r) + c);
		}		
	}

	//deallocate arr
	for (int i = 0; i < oldRow; i++) {
		delete[] arr[i];
	}
	delete[] arr;

	return tempArr;
}

double findTestScore(string** key, string**student, int row, int cols)
{
	double points = 0;
	for (int c = 1; c < cols - 2; c++) {
		if (*(*(student + row) + c) == *(*(key) + c - 1))
			points += 2;
		else if (*(*(student + row) + c) == " ")
			points += 0;
		else if (*(*(student + row) + c) != *(*(key) + c - 1))
			points -= 1;
	}
	double grade = points / 40 * 100;
	return grade;
}

string findLetterGrade(double grade)
{
	if (grade <= 100 && grade >= 90)
		return "A";
	else if (grade <= 89.99 && grade >= 80)
		return "B";
	else if (grade <= 79.99 && grade >= 70)
		return "C";
	else if (grade <= 69.99 && grade >= 60)
		return "D";
	else if (grade <= 59.99)
		return "F";
}
