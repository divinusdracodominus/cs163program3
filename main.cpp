#include "program.hpp"
#include<csignal>
#include<thread>
#include<execinfo.h>
#include<mutex>
using namespace adt;
using namespace std;

void segfault_handler(int signum){
    void* buffer[8];
    int backtrace_len = backtrace(buffer, 8);
    char** messages = backtrace_symbols(buffer, backtrace_len); 
    for(int i = 2; i < backtrace_len; i++){
        cout << messages[i] << endl;
    }
    exit(-1);
}

void better_test() {
    HashTable<CppString, Address> test(2000);
    Queue<CppString> queue;
    for(int t = 0; t < 100; t++){
        std::thread obj([&test, &queue]() {
            mutex thdlocker;
            for(int i = 0; i < 10000; i++){
                CppString street = CppString::random(rand() % 100);
                CppString city = CppString::random(rand() % 100);
                CppString state = CppString::random(rand() % 100);
                int zip_code = rand() % 99950;
                Address addr(street, city, state, zip_code);
                CppString key = street + city;
                thdlocker.lock();
                if(zip_code < 1000){
                    queue.enqueue(key);
                }
                test.insert(key, addr);
                thdlocker.unlock();
            }
        });
        obj.join();
    }
    CppString search_key;
    int value = queue.dequeue(search_key);
    while(value > 0) {
        Address back;
        if(test.get(search_key, back)) {
            back.display();
        }else{
            cout << "failed to get match" << endl;
        }
        value = queue.dequeue(search_key);
    }
}

int main() {
    signal(SIGSEGV, segfault_handler);
    better_test();
}