#include <iostream>
#include <fstream>
using namespace std;

void processInput(char *filename);
void map();
void reduce();
void output();

int main() {
	char dataFile[] = "data.txt";
	processInput(dataFile);
	return 0;
}

void processInput(char *filename) {
	ifstream file;
	file.open(filename);
	char letter = NULL;
	while (!file.eof()) {
		file >> letter;
		if (letter == ' ') {
			letter = '!';
		}
		cout << letter;
	}
}
void map() {
}
void reduce() {
}
void output() {
}