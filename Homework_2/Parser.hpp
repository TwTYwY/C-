#ifndef PARSER_HPP
#define PARSER_HPP
#include "Expression.hpp"
#include "Token.hpp"
#include <memory>
#include <vector>

class Parser {
private:
    const std::vector<Token> tokens;
    size_t curr = 0;
    bool comp(TokenType type);
    bool check(TokenType type);
    const Token& nextTok();
    const Token& currTok() const;
    explicit Parser(const std::vector<Token> &tokens);
    std::shared_ptr<Expression> parseExpression();
    std::shared_ptr<Expression> parseTerm();
    std::shared_ptr<Expression> parseFactor();
    std::shared_ptr<Expression> parsePrimary();
    std::shared_ptr<Expression> parseFunctionCall(const std::string &name);
public:
    static std::shared_ptr<Expression> parse(const std::string &expression);
};

class ParseError : public std::runtime_error {
public:
    explicit ParseError(const std::string& msg, size_t pos): 
        std::runtime_error(msg + " at position " + std::to_string(pos)) {}
};

#endif