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
    HashTable<CppString, Animal> table(2000);
    CLLQueue<CppString> keys;
    for(int t = 0; t < 10; t++){
        std::thread obj([&table, &keys]() {
            mutex thdlocker;
            for(int i = 0; i < 1000; i++){
                CppString street = CppString::random(rand() % 20);
                CppString city = CppString::random(rand() % 20);
                CppString state = CppString::random(rand() % 20);
                CppString country = CppString::random(rand() % 20);
                int zip_code = rand() % 99950;
                Address addr(street, city, state, country, zip_code);
                /// it could be fun to read breeds, names, etc from an external data file
                CppString name = CppString::random(rand() % 20);
                CppString breed = CppString::random(rand() % 20);
                CppString species = CppString::random(rand() % 20);
                CppString desc = CppString::random(rand() % 40);
                CppString link = CppString::random(rand() % 30);
                Animal subject(name, breed, species, addr, desc, link);
                CppString key = name + breed;
                thdlocker.lock();
                if(zip_code > 1000){
                    keys.enqueue(key);
                }
                table.insert(key, subject);
                thdlocker.unlock();
            }
        });
        obj.join();
    }
    CppString search_key;
    int value = keys.dequeue(search_key);
    while(value > 0) {
        Animal back;
        try {
            table[search_key].unwrap().display();
        } catch (exception e) {
            cout << "failed to get value";
        }
        value = keys.dequeue(search_key);
    }
    cout << "about to clean up" << endl;
}

void test_queue() {
    Queue<CppString> test;
    for(int i = 0; i < 100000; i++) {
        CppString contents = CppString::random(rand() % 100);
        test.enqueue(contents);
    }
    for(int i = 0; i < 1000; i++){
        CppString contents;
        if(test.dequeue(contents) > -1) {
            cout << contents << endl;
        }else{
            cout << "queue is void" << endl;
        }
    }
}

int main() {
    signal(SIGSEGV, segfault_handler);
    better_test();
}