//============================================================================
// Name        : 12_atomic.cpp
// Author      : 
// Version     :
// Copyright   : Steal this code!
// Description : Hello World in C++, Ansi-style
//============================================================================

using namespace std;
#include <thread>
#include <atomic>
#include <iostream>
#include <vector>

struct AtomicCounter {
	std::atomic<int> value;

	AtomicCounter() : value(0) {}

	void increment(){
		++value;
	}

	void decrement(){
		--value;
	}

	int get(){
		return value.load();
	}
};

struct BadCounter {
	int value;

	BadCounter() : value(0) {}

	void increment(){
		value++;
	}

	void decrement(){
		--value;
	}

	int get(){
		return value;
	}
};


//////////////////////////////
//AtomicCounter counter;
BadCounter counter;
const int TOTAL_THREADS				=20;
const int TOTAL_COUNTS_PER_THREAD	= 5000;

void thrdfunc(){
	for(int i = 0; i < 5000; ++i){
		counter.increment();
	}
}

int main(){
	
	//create a bunch of threads
	std::vector<std::thread> threads;
	for(int i = 0; i < 20; ++i){
		threads.push_back(std::thread(thrdfunc));
	}


	//wait for em to finish
	for(auto& thread : threads){
		thread.join();
	}

	//whats the count
	std::cout <<"The count is "<< counter.get()<<" , It should be "<<(TOTAL_THREADS* TOTAL_COUNTS_PER_THREAD) << std::endl;

	return 0;
}
