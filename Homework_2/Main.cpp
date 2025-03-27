#include "Parser.hpp"
#include <iostream>
#include <map>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: differentiator --eval <expression> [variable=value ...] | --diff <expression> --by <variable>" << std::endl;
        return 1;
    }

    std::string mode = argv[1];
    std::string expressionStr = argv[2];

    auto expression = Parser::parse(expressionStr);

    if (mode == "--eval") {
        std::map<std::string, double> variables;
        for (int i = 3; i < argc; i++) {
            std::string arg = argv[i];
            size_t eqPos = arg.find('=');
            if (eqPos == std::string::npos) {
                std::cerr << "Invalid variable assignment: " << arg << std::endl;
                return 1;
            }
            std::string varName = arg.substr(0, eqPos);
            double varValue = std::stod(arg.substr(eqPos + 1));
            variables[varName] = varValue;
        }
        std::cout << expression->substitution(variables) << std::endl;
    } else if (mode == "--diff") {
        if (argc < 5 || std::string(argv[3]) != "--by") {
            std::cerr << "Usage: differentiator --diff <expression> --by <variable>" << std::endl;
            return 1;
        }
        std::string variable = argv[4];
        auto derivative = expression->derivative(variable);
        std::cout << derivative->toString() << std::endl;
    } else {
        std::cerr << "Unknown mode: " << mode << std::endl;
        return 1;
    }

    return 0;
}