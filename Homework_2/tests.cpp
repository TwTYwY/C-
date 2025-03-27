#include <catch2/catch_test_macros.hpp>
#include "Token.hpp"
#include "Parser.hpp"
#include "Expression.hpp"

TEST_CASE("Tokenizer - Разбиение выражений на токены") {
    Tokenizer tokenizer("3 + x * 5");
    std::vector<Token> tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 5);
    REQUIRE(tokens[0].type == TokenType::NUM);
    REQUIRE(tokens[0].value == "3");
    REQUIRE(tokens[1].type == TokenType::OP);
    REQUIRE(tokens[1].value == "+");
    REQUIRE(tokens[2].type == TokenType::VAR);
    REQUIRE(tokens[2].value == "x");
}

TEST_CASE("Parser - Парсинг выражений") {
    auto expr = Parser::parse("3 + 5");
    REQUIRE(expr != nullptr);
}

TEST_CASE("Expression - Сложение чисел") {
    auto left = std::make_shared<Number>(3);
    auto right = std::make_shared<Number>(5);
    Addition add(left, right);

    REQUIRE(add.substitution({}) == 8);
}

TEST_CASE("Expression - Вычитание") {
    auto left = std::make_shared<Number>(10);
    auto right = std::make_shared<Number>(4);
    Subtraction sub(left, right);

    REQUIRE(sub.substitution({}) == 6);
}

TEST_CASE("Expression - Умножение") {
    auto left = std::make_shared<Number>(6);
    auto right = std::make_shared<Number>(7);
    Multiplication mul(left, right);

    REQUIRE(mul.substitution({}) == 42);
}

TEST_CASE("Expression - Деление") {
    auto left = std::make_shared<Number>(20);
    auto right = std::make_shared<Number>(5);
    Division div(left, right);

    REQUIRE(div.substitution({}) == 4);
}

TEST_CASE("Expression - Возведение в степень") {
    auto base = std::make_shared<Number>(2);
    auto exponent = std::make_shared<Number>(3);
    RaisingToPower pow(base, exponent);

    REQUIRE(pow.substitution({}) == 8);
}

TEST_CASE("Expression - Переменная") {
    auto var = std::make_shared<Variable>("x");
    REQUIRE(var->substitution({{"x", 10}}) == 10);
}

TEST_CASE("Expression - Производная") {
    auto var = std::make_shared<Variable>("x");
    auto expr = std::make_shared<Multiplication>(var, var); // x * x
    auto deriv = expr->derivative("x");

    REQUIRE(deriv->substitution({{"x", 2}}) == 4);
}
