#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP
#include <string>
#include <memory>
#include <map>

class Expression {
public:
    Expression() = default;
    ~Expression() = default;
    Expression(const Expression&) = default;
    Expression(Expression&&) = default;
    Expression& operator=(const Expression&) = default;
    Expression& operator=(Expression&&) = default;
    virtual double substitution(const std::map<std::string, double>& variables) const = 0;
    virtual std::shared_ptr<Expression> derivative(const std::string& variable) const = 0;
    virtual std::string toString() const = 0;
};

class Number: public Expression {
    double value;
public:
    Number(double value);
    double substitution(const std::map<std::string, double>& variables) const override;
    std::shared_ptr<Expression> derivative(const std::string& variable) const override;
    std::string toString() const override;
};

class Variable: public Expression {
    std::string name;
public:
    Variable(const std::string& name);
    double substitution(const std::map<std::string, double>& variables) const override;
    std::shared_ptr<Expression> derivative(const std::string& variable) const override;
    std::string toString() const override;
};

class BaseArithmetic: public Expression {
protected:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
    char op;
public:
    BaseArithmetic(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right, char op);
    double substitution(const std::map<std::string, double>& variables) const override;
    std::string toString() const override;
};

class Addition: public BaseArithmetic {
public:
    Addition(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> derivative(const std::string& variable) const override;
};

class Subtraction: public BaseArithmetic {
public:
    Subtraction(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> derivative(const std::string& variable) const override;
};

class Multiplication: public BaseArithmetic {
public:
    Multiplication(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> derivative(const std::string& variable) const override;
};

class Division: public BaseArithmetic {
public:
    Division(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> derivative(const std::string& variable) const override;
};

class RaisingToPower: public BaseArithmetic {
public:
    RaisingToPower(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);
    std::shared_ptr<Expression> derivative(const std::string& variable) const override;
};

class Functions: public Expression {
protected:
    std::shared_ptr<Expression> argument;
    std::string funType;
public:
    Functions(std::shared_ptr<Expression> argument, const std::string& funType);
    double substitution(const std::map<std::string, double>& variables) const override;
    std::string toString() const override;
};

class Sin: public Functions {
public:
    Sin(std::shared_ptr<Expression> argument);
    std::shared_ptr<Expression> derivative(const std::string& variable) const override;
};

class Cos: public Functions {
public:
    Cos(std::shared_ptr<Expression> argument);
    std::shared_ptr<Expression> derivative(const std::string& variable) const override;
};

class Ln: public Functions {
public:
    Ln(std::shared_ptr<Expression> argument);
    std::shared_ptr<Expression> derivative(const std::string& variable) const override;
};

class Exp: public Functions {
public:
    Exp(std::shared_ptr<Expression> argument);
    std::shared_ptr<Expression> derivative(const std::string& variable) const override;
};

#endif