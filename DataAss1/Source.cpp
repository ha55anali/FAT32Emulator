#include <iostream>
#include <string>
#include "fileSystem.h"

using namespace std;

//checks if passed string is numeric
bool isInteger(const std::string& s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char* p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

//checks input string is numeric and within optional bounds
int checkIntInput(int lowerbound = 0, int upperbound = 0) {
	std::string temp;
	cin >> temp;
	
	while (isInteger(temp) == 0) {
		cout << "enter a number: ";
		cin >> temp;
	}

	int tempint = stoi(temp);
	if (!(lowerbound == 0 && upperbound == 0))
	{
		while (lowerbound > tempint|| tempint > upperbound) {
			cout << "enter a number within range: ";
			cin >> temp;
			tempint = stoi(temp);
		}
	}

	return tempint;
}

void showMenu() {
	cout << "1. print file system" << endl;
	cout << "2. create file" << endl;
	cout << "3. delete file" << endl;
	cout << "4. output file" << endl;
	cout << "5. exit" << endl;
}

void createFile(fileSystem* f) {
	std::string fname;
	std::string fcontent;
	cout << endl << "enter name of the file: ";
	cin >> fname;
	cout << endl << "enter content of the file: ";
	cin >> fcontent;

	try {
		f->saveFile(fname, fcontent, fcontent.size());
	}
	catch (invalid_argument & e) {
		cout << e.what() << endl;
	}
}

void deleteFile(fileSystem* f) {
	std::string fname;
	cout << endl << "enter name of the file to delete: ";
	cin >> fname;
	try {
		f->deleteFile(fname);
	}
	catch (invalid_argument & e) {
		cout << e.what() << endl;
	}
}

void outputFile(fileSystem* f) {
	std::string fname;
	cout << endl << "enter name of the file to print: ";
	cin >> fname;
	try {
		cout << "content: " << f->readFile(fname)<<endl;
	}
	catch (invalid_argument & e) {
		cout << e.what()<<endl;
	}
}

//return 1 for exit
bool performAction(fileSystem* f,int choice) {
	switch (choice)
	{
	case 1:
		cout << *f;
		break;
	case 2:
		createFile(f);
		break;
	case 3:
		deleteFile(f);
		break;
	case 4:
		outputFile(f);
		break;
	case 5:
		return 1;

	default:
		break;
	}
	return 0;
}

void main(){
	const int NoOfSectors = 10;
	const int SectorSize = 5;
	fileSystem* fS = new fileSystem(NoOfSectors,SectorSize);

	//interface
	showMenu();
	int choice;
	cout << "enter choice: ";
	choice = checkIntInput(1, 5);

	while (performAction(fS, choice) == 0) {
		showMenu();
		cout << "enter choice: ";
		choice = checkIntInput(1, 5);
	}

	delete fS;
}
