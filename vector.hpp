#ifndef ADT_VECTOR_H
#define ADT_VECTOR_H
#include "traits.hpp"
#include<memory>

namespace adt {
    template<typename T> struct Vector {
            Vector() {
                this->len = 0;
                this->cap = 0;
                this->data = std::unique_ptr<T[]>(nullptr);
            }
            Vector(uintptr_t length, uintptr_t capacity){
                this->len = length;
                this->cap = capacity;
                this->data = std::unique_ptr<T[]>(new T[capacity]());
            }
            /// this performs a deep copy of data of given length
            Vector(const T* content, uintptr_t length) {
                if(content == nullptr) {
                    throw nullvalue("use the default constructor, rather then attempting to construct a vector with null data");
                }
                this->len = length;
                this->cap = length;
                T* newbuf = new T[length]();
                memcpy(newbuf, content, length);
                this->data = std::unique_ptr<T[]>(newbuf);
            }
            /// this doesn't perform a copy BE CAREFUL USING THIS FUNCTION
            Vector(T* content, uintptr_t length) {
                if(content == nullptr) {
                    throw nullvalue("use the default constructor, rather then attempting to construct a vector with null data");
                }
                this->len = length;
                this->cap = length;
                this->data = std::unique_ptr<T[]>(content);
            }

            Vector<T> operator+(const Vector<T>& vec2) const {
                Vector<T> retval;
                retval.len = this->len + vec2.len;
                retval.cap = retval.len > vec2.cap || retval.len > this->cap ? retval.len : this->cap >= vec2.cap ? this->cap : vec2.cap;
                T* newbuf = new T[retval.cap]();
                memcpy(newbuf, this->data.get(), this->len);
                memcpy(newbuf + this->len, vec2.data.get(), vec2.len);
                retval.data = std::unique_ptr<T[]>(newbuf);
                return retval;
            }

            T* deconstruct() {
                this->len = 0;
                this->cap = 0;
                return this->data.release();
            }

            Vector<T>(const Vector<T>&) = delete;
            void operator=(const Vector<T>& vec) {
                T* ptr = vec.data.get();
                /// assuming this is an array wrapepr or something
                if(ptr != nullptr){
                this->cap = vec.cap;
                this->len = vec.len;
                
                    T* to_be_owned = new T[vec.cap]();
                    memcpy(to_be_owned, ptr, vec.cap);
                    this->data = std::unique_ptr<T[]>(to_be_owned);
                }else{
                    this->len = 0;
                    this->cap = 0;
                    this->data = std::unique_ptr<T[]>(nullptr);
                }
            }

            Vector<T>(Vector<T>&&) = default;
            Vector<T>& operator=(Vector<T>&&) = default;

            T& operator[](uintptr_t i) {
                if(i >= this->len || i < 0) {
                    throw outofbounds(i, this->len);
                }
                if(this->data.get() == nullptr) {
                    throw nullvalue("attempted to index into a null vector");
                }
                return this->data.get()[i];
            }
            const T& operator[](uintptr_t i) const {
                if(i >= this->len || i < 0) {
                    throw outofbounds(i, this->len);
                }
                return this->data.get()[i];
            }

            friend std::ostream& operator<<(std::ostream& os, const Vector<T>& value) {
                if(!value.data || value.data.get() == nullptr) {
                    throw nullvalue("in ostream operator << for class Vector<T> data is null");
                }
                os << value.data.get();
                return os;
            }
            friend std::istream& operator>> (std::istream& is, Vector<T>& vec) {
                if(!vec.data.get() || vec.data.get() == nullptr) {
                    throw nullvalue("cannot read into uninitialized vector");
                }
                is.ignore();
                is.getline(vec.data.get(), vec.cap);
                is.clear();
                return is;
            }

            uintptr_t length() const { return this->len; }
            uintptr_t capacity() const {return this->cap; }


        private:
            std::unique_ptr<T[]> data;
            uintptr_t len;
            uintptr_t cap;
    };
}

#endif