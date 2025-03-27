#include "Token.hpp"

char Tokenizer::getEl() const {
    if (pos < input.size()) {
        return input[pos];
    }
    return '\0';
}

char Tokenizer::nextEl() {
    return input[pos++];
}

void Tokenizer::space() {
    while ((pos < input.size()) && (getEl() == ' ')) {
        nextEl();
    }
}

Token Tokenizer::readNumber() {
    size_t start = pos;
    while ((pos < input.size()) && (isdigit(getEl()) || (getEl() == '.'))) {
        nextEl();
    }
    return {TokenType::NUM, input.substr(start, pos - start), start};
}

Token Tokenizer::readFunOrVar() {
    size_t start = pos;
    while ((pos < input.size()) && (((getEl() >= 'A') && (getEl() <= 'Z'))) || ((getEl() >= 'a') && (getEl() <= 'z'))) {
        nextEl();
    }
    std::string s = input.substr(start, pos - start);
    if ((s == "sin") || (s == "cos") || (s == "ln") || (s == "exp")) {
        return {TokenType::FUN, s, start};
    } 
    return {TokenType::VAR, s, start};
}

Token Tokenizer::readOperator() {
    size_t start = pos;
    char op = getEl();
    nextEl();
    return {TokenType::VAR, std::string(1, op), start};
}

Token Tokenizer::readBrackets() {
    size_t start = pos;
    char b = getEl();
    nextEl();
    if (b == '(') {
        return {TokenType::LEFTP, std::string(1, b), start};
    } else {
        return {TokenType::RIGHTP, std::string(1, b), start};
    }
}

Tokenizer::Tokenizer(const std::string &input):
    input(input) {}

std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens;
    while (pos < input.size()) {
        space();
        if (pos >= input.size()) {
            break;
        }
        char currEl = getEl();
        if (isdigit(currEl) || currEl == '.') {
            tokens.push_back(readNumber());
        } else if (((currEl >= 'A') && (currEl <= 'Z')) || ((currEl >= 'a') && (currEl <= 'z'))) {
            tokens.push_back(readFunOrVar());
        } else if (currEl == '(') {
            tokens.push_back(readBrackets());
            nextEl();
        } else if (currEl == ')') {
            tokens.push_back(readBrackets());
            nextEl();
        } else {
            tokens.push_back(readOperator());
        }
    }
    return tokens;
}