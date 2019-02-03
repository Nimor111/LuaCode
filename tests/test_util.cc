#include <fstream>
#include <sstream>
#include <string>

inline const std::string readFixture(std::string filename)
{
    std::ifstream file(filename);

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}
