#include "program.hpp"
using namespace adt;
using namespace std;
Address::Address(CppString& strt, CppString& cit, CppString& st, int zip) {
    this->street = strt;
    this->city = cit;
    this->state = st;
    this->zip_code = zip;
}

Address::Address(CppString strt, CppString cit, CppString st, int zip, bool ignore) {
    this->street = strt;
    this->city = cit;
    this->state = st;
    this->zip_code = zip;
}

void Address::display() {
    cout << "street: " << this->street << endl;
    cout << "city: " << this->city << endl;
    cout << "state: " << this->state << endl;
    cout << "zip code: " << this->zip_code << endl;
}

Animal::Animal(adt::CppString& n, adt::CppString& b, Address& addr, adt::CppString& desc, adt::CppString& l) {
    this->name = n;
    this->breed = b;
    this->location = addr;
    this->description = desc;
    this->link = l;
}

void Animal::display() {
    cout << "name: " << this->name << endl;
    cout << "breed: " << this->breed << endl;
    cout << "location: " << endl;
    this->location.display();
    cout << "description: " << this->description << endl;
    cout << "link: " << this->link << endl;
    this->location.display();
}