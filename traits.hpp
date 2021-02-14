#ifndef TRACE_TRAITS_H
#define TRACE_TRAITS_H
/*
    Julian Lazaras
    1/21/21
    the purpose of this file is to provide convenience types that allow the other components
    of this project to take on a more object oriented approach, comparate to the imperitive approach that is
    often employed.

    content:
    nullvalue // an except class for throwing a c++ version of a null pointer exception
    ItemState
    accessdenied // some dumb errors, like attempting to access private data
    outofboumds //used to denote a failure in overloading the [] operator
    Collection // defines shared behavior in the same way as a rust trait for the purpose of in the future practicing the use of RTTI
*/

#include<iostream>
#include<cstring>
#include<exception>
#include<typeinfo>
#include<sstream>
#include "adt.hpp"

const char* get_message(uintptr_t, uintptr_t);
/// this is a use of classes conceptually similiar to rust's traits
namespace adt {
    class Hash {
        public:
            virtual uintptr_t hash() const {
                return 0;
            }
    };

    /// I didn't put another file because this types are so tiny
    class nullvalue: public std::exception {
        public:
            nullvalue(const char* msg) {
                this->message = msg;
            }
            virtual const char* what() const throw() {
                return this->message;
            }
        private:
            const char* message;
    };

    enum class Tag {
        Empty,
        Full,
    };
    /// the use of the struct keyword makes me happier then the class keyword, because 
    /// I associate classes with bad programming found in non rust languages, but since rust
    /// doesn't use that keyword I have come to use structs in the same way, thus the keyword struct
    /// makes me happy, and since I am specifying what is public, and private manually
    /// it really doesn't make a difference what keyword I use (look it up, that is I believe the only difference)
    template<typename T> struct ItemState {
        public:
            friend std::ostream& operator<<(std::ostream& os, const ItemState& value){
                if(value.tag == adt::Tag::Empty){
                    os << "None";
                }else{
                    os << value.full;
                }
                return os;
            }
            ItemState(){
                this->tag = Tag::Empty;
            }
            void operator = (const ItemState<T>& state){
                this->tag = state.tag;
                this->full = state.full;
            }
            ItemState(const ItemState<T>& state){
                this->tag = state.tag;
                this->full = state.full;
            }
            ~ItemState(){}
            ItemState(T& value){
                this->tag = Tag::Full;
                this->full = &value;
            }
            bool operator ==(const ItemState<T>& str2){
                if(this->tag == str2.tag && this->tag == Tag::Empty) {
                    return true;
                }
                if(this->tag == Tag::Full && str2.tag == Tag::Full){
                    if(this->full == str2.full){
                        return true;
                    }
                }
                return false;
            }

            T& unwrap() {
                if(this->tag == Tag::Empty){
                    throw nullvalue("attempted to call unwrap on an empty value");
                }
                return *this->full;
            }

            template<typename A> A map_or_else(A (*on_failure)(), A (*on_success)(T&)){
                if(this->tag == Tag::Empty){
                    return (*on_failure)();
                }else{
                    return (*on_success)(this->full);
                }
            }
        private:
            Tag tag;
            T* full;
    };

    /// I use classes her because I don't need to linker/cbindgen to be able to tell if the rust version of the type exists
    /// and fundementally this concept of exception handiling isn't a functional one, rather it is an OOP one.
    class outofbounds: public std::exception 
    {
        public:
            outofbounds(uintptr_t index, uintptr_t length){
                this->index = index;
                this->length = length;
            }
            // soem callsite tracing would be nice, and I guess I could use backtrace, but that's annoying
            virtual const char* what() const throw() {        
                return get_message(this->index, this->length);
            }
        private:
            void * operator new(size_t size);
            uintptr_t index;
            uintptr_t length;
    };

    class accessdenied: public std::exception {
        public:
            accessdenied(const char* message) {
                this->message = message;
            }
            virtual const char* what() const throw(){
                return this->message;
            }
        private:
            const char* message;
    };

    class unimplemented: public std::exception {
        public:
            unimplemented(const char* msg){
                this->message = msg;
            }
            virtual const char* what() {
                return this->message;
            }
        private:
            const char* message;
    };

    template<typename T> class Collection {
        public:
        virtual uintptr_t length() const {
            throw unimplemented("base implementation of function Collection::length is not allowed");
        }
        virtual T pop() {
            throw unimplemented("base implementation of function Collection::pop is not allowed");
        }
        virtual void push(T data) {
            throw unimplemented("base implementation of function Collection::push is not allowed");
        }
        virtual const T& operator[](uintptr_t index) const {
            throw unimplemented("base implementation of function Collection::operator[] is not allowed");
        }
        virtual T& operator[](uintptr_t index){
            throw unimplemented("base implementation of function Collection::operator[] is not allowed");
        }
    };
}

#endif