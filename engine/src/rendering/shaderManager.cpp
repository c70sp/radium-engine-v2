// 3rd party libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// C++ STL
#include <iostream>
#include <vector>
#include <filesystem>
#include <string>

// Own libs
#include "rendering/shaderManager.hpp"
#include "utils.hpp"

// ShaderManager::ShaderManager(){
    
// }

void ShaderManager::compileAllShaders(){
    std::string path = "C:/dev/projects/C++/OpenGL/Radium Engine att2/engine/shaders/";
    std::vector<std::string> files;

    try{
        for(const auto& entry : std::filesystem::directory_iterator(path)){
            if(std::filesystem::is_regular_file(entry)){
                std::string file = entry.path().filename().string();
                files.push_back(file);
            }
        }
    } catch(const std::filesystem::filesystem_error& e){
        std::cerr << "Error while parsing shader files: " << e.what() << std::endl;
    }

    for(std::string file : files){
        std::string fileSource = utils::loadFileAsString(path + file);

        if(file.rfind("v_", 0) == 0){
            compileShader(GL_VERTEX_SHADER, fileSource, file);
        }else if(file.rfind("f_", 0) == 0){
            compileShader(GL_FRAGMENT_SHADER, fileSource, file);
        }
    }

    std::cout << "" << std::endl;
}

void ShaderManager::compileShader(GLuint type, const std::string& source, std::string& name){
    std::cout << "Compiling type " << type << " shader..." << std::endl;
    GLuint shaderObject;
    shaderObject = glCreateShader(type);

    const char* src = source.c_str();
    glShaderSource(shaderObject, 1, &src, nullptr);
    utils::checkGLError("after glShaderSource, shaderManager");

    glCompileShader(shaderObject);
    utils::checkGLError("after glCompileShader, shaderManager");

    checkShaderCompileStatus(shaderObject);

    ShaderInfo shader;
    shader.name = name;
    shader.type = type;
    shader.ID = shaderObject;
    int id = mShaders.size();

    mShaders.emplace(id, shader);
}

void ShaderManager::checkShaderCompileStatus(const GLuint shaderObject){
    GLint compileStatus;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &compileStatus);
    if(compileStatus == GL_FALSE){
        GLint logLength;
        glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(logLength);
        glGetShaderInfoLog(shaderObject, logLength, &logLength, log.data());
        std::cerr << "Shader compilation failed: " << log.data() << std::endl;
        return;
    }
    std::cout << "Compilation successful" << std::endl;
}

GLuint ShaderManager::getShader(const std::string& shaderName){
    ShaderInfo* foundShader;

    for(auto& [id, shader] : mShaders){
        if(shader.name == shaderName){
            foundShader = &shader;
            break;
        }
    }

    if(foundShader){
        return foundShader->ID;
    }else{
        std::cerr << "Shader with name \"" << shaderName << "\" not found!" << std::endl;
        return 0;
    }
}

GLuint ShaderManager::createPipeline(const GLuint vertexShaderID, const GLuint fragmentShaderID){
    GLuint programObject = glCreateProgram();

    glAttachShader(programObject, vertexShaderID);
    glAttachShader(programObject, fragmentShaderID);
    glLinkProgram(programObject);

    GLint linkStatus;
    glGetProgramiv(programObject, GL_LINK_STATUS, &linkStatus);
    if(linkStatus == GL_FALSE){
        GLint logLength;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(logLength);
        glGetProgramInfoLog(programObject, logLength, &logLength, log.data());
        std::cerr << "Program linking failed: " << log.data() << std::endl;
        std::cerr << "In pipeline: " << programObject << ", with shaders " << vertexShaderID << " and " << fragmentShaderID << std::endl;
        std::cout << "" << std::endl;
    }

    glValidateProgram(programObject);

    PipelineInfo pipeline;
    pipeline.name = programObject;
    pipeline.ID = programObject;
    pipeline.vertexShaderID = vertexShaderID;
    pipeline.fragmentShaderID = fragmentShaderID;
    int id = mPipelines.size();
    mPipelines.emplace(id, pipeline);
    std::cout << "Pipeline " << pipeline.ID << " created!" << std::endl;

    return programObject;
}

GLuint ShaderManager::getPipeline(const std::string& vertexShaderName, const std::string& fragmentShaderName){
    GLuint vertexShaderID = getShader(vertexShaderName);
    GLuint fragmentShaderID = getShader(fragmentShaderName);

    for(auto& [id, pipeline] : mPipelines){
        if(pipeline.vertexShaderID == vertexShaderID && pipeline.fragmentShaderID == fragmentShaderID){
            return pipeline.ID;
        }
    }

    return createPipeline(vertexShaderID, fragmentShaderID);
}

void ShaderManager::setUniformInt(GLuint pipeline, const char* name, int value){
    GLint location = glGetUniformLocation(pipeline, name);
    glUniform1i(location, value);
}

void ShaderManager::setUniformFloat(GLuint pipeline, const char* name, float value){
    GLint location = glGetUniformLocation(pipeline, name);
    glUniform1f(location, value);
}

void ShaderManager::setUniformVec2(GLuint pipeline, const char* name, glm::vec2 value){
    GLint location = glGetUniformLocation(pipeline, name);
    glUniform2fv(location, 1, &value[0]);
}

void ShaderManager::setUniformVec3(GLuint pipeline, const char* name, glm::vec3 value){
    GLint location = glGetUniformLocation(pipeline, name);
    glUniform3fv(location, 1, &value[0]);
}

void ShaderManager::setUniformMat4(GLuint pipeline, const char* name, glm::mat4 value){
    GLint location = glGetUniformLocation(pipeline, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}