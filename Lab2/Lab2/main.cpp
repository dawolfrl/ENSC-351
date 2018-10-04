// 1) single pthread_lock
// 2) array of 1000 bools (1/thread)
// 3) self-implemented ticket lock

// What is variable all_threads_are_created?
// How do you create threads that do nothing?
// Partner?

// lock implementation
// https://www2.cs.duke.edu/courses/spring09/cps110/handouts/threads3-spring09.pdf
// thread pool
// https://softwareengineering.stackexchange.com/questions/173575/what-is-a-thread-pool

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