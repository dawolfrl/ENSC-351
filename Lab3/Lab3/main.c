#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void processInput(char *filename, char *tokenarrayptr);
void map();
void reduce();
void print();

int main() {
    printf("beginning main function...\n");

	char data[] = "data.txt"; // file name
	char wordArray[256];// array for tokenized text
	char *wordArrayptr = &wordArray;
	// array for key-value pairs?
	// array for reduced key-value pairs?
	processInput(data,wordArrayptr);

    printf("ending main function...\n");
	return 0;
}

void processInput(char *filename, char *tokenarrayptr) {
    printf("beginning processInput function...\n");

    char filechar;
	FILE *fileptr; // file type pointer
	char line[256]; // array to store line from file
	char token[50]; // array to store token
    int tokenArrayIterator = 0;

	fileptr = fopen(filename,"r"); // open file for reading
    if(fileptr == NULL){
        perror(">> Error opening file");
        return(-1);
    }

	while(!feof(fileptr)){
        fgets(line,20,fileptr);
        token = strtok(line," ");
        tokenarrayptr[tokenArrayIterator] = token;
        tokenArrayIterator++;
	}

	fclose(fileptr); // close file
	printf("ending processInput function...\n");
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
