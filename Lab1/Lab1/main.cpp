// TO DO
// - create functions for other event types
//		- void trace_object_new(char* name, void* obj_pointer);
//		- void trace_object_gone(char* name, void* obj_pointer);
//		- void trace_counter(char* name, char* key, char* value);
// - fix comma delimiter
// - implement buffer for dumping traces
// - implement flushing mechanism
//		- void trace_flush();
// - implement argument capabilities?
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;
// global things
ofstream json_file; // json file name/path for tracing
int reps = 9; // number of events to generate - 1
int iters = 0; // number of events generated

// function prototypes
/*
* @description Generates dummy events for testing.
* @parameters [a, b] a > b, number of events generated is a + 1
* @returns none
*/
int recursion(int a, int b);
/*
* @description Opens json file for tracing.
* @parameters [filename] pointer to file name/path
* @returns none
*/
void trace_start(char* filename);
/*
* @description Generates the beginning line for duration events.
* @parameters [name, categories] name is the name of the event, category is its category
* @returns none
*/
void trace_event_start(char* name, char* categories);
/*
* @description Generates ending line for duration events.
* @parameters none
* @returns none
*/
void trace_event_end();
/*
* @description Generates line for instant events.
* @parameters [name] name of instant event
* @returns none
*/
void trace_instant_global(char* name);
/*
* @description Closes json file.
* @parameters none
* @returns none
*/
void trace_end();
//----------------------------------------------------------------------------------
int main() {
	char path[] = "C:\\Users\\D\\Desktop\\trace.json"; // file path
	char instant_name[] = "Instant"; // name for instant event
	char* filename_ptr = path; // pointer to file name/path
	char* instant_ptr = instant_name; // pointer to instant event name
	
	trace_start(filename_ptr); // begin output (opening square bracket)
	
	trace_instant_global(instant_ptr); // generate instant event
	recursion(reps, 0); // generate events (reps + 1)

	trace_end(); // end output (closing square bracket)
	return 0;
}
//----------------------------------------------------------------------------------
// function definitions
int recursion(int a, int b) {
	char name_array[] = "Test"; // name of all events
	char cat_array[] = "Duration"; // category of all events
	char* test_name = name_array; // pointer to event name
	char* test_cat = cat_array; // pointer to event category

	trace_event_start(test_name, test_cat); // generate duration event beginning line
	if (a == 0) {
		trace_event_end(); // generate duration event ending line
		return b;
	}
	else {
		int result = recursion(a - 1, b + 1);
		trace_event_end(); // generate duration event ending line
		return result;
	}
}
void trace_start(char* filename) {
	json_file.open(filename); // open json file
	json_file << "[\n"; // opening bracket for trace file
}
void trace_event_start(char* name, char* categories) {
	json_file << "{"; // opening brace
	json_file << "\"name\": \"" << name << "\", "; // name
	json_file << "\"cat\": \"" << categories << "\", "; // category
	json_file << "\"ph\": \"B\", "; // phase
	json_file << "\"ts\": "; // timestamp
	json_file << chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
	json_file << ", ";
	json_file << "\"pid\": 1, "; // process ID
	json_file << "\"tid\": 1"; // thread ID
	json_file << "}," << endl; // terminate line with closing brace and comma
}
void trace_event_end() {
	iters += 1; // increment event counter
	json_file << "{"; // opening brace
	json_file << "\"ph\": \"E\", "; // phase
	json_file << "\"ts\": "; // timestamp
	json_file << chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
	json_file << ", ";
	json_file << "\"pid\": 1, "; // process ID
	json_file << "\"tid\": 1"; // thread ID
	json_file << "}"; // closing brace
	if (iters < (reps + 1)) {
		json_file << ","; // terminate line with comma if not the last line in trace
	}
	json_file << endl; // newline
}
void trace_instant_global(char* name) {
	json_file << "{"; // opening brace
	json_file << "\"name\": \"" << name << "\", "; // name
	json_file << "\"ph\": \"i\", "; // phase
	json_file << "\"ts\": "; // timestamp
	json_file << chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
	json_file << ", ";
	json_file << "\"pid\": 1, "; // process ID
	json_file << "\"tid\": 1, "; // thread ID
	json_file << "\"s\": \"g\""; // scope
	json_file << "}," << endl; // terminate line with closing brace and comma
}
void trace_end() {
	json_file << "]"; // closing bracket for trace file
	json_file.close(); // close json file
}