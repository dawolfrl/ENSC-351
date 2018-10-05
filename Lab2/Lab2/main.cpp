// 1) single pthread_lock
// 2) array of 1000 bools (1/thread)
// 3) self-implemented ticket lock

#include <iostream>
#include <thread>
using namespace std;

const int NUM_THREADS = 5; // number of threads
int i = 0; // thread creation counter
int door = 0; // door counter
bool all_threads_created = false; // status to keep threads spinning
thread threadArray[NUM_THREADS]; // all threads (thread pool?)

void setup(thread *array);
void spin();
void enterDoor();

int main() {
	setup(threadArray); // create threads
	return 0;
}

void setup(thread *array) {
	while (i < NUM_THREADS) {
		array[i] = thread(spin); // create a thread
		cout << "Thread created: " << i << endl; // output check
		i++; // incrememnt thread creation counter
	}
}
void spin(){
	while(all_threads_created == false){
		// spin lock; do nothing
		cout << "Spinning..." << endl;
		if (i == NUM_THREADS){
			all_threads_created = true;
			cout << "All threads created" << endl;
		}
	}
	while (i != 0){
		i--;
		threadArray[i].join();
	}
	cout << "Lock acquired" << endl;
}
void enterDoor() {
	door++; // count number passed
	cout << door << endl;
}
