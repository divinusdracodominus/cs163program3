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
            bool operator !=(CppString& str1) const;
            bool operator ==(CppString& str2) const;
            bool operator ==(const CppString& str2) const;
            virtual uintptr_t hash() const;
        private:
            Vector<char> contents;
    };
}
namespace adt {

    template<typename T> struct DLLQueue {
        private:
            struct Node {
                Node(T& d) {
                    this->data = d;
                }
                T data;
                Node* next;
                Node* prev;
            };
        public:
            DLLQueue() { this->head = nullptr; this->tail = nullptr; }
            DLLQueue(const DLLQueue<T>&) = delete;
            void operator=(const DLLQueue<T>&) = delete;
            int enqueue(T& data) {
                if(this->head == nullptr){
                    
                    this->head = new Node(data);
                    this->head->next = nullptr;
                    this->head->prev = nullptr;
                    this->tail = head;
                    return 0;
                }
                
                Node* next = head;
                head = new Node(data);
                head->next = next;
                head->next->prev = head;
                return 0;
            }

            int dequeue(T& dest) {
                if(head == nullptr) {
                    return -1;
                }
                if(tail == nullptr){
                    return -1;
                }
                Node* prev = this->tail->prev;
                dest = this->tail->data;
                delete tail;
                this->tail = prev;
                return 1;
                //return dequeue_priv(head, dest, 0);
            }
            ~DLLQueue() {
                if(head != nullptr && tail != nullptr){
                    destroy(head);
                }
            }

        private:
            void destroy(Node* first) {
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
            Node* head;
            Node* tail;
    };

    template<typename T> struct CLLQueue {
        private:
            struct Node {
                Node(T& d) {
                    this->data = d;
                }
                T data;
                Node* next;
            };
        public:
            CLLQueue() { this->rear = nullptr; }
            CLLQueue(const DLLQueue<T>&) = delete;
            void operator=(const DLLQueue<T>&) = delete;
            int enqueue(T& data) {
                if(this->rear == nullptr){
                    
                    this->rear = new Node(data);
                    this->rear->next = this->rear;
                    return 1;
                }
                Node* begining = this->rear->next;
                this->rear->next = new Node(data);
                this->rear = this->rear->next;
                this->rear->next = begining;
                return 1;
            }

            int dequeue(T& dest) {
                if(this->rear == nullptr) {
                    return -1;
                }
                if(this->rear->next == this->rear){
                    dest = this->rear->data;
                    delete this->rear;
                    this->rear = nullptr;
                    return 1;
                }
                dest = this->rear->next->data;
                Node* second = this->rear->next->next;
                delete this->rear->next;
                this->rear->next = second;
                return 1;
                //return dequeue_priv(head, dest, 0);
            }
            ~CLLQueue() {
                if(rear != nullptr){
                    destroy(this->rear->next);
                }
            }

        private:
            void destroy(Node* first) {
                if(first == nullptr) { return; }
                if(first->next == this->rear){
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
            Node* rear;
    };

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
            Node* head;
    };

    template<typename T> struct UnsizedTree {
        private:
            struct Node {
                Node* left;
                Node* right;
                T value;
            };
        public:

        private:
            Node* root;
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
                    static bool get(Node* head, K& k, V& dest) {
                        if(head == nullptr) {
                            return false;
                        }
                        if(k == head->key) {
                            dest = head->value;
                            return true;
                        }
                        return get(head->next, k, dest);
                    }
                    static ItemState<const V> get_ref(Node* head, const K& k) {
                        if(head == nullptr) {
                            return ItemState<const V>();
                        }
                        if(k == head->key) {
                            return ItemState<const V>(head->value);
                        }
                        return get_ref(head->next, k);
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
                uintptr_t index = key.hash() % this->array_len;
                if(this->array[index] == nullptr){
                    
                    this->array[index] = new Node(key, value);
                    this->array[index]->next = nullptr;
                    return 0;
                }
                
                Node* next = this->array[index];
                this->array[index] = new Node(key, value);
                this->array[index]->next = next;
                return 0;
            }

            bool get(K& key, V& dest) {
                uintptr_t index = key.hash() % this->array_len;
                //uintptr_t index = hash_val > this->array_len ? (hash_val % this->array_len) : hash_val;
                return Node::get(this->array[index], key, dest);
            }
            ItemState<const V> operator[](const K& key){
                uintptr_t index = key.hash() % this->array_len;
                return Node::get_ref(this->array[index], key);
            }
        private:
            /// I might switch to using Queues
            Node** array;
            uintptr_t array_len;
    };
}

#endif