#include <iostream>
#include <sstream>
#include <thread>
#include <shared_mutex>
#include <atomic>

unsigned const short int w = 2; //amount of writers
unsigned const short int r = 5; //amount of reader
unsigned const short int iterations = 5; //amount of iterations

std::shared_timed_mutex global_mutex;

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
        global_mutex.lock_shared();

        readerPrint();
        count++;

        global_mutex.unlock_shared();
    }
}

void writers(int &count) {
    for (int i = 0; i < iterations; ++i) {
        global_mutex.lock();

        writerPrint();
        count++;

        global_mutex.unlock();
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
