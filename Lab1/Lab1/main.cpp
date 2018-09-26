#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;
// global things
const int BUFFER_MAX = 10000; // maximum items in buffer
const int DATA_MAX = 120; // maximum characters to store in line of trace
struct traceStruct {
	int position; // position of trace in buffer of 10 000
	char type; // type of event
	char* name;
	char* category;
	char phase;
	void* objectID;
	long long timestamp;
	int pid;
	int tid;
	char scope;
	char* key;
	char* value;
};
ofstream json_file; // json file name/path for tracing
traceStruct traceBuffer[BUFFER_MAX]; // buffer for traces
int bufferCounter = 0; // number of traceStructs in the buffer

// function prototypes
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
* @description Generates beginning line for object events.
* @parameters [name, obj_pointer] name of object event, pointer to object in question
* @returns none
*/
void trace_object_new(char* name, void* obj_pointer);
/*
* @description Generates ending line for object events.
* @parameters [name, obj_pointer] name of object event, pointer to object in question
* @returns none
*/
void trace_object_gone(char* name, void* obj_pointer);int num_events = 0; // number of events generated
/*
* @description Generates line for counter events.
* @parameters [name, key, value] name of counter event, thing to tally, tally
* @returns none
*/
void trace_counter(char* name, char* key, char* value);
/*
* @description Dumps buffer contents into json file.
* @parameters none
* @returns none
*/
void trace_flush();
/*
* @description Closes json file.
* @parameters none
* @returns none
*/
void trace_end();
//----------------------------------------------------------------------------------
int main() {
    //char path[] = "trace.json"; // file path for lab
	char path[] = "C:\\Users\\D\\Desktop\\traceDummy.json"; // file path for DW's PC
	// dummy variables for testing
	char instant_name[] = "Instant"; // name for instant event
	char name_array[] = "Test"; // name of all events
	char cat_array[] = "Duration"; // category of all events
	char obj_name[] = "Object"; // name for object event
	char object[] = "blah";
	char counter_name[] = "Counter"; // name for counter event
	char counter_key[] = "Pepes"; // counter key
	char counter_value[] = "27"; // counter value for key
	char* filename_ptr = path; // pointer to file name/path
	char* instant_ptr = instant_name; // pointer to instant event name
	char* test_name = name_array; // pointer to event name
	char* test_cat = cat_array; // pointer to event category
	char* obj_name_ptr = obj_name; // pointer to object event name
	char* obj_ptr = object;
	char* counter_name_ptr = counter_name;
	char* counter_key_ptr = counter_key;
	char* counter_value_ptr = counter_value;
	
	// testing
	int loop = 0;
	while (loop != 20) {
		trace_start(filename_ptr); // begin output (opening square bracket)
		trace_event_start(test_name, test_cat);
		trace_event_start(test_name, test_cat);
		trace_event_start(test_name, test_cat);
		trace_object_new(obj_name_ptr, obj_ptr); // generate object event
		trace_object_gone(obj_name_ptr, obj_ptr); // end object event
		trace_counter(counter_name_ptr, counter_key_ptr, counter_value_ptr); // generate counter event
		trace_instant_global(instant_ptr); // generate instant event
		trace_event_end();
		trace_event_end();
		trace_event_end();
		trace_event_start(test_name, test_cat);
		trace_event_start(test_name, test_cat);
		trace_event_start(test_name, test_cat);
		trace_event_start(test_name, test_cat);
		trace_event_start(test_name, test_cat);
		trace_event_start(test_name, test_cat);
		trace_event_end();
		trace_event_end();
		trace_event_end();
		trace_event_end();
		trace_event_end();
		trace_event_end();
		loop++;
	}
	trace_flush();
	trace_end(); // end output (closing square bracket)
	return 0;
}
//----------------------------------------------------------------------------------
// function definitions
void trace_start(char* filename) {
	json_file.open(filename); // open json file
	json_file << "[\n"; // opening bracket for trace file
}
void trace_event_start(char* name, char* categories) {
	// internal info
	traceBuffer[bufferCounter].position = bufferCounter + 1; // line number
	traceBuffer[bufferCounter].type = 'S'; // S = start
	// event info
	traceBuffer[bufferCounter].name = name;
	traceBuffer[bufferCounter].category = categories;
	traceBuffer[bufferCounter].phase = 'B';
	traceBuffer[bufferCounter].timestamp = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
	traceBuffer[bufferCounter].pid = 1;
	traceBuffer[bufferCounter].tid = 1;
	bufferCounter++;
}
void trace_event_end() {
	// internal info
	traceBuffer[bufferCounter].position = bufferCounter + 1; // line number
	traceBuffer[bufferCounter].type = 'E'; // E = end
	// event info
	traceBuffer[bufferCounter].phase = 'E';
	traceBuffer[bufferCounter].timestamp = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
	traceBuffer[bufferCounter].pid = 1;
	traceBuffer[bufferCounter].tid = 1;
	bufferCounter++;
}
void trace_instant_global(char* name) {
	// internal info
	traceBuffer[bufferCounter].position = bufferCounter + 1; // line number
	traceBuffer[bufferCounter].type = 'I'; // I = instant
	// event info
	traceBuffer[bufferCounter].name = name;
	traceBuffer[bufferCounter].phase = 'i';
	traceBuffer[bufferCounter].timestamp = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
	traceBuffer[bufferCounter].pid = 1;
	traceBuffer[bufferCounter].tid = 1;
	traceBuffer[bufferCounter].scope = 'g'; // g = global
	bufferCounter++;
}
void trace_object_new(char* name, void* obj_pointer){
	// internal info
	traceBuffer[bufferCounter].position = bufferCounter + 1; // line number
	traceBuffer[bufferCounter].type = 'N'; // N = object new
	// event info
	traceBuffer[bufferCounter].name = name;
	traceBuffer[bufferCounter].phase = 'N';
	traceBuffer[bufferCounter].objectID = obj_pointer;
	traceBuffer[bufferCounter].timestamp = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
	traceBuffer[bufferCounter].pid = 1;
	traceBuffer[bufferCounter].tid = 1;
	bufferCounter++;
}
void trace_object_gone(char* name, void* obj_pointer){
	// internal info
	traceBuffer[bufferCounter].position = bufferCounter + 1; // line number
	traceBuffer[bufferCounter].type = 'G'; // G = object gone
	// event info
	traceBuffer[bufferCounter].name = name;
	traceBuffer[bufferCounter].phase = 'D';
	traceBuffer[bufferCounter].objectID = obj_pointer;
	traceBuffer[bufferCounter].timestamp = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
	traceBuffer[bufferCounter].pid = 1;
	traceBuffer[bufferCounter].tid = 1;
	bufferCounter++;
}
void trace_counter(char* name, char* key, char* value){
	// internal info
	traceBuffer[bufferCounter].position = bufferCounter + 1; // line number
	traceBuffer[bufferCounter].type = 'C'; // C = counter
	// event info
	traceBuffer[bufferCounter].name = name;
	traceBuffer[bufferCounter].phase = 'C';
	traceBuffer[bufferCounter].timestamp = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count();
	traceBuffer[bufferCounter].pid = 1;
	traceBuffer[bufferCounter].tid = 1;
	traceBuffer[bufferCounter].key = key; // argument
	traceBuffer[bufferCounter].value = value; // argument
	bufferCounter++;
}
void trace_flush() {
	int i = 0;
	while (i != bufferCounter) {
		json_file << "{"; // opening brace
		if (traceBuffer[i].type != 'E') {
			json_file << "\"name\": \"" << traceBuffer[i].name << "\", "; // name
			if (traceBuffer[i].type == 'S') {
				json_file << "\"cat\": \"" << traceBuffer[i].category << "\", "; // category
			}
		}
		json_file << "\"ph\": \"" << traceBuffer[i].phase << "\""; // phase
		if (traceBuffer[i].type == 'N') {
			json_file << ", \"id\": \"" << traceBuffer[i].objectID << "\""; // object ID
		}
		json_file << ", \"ts\": " << traceBuffer[i].timestamp; // timestamp
		json_file << ", \"pid\": " << traceBuffer[i].pid; // process ID
		if (traceBuffer[i].type == 'C') {
			json_file << ", \"args\": {\"" << traceBuffer[i].key << "\": " << traceBuffer[i].value << "}"; // arguments (counter)
		}
		else {
			json_file << ", \"tid\": " << traceBuffer[i].tid; // thread ID
		}
		if (traceBuffer[i].type == 'I') {
			json_file << ", \"s\": \"" << traceBuffer[i].scope << "\""; // scope
		}
		json_file << "}," << endl; // closing brace and newline
		i++;
	}
	memset(&traceBuffer, 0, bufferCounter);
	bufferCounter = 0; // reset buffer
}
void trace_end() {
	json_file << "{}]"; // extra curlies to offset comma problem, closing bracket for trace file
	json_file.close(); // close json file
}