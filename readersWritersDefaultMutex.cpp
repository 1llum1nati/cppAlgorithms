
#include <iostream>
#include <sstream>
#include <thread>
#include <atomic>
#include <mutex>

unsigned const short int w = 2; //amount of writers
unsigned const short int r = 5; //amount of reader
unsigned const short int iterations = 5; //amount of iterations

std::atomic<int > readCount;

std::mutex resourse_access;
std::mutex readCount_access;
std::mutex queue_access;

void readerPrint() {
	std::stringstream msg;
	msg << "Reader " << std::this_thread::get_id() << " works " << "\n";
	std::cout << msg.str();
}

void writerPrint() {
	std::stringstream msg;
	std::cout << "Writer " << std::this_thread::get_id() << " works\n";
	std::cout << msg.str();
}

void readers(int &count) {
	for (int i = 0; i < iterations; ++i) {
        bool currentCreated = false;
        queue_access.lock(); //Enter
            readCount_access.lock();

            if (readCount == 0) {
                std::lock_guard<std::mutex> lock(resourse_access);
            }
	    readCount++;
            readCount_access.unlock();

	queue_access.unlock();

	    readerPrint(); //Some action
            count++;

	readCount_access.lock(); //Exit

		readCount--;
        
        readCount_access.unlock();
	}
}

void writers(int &count) {
	for (int i = 0; i < iterations; ++i) {
	queue_access.lock(); //Enter

        resourse_access.lock();

        queue_access.unlock();

        writerPrint(); //Some action
        count++;

        resourse_access.unlock(); //Exit 
	}
}

int main() {
    int allOperations = 0; //to count all operations, allOperation = (w + r) * iterations
    if (w > 0 && r > 0 && iterations > 0) {
        std::thread writersPool[w];
        std::thread readersPool[r];

        for (int i = 0; i < w; i++) {
            writersPool[i] = std::thread(writers, std::ref(allOperations));
        }

        for (int i = 0; i < r; i++) {
            readersPool[i] = std::thread(readers, std::ref(allOperations));
        }

        for (int i = 0; i < w; ++i) {
            writersPool[i].join();
        }

        for (int i = 0; i < r; ++i) {
            readersPool[i].join();
        }

        std::cout << allOperations;
    }
    getchar();
	return 0;
}
