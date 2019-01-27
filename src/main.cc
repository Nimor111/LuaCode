#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/error.h"
#include "../include/scanner.h"
#include "../include/token.h"

void Run(std::string src)
{
    Scanner scanner(src);
    std::vector<Token> tokens = scanner.ScanTokens();

    for (auto const& token : tokens) {
        std::cout << token << std::endl;
    }
}

void RunFile(std::string filename)
{
    std::ifstream file(filename);

    std::stringstream buffer;
    buffer << file.rdbuf();

    Run(buffer.str());

    if (Error::had_error()) {
        exit(65);
    }
}

void RunPrompt()
{
    std::string input;
    for (;;) {
        std::cout << "> ";
        std::getline(std::cin, input);
        Run(input);
        Error::set_had_error(false);
    }
}

int main(int argc, char const** argv)
{
    if (argc > 2) {
        std::cout << "Usage: clua [script].lua" << std::endl;
        exit(64);
    } else if (argc == 2) {
        RunFile(std::string(argv[1]));
    } else {
        RunPrompt();
    }

    return 0;
}
