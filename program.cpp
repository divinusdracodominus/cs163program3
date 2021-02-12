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