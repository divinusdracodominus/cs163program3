#include "adt.hpp"
namespace adt{
    class MissingToken: std::exception {
        public:
            MissingToken(const char* msg) {
                this->message = msg;
            }
            virtual const char* what() {
                return this->message;
            }
        private:
            const char* message;
    }

    struct Token {
        public:
            enum TokenType {
                OpenBracket,
                CloseBracket,
                OpenParan,
                CloseParan,
                Comma,
                Colon,
                SemiColon,
                Value,
            };
            TokenType type;
            union {
                CppString value;
            };
    }

    struct Parser {
        public:
            Parser(CppString& contents);
            /// I don't know wether or not a collection will be present, thus all JSON values
            /// are vectors of either a single, or multiple elemnts
            HashTable<CppString, Vector<CppString>> parse();
        private:
            CppString& contents;
    };
};