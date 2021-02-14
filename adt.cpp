#include "adt.hpp"
#include<stdlib.h>
using namespace std;
namespace adt {

CppString::CppString(const char* msg) {
    uintptr_t length = strlen(msg)+1;
    char* newbuf = new char[length]();
    strcpy(newbuf, msg);
    this->contents = Vector<char>(newbuf, length);
}

CppString CppString::operator+(const CppString& str1) const {
    CppString retval;
    retval.contents = this->contents + str1.contents;
    return retval;
}

std::ostream& operator<<(std::ostream& os, const CppString& value) {
    os << value.contents;
    return os;
}
std::istream& operator>> (std::istream& is, CppString& str) {
    is >> str.contents;
    return is;
}

bool CppString::operator !=(CppString& str2) const {
    if(this->contents.length() != str2.contents.length()) {
        return true;
    }
    for(int i = 0; i < str2.contents.length(); i++){
        if(this->contents[i] != str2.contents[i]){
            return true;
        }
    }
    return false;
}
bool CppString::operator ==(CppString& str2) const{
    return !(*this != str2);
}

CppString CppString::operator+(uintptr_t num) const {
    char buffer[10];
    sprintf(buffer, "%d", num);
    return *this + CppString((const char*)buffer);
}

uintptr_t CppString::hash() const {
    uintptr_t retval = 1;
    for(uintptr_t i = 0; i < this->contents.length(); i++){
        retval += this->contents[i];
        //std::cout << "in the loop" << std::endl;
    }
    return retval;
}

CppString CppString::random(uintptr_t length) {
    CppString retval;
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const size_t max_index = strlen(charset)-1;
    retval.contents = Vector<char>(length+1, length+1);
    for(uintptr_t i = 0; i < length; i++){
        retval.contents[i] = charset[ rand() % max_index ];
    };
    retval.contents[length] = '\0';
    return retval;
}

}

const char* get_message(uintptr_t index, uintptr_t length) {
    adt::CppString first("index out of bounds, the index is: ");
    adt::CppString second(" but the lengths is: ");
    return (first + index + second + length).deconstruct();
}