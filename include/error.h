#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <string>

class Error {
private:
    static bool had_error_;
    static void Report(int line, std::string location, std::string message);

public:
    Error();
    static void set_had_error(bool);
    static bool had_error();
    static void MakeError(int, std::string);
};

#endif /* ERROR_H */
