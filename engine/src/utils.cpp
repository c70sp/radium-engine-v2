// 3rd party libs
#include <glad/glad.h>

// C++ STL
#include <iostream>
#include <string>
#include <fstream>

// Own libs
#include "utils.hpp"

namespace utils{
    std::string loadFileAsString(const std::string& filePath){
        std::string result = "";

        std::string line = "";
        std::ifstream myFile(filePath.c_str());
        
        if(myFile.is_open()){
            while(std::getline(myFile, line)){
                result += line + "\n";
            }
            myFile.close();
        }

        return result;
    }

    void checkGLError(const std::string& location) {
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error at " << location << ": " << err << std::endl;
        }
    }
}