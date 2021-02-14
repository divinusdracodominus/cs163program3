#include "program.hpp"
using namespace adt;
using namespace std;
Address::Address(CppString& strt, CppString& cit, CppString& st, CppString& c, int zip) {
    this->street = strt;
    this->city = cit;
    this->state = st;
    this->country = c;
    this->zip_code = zip;
}

void Address::display() const {
    cout << "street: " << this->street << endl;
    cout << "city: " << this->city << endl;
    cout << "state: " << this->state << endl;
    cout << "country: " << this->country << endl;
    cout << "zip code: " << this->zip_code << endl;
}

Animal::Animal(adt::CppString& n, adt::CppString& b, adt::CppString& s, Address& addr, adt::CppString& desc, adt::CppString& l) {
    this->name = n;
    this->breed = b;
    this->species = s;
    this->location = addr;
    this->description = desc;
    this->link = l;
}

void Animal::display() const {
    cout << "name: " << this->name << endl;
    cout << "breed: " << this->breed << endl;
    cout << "species: " << this->species << endl;
    cout << "location: " << endl;
    this->location.display();
    cout << "description: " << this->description << endl;
    cout << "link: " << this->link << endl;
    this->location.display();
}