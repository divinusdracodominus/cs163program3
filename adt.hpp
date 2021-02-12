#ifndef ADT_QUEUE_TABLE_H
#define ADT_QUEUE_TABLE_H
#include "vector.hpp"
#include<iostream>
#include<type_traits>
//using CppString = adt::Vector<char>;
namespace adt {
    struct CppString: Hash {
            CppString(const CppString&) = delete;
            CppString() {}
            CppString(const char* msg);
            CppString operator+(const CppString& str1) const;
            CppString operator+(uintptr_t num) const;
            void operator=(const CppString& str1){
                this->contents = str1.contents;
            }
            static CppString random(uintptr_t length);
            CppString(uintptr_t capacity);
            CppString(CppString&&) = default;
            CppString& operator=(CppString&&) = default;
            char* deconstruct() { return this->contents.deconstruct();}

            friend std::ostream& operator<<(std::ostream& os, const CppString& value);
            friend std::istream& operator>> (std::istream& is, CppString& str);
            bool operator !=(CppString& str1);
            bool operator ==(CppString& str2);
            virtual uintptr_t hash();
        private:
            Vector<char> contents;
    };
}
namespace adt {

    template<typename T> struct Queue {
        private:
            struct Node {
                Node(T& d) {
                    this->data = d;
                }
                T data;
                Node* next;
            };
        public:
            Queue() { this->head = nullptr; }
            int enqueue(T& data) {
                if(head == nullptr){
                    
                    head = new Node(data);
                    head->next = nullptr;
                    return 0;
                }
                
                Node* next = head;
                head = new Node(data);
                head->next = next;
                return 0;
            }

            int dequeue(T& dest) {
                if(head == nullptr) {
                    return -1;
                }
                return dequeue_priv(head, dest, 0);
            }
            ~Queue() {
                if(head != nullptr){
                    destroy(head);
                }
            }

        private:
            void destroy(Node*& first) {
                if(first == nullptr) { return; }
                if(first->next == nullptr){
                    delete first;
                    first = nullptr;
                    return;
                }
                Node* next = first->next;
                delete first;
                first = nullptr;
                return destroy(next);
            }
            int dequeue_priv(Node*& first, T& dest, int idx) {
                if(first->next == nullptr){
                    dest = first->data;
                    delete first;
                    first = nullptr;
                    return idx;
                }
                return dequeue_priv(first->next, dest, idx+1);
            }
            /*int insert(Node*& head, T& data, int idx) {
                if(head == nullptr) {
                    head = new Node(data);
                    head->next = nullptr;
                    return idx;
                }
                return insert(head->next, data, idx+1);
            }*/
            Node* head;
    };

    template<typename K, typename V> struct HashTable {
        static_assert(std::is_base_of<Hash, K>::value, "K must inherit from Hash");
            private:
                struct Node {
                    K key;
                    V value;
                    Node* next;
                    static int destroy(Node*& head, int idx) {
                        if(head == nullptr) {
                            return idx;
                        }
                        Node* next = head->next;
                        delete head;
                        head = nullptr;
                        return destroy(next, idx+1);
                    }
                    Node(K& k, V& v){
                        this->key = k;
                        this->value = v;
                        this->next = nullptr;
                    }
                    static int insert(Node*& head, K& key, V& value, int idx) {
                        if(head == nullptr) {
                            head = new Node(key, value);
                            return idx;
                        }
                        return insert(head->next, key, value, idx+1);
                    }
                    static bool get(Node*& head, K& k, V& dest) {
                        if(head == nullptr) {
                            return false;
                        }
                        if(k == head->key) {
                            dest = head->value;
                            return true;
                        }
                        return get(head->next, k, dest);
                    }
                };
        public:
            ~HashTable(){
                for(uintptr_t i = 0; i < this->array_len; i++){
                    Node::destroy(this->array[i], 0);
                }
                delete[] this->array;
            }
            HashTable() {
                this->array_len = 0;
                this->array = nullptr;
            }
            HashTable(uintptr_t arr_len) {
                this->array_len = arr_len;
                this->array = new Node*[arr_len]();
            }
            int insert(K& key, V& value) {
                uintptr_t hash_val = key.hash();
                uintptr_t index = hash_val > this->array_len ? (hash_val % this->array_len) : hash_val;
                return Node::insert(this->array[index], key, value, 0);
            }

            bool get(K& key, V& dest) {
                uintptr_t hash_val = key.hash();
                uintptr_t index = hash_val > this->array_len ? (hash_val % this->array_len) : hash_val;
                return Node::get(this->array[index], key, dest);
            }
        private:
            /// I might switch to using Queues
            Node** array;
            uintptr_t array_len;
    };
}

#endif