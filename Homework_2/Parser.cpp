#include "Parser.hpp"

bool Parser::comp(TokenType type) {
    if (check(type)) {
        nextTok();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) {
    return !(curr >= tokens.size()) && currTok().type == type;
}

const Token& Parser::nextTok() {
    return tokens[curr++];
}

const Token& Parser::currTok() const {
    return tokens[curr];
}

Parser::Parser(const std::vector<Token> &tokens):
    tokens(tokens) {}

std::shared_ptr<Expression> Parser::parseExpression() {
    auto expr = parseTerm();
    while (comp(TokenType::OP) && (currTok().value == "+" || currTok().value == "-")) {
        std::string op = currTok().value;
        nextTok();
        auto right = parseTerm();
        if (op == "+") {
            expr = std::make_shared<Addition>(expr, right);
        } else {
            expr =  std::make_shared<Subtraction>(expr, right);
        }
    }
    return expr;
}

std::shared_ptr<Expression> Parser::parseTerm() {
    auto expr = parseFactor();
    while (comp(TokenType::OP) && (currTok().value == "*" || currTok().value == "/")) {
        std::string op = currTok().value;
        nextTok();
        auto right = parseFactor();
        if (op == "*") {
            expr = std::make_shared<Multiplication>(expr, right);
        } else {
            expr =  std::make_shared<Division>(expr, right);
        }
    }
    return expr;
}

std::shared_ptr<Expression> Parser::parseFactor() {
    auto expr = parsePrimary();
    if (comp(TokenType::OP) && currTok().value == "^") {
        nextTok();
        auto right = parseFactor();
        expr = std::make_shared<RaisingToPower>(expr, right);
    }
    return expr;
}

std::shared_ptr<Expression> Parser::parsePrimary() {
    if (comp(TokenType::LEFTP)) {
        auto expr = parseExpression();
        if (!comp(TokenType::RIGHTP)) {
            throw ParseError("Expected ')'", currTok().pos);
        }
        return expr;
    }
    if (comp(TokenType::NUM)) {
        double value = std::stod(currTok().value);
        nextTok();
        return std::make_shared<Number>(value);
    }
    if (comp(TokenType::VAR)) {
        return std::make_shared<Variable>(currTok().value);
        nextTok();
    }
    
    if (comp(TokenType::FUN)) {
        std::string name = currTok().value;
        nextTok();
        if (!comp(TokenType::LEFTP)) {
            throw ParseError("Expected '(' after function name", currTok().pos);
        }
        auto arg = parseExpression();
        if (!comp(TokenType::RIGHTP)) {
            throw ParseError("Expected ')' after function argument", currTok().pos);
        }
        if (name == "sin") {
            return std::make_shared<Sin>(arg);
        } else if (name == "cos") {
            return std::make_shared<Cos>(arg);
        } else if (name == "ln") {
            return std::make_shared<Ln>(arg);
        } else if (name == "exp") {
            return std::make_shared<Exp>(arg);
        }
        throw ParseError("Unknown function: " + name, currTok().pos);
    }
    throw ParseError("Unexpected token: " + currTok().value, currTok().pos);
}

std::shared_ptr<Expression> Parser::parse(const std::string &expression) {
    Tokenizer tokenizer(expression);
    std::vector<Token> tokens = tokenizer.tokenize();
    Parser parser(tokens);
    return parser.parseExpression();
}