#include "Expression.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>

Number::Number(double value):
    value(value) {}

double Number::substitution(const std::map<std::string, double>& variables) const {
    return value;
}

std::shared_ptr<Expression> Number::derivative(const std::string& variable) const {
    return std::make_shared<Number>(0);
}

std::string Number::toString() const {
    return std::to_string(value);
}

Variable::Variable(const std::string& name):
    name(name) {}

double Variable::substitution(const std::map<std::string, double>& variables) const {
    auto value = variables.find(name);
    if (value != variables.end()) {
        return value->second;
    }
    throw std::invalid_argument("Variable not found: " + name);
}

std::shared_ptr<Expression> Variable::derivative(const std::string& variable) const {
    if (name == variable) {
        return std::make_shared<Number>(1);
    }
    return std::make_shared<Number>(0);
}

std::string Variable::toString() const {
    return name;
}

BaseArithmetic::BaseArithmetic(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right, char op):
    left(left),
    right(right),
    op(op) {}

double BaseArithmetic::substitution(const std::map<std::string, double>& variables) const {
    double leftValue = left->substitution(variables);
    double rightValue = right->substitution(variables);
    switch (op) {
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            return leftValue / rightValue;
        case '^':
            return std::pow(leftValue, rightValue);
        default:
            throw std::invalid_argument("Unknown operator: " + op);
    }
}

std::string BaseArithmetic::toString() const {
    return "(" + left->toString() + " " + op + " " + right->toString() + ")";
}

Addition::Addition(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
    BaseArithmetic(left, right, '+') {}

std::shared_ptr<Expression> Addition::derivative(const std::string& variable) const {
    return std::make_shared<Addition>(left->derivative(variable), right->derivative(variable));
}

Subtraction::Subtraction(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
    BaseArithmetic(left, right, '-') {}

std::shared_ptr<Expression> Subtraction::derivative(const std::string& variable) const {
    return std::make_shared<Subtraction>(left->derivative(variable), right->derivative(variable));
}

Multiplication::Multiplication(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
    BaseArithmetic(left, right, '*') {}

std::shared_ptr<Expression> Multiplication::derivative(const std::string& variable) const {
    return std::make_shared<Addition>(std::make_shared<Multiplication>(left->derivative(variable), right), std::make_shared<Multiplication>(left, right->derivative(variable)));
}

Division::Division(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
    BaseArithmetic(left, right, '/') {}

std::shared_ptr<Expression> Division::derivative(const std::string& variable) const {
    return std::make_shared<Division>(std::make_shared<Subtraction>(std::make_shared<Multiplication>(left->derivative(variable), right), std::make_shared<Multiplication>(left, right->derivative(variable))), std::make_shared<RaisingToPower>(right, std::make_shared<Number>(2)));
}

RaisingToPower::RaisingToPower(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
    BaseArithmetic(left, right, '^') {}

std::shared_ptr<Expression> RaisingToPower::derivative(const std::string& variable) const {
    return std::make_shared<Multiplication>(right, std::make_shared<Multiplication>(std::make_shared<RaisingToPower>(left, std::make_shared<Subtraction>(right, std::make_shared<Number>(1))), left->derivative(variable)));
}

Functions::Functions(std::shared_ptr<Expression> argument, const std::string& funType):
    argument(argument),
    funType(funType) {}

double Functions::substitution(const std::map<std::string, double>& variables) const {
    if (funType == "sin") {
        return std::sin(argument->substitution(variables));
    } else if (funType == "cos") {
        return std::cos(argument->substitution(variables));
    } else if (funType == "ln") {
        return std::log(argument->substitution(variables));
    } else if (funType == "exp") {
        return std::exp(argument->substitution(variables));
    } 
    throw std::invalid_argument("Unknown function: " + funType);
}

std::string Functions::toString() const {
    return funType + "(" + argument->toString() + ")";
}

Sin::Sin(std::shared_ptr<Expression> argument):
    Functions(argument, "sin") {}

std::shared_ptr<Expression> Sin::derivative(const std::string& variable) const {
    return std::make_shared<Multiplication>(std::make_shared<Cos>(argument), argument->derivative(variable));
}

Cos::Cos(std::shared_ptr<Expression> argument):
    Functions(argument, "cos") {}

std::shared_ptr<Expression> Cos::derivative(const std::string& variable) const {
    return std::make_shared<Multiplication>(std::make_shared<Number>(-1), std::make_shared<Multiplication>(std::make_shared<Sin>(argument), argument->derivative(variable)));
}

Ln::Ln(std::shared_ptr<Expression> argument):
    Functions(argument, "ln") {}

std::shared_ptr<Expression> Ln::derivative(const std::string& variable) const {
    return std::make_shared<Division>(argument->derivative(variable), argument);
}

Exp::Exp(std::shared_ptr<Expression> argument):
    Functions(argument, "exp") {}

std::shared_ptr<Expression> Exp::derivative(const std::string& variable) const {
    return std::make_shared<Multiplication>(argument->derivative(variable), std::make_shared<Exp>(argument));
}