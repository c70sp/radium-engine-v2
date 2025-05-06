#ifndef UTILS_HPP
#define UTILS_HPP

// C++ STL
#include <iostream>
#include <string>
#include <fstream>

namespace utils{
    std::string loadFileAsString(const std::string& filePath);

    void checkGLError(const std::string& location);
}

#endif // UTILS_HPP