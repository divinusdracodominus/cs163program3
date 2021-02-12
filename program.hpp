#ifndef ADT_TEST_PROGRRAM_H
#define ADT_TEST_PROGRAM_H
#include "adt.hpp"
struct Address {
    public:
        Address() {}
        /// copies the data in
        Address(adt::CppString& street, adt::CppString& city, adt::CppString& state, int zip);
        /// moves in, or takes ownership of existing types
        Address(adt::CppString street, adt::CppString city, adt::CppString state, int zip, bool ignore);
        Address(const Address&) = delete;
        void display();
        //void operator=(const Address&) = default;
    private:
        adt::CppString street;
        adt::CppString city;
        adt::CppString state;
        int zip_code;
};

struct Animal {
        Animal() {}
        Animal(adt::CppString& name, adt::CppString& breed, Address& location, adt::CppString& description, adt::CppString& link);
        void display();
        //Animal(adt::CppString name, adt::CppString breed, Address location, adt::CppString description, adt::CppString link);
        Animal(const Animal&) = delete;
        //operator=(const Animal&) = default;
    private:
        adt::CppString name;
        adt::CppString breed;
        Address location;
        adt::CppString description;
        /// I am tempted to implement as Vector<[uint8_t;3]> but that would require a jpg encoder
        adt::CppString link;
};

#endif