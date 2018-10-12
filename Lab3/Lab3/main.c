#include "stdio.h"
#include "string.h"

void processInput(char *filename);
void map();
void reduce();
void print();

int main() {
	char data[] = "data.txt";
	// array for strings?
	// array for key-value pairs?
	// array for reduced key-value pairs?
	processInput(data);

	return 0;
}

void processInput(char *filename) {
	FILE *fileptr;
	fileptr = fopen(filename,"r");
	// read lines and separate words
	fclose(fileptr);
}
void map() {
	// create key-value pair for each word
	// value = 1 for all words
}
void reduce() {
	// collapse key-value pairs of the same word
	// value = count of the particular word
}
void print() {
	// output collapsed key-value pairs
}
