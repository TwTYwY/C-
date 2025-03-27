#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <string>
#include <vector>
#include <stdexcept>

enum class TokenType {
    NUM,
    VAR,
    OP,
    FUN,
    LEFTP,
    RIGHTP
};

struct Token {
    TokenType type;
    std::string value;
    size_t pos;
};

class Tokenizer {
private:
    const std::string input;
    size_t pos = 0;
    char getEl() const;
    char nextEl();
    void space();
    Token readNumber();
    Token readFunOrVar();
    Token readOperator();
    Token readBrackets();
public:
    explicit Tokenizer(const std::string &input);
    std::vector<Token> tokenize();
};

class TokenizeError : public std::runtime_error {
public:
    explicit TokenizeError(const std::string& msg, size_t pos)
        : std::runtime_error(msg + " at position " + std::to_string(pos)) {}
};

#endif