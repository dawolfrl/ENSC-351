// 1) single pthread_lock
// 2) array of 1000 bools (1/thread)
// 3) self-implemented ticket lock

// What is variable all_threads_are_created?
// How do you create threads that do nothing?
// Partner?

#include <iostream>
#include <thread>
using namespace std;

const int NUM_THREADS = 1000;
int door = 0; // door counter
bool all_threads_created = false; // status to keep threads spinning
thread threadArray[NUM_THREADS]; // all threads (thread pool?)

void setup(thread *array) {
	int i = 0; // thread creation counter
	while (i < NUM_THREADS) {
		array[i] = thread (); // create a thread
		i++; // incrememnt thread creation counter
	}
}
void getLock() {
	enterDoor();
}
void enterDoor() {
	door++;
}

int main() {
	setup(threadArray); // create threads
	// try pthread_lock
	return 0;
}