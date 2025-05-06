#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP

// 3rd party libs
#include <glad/glad.h>
#include <glm/glm.hpp>

// C++ STL
#include <string>
#include <unordered_map>

struct ShaderInfo{
    std::string name;
    GLuint ID; // shader object id used for linking to program, not this local ID for finding the shader
    GLuint type;
};

struct PipelineInfo{
    std::string name;
    GLuint ID; // program object id used for the actual draw calls, not this local ID for finding the pipeline
    GLuint vertexShaderID;
    GLuint fragmentShaderID;
};

class ShaderManager{
    public:
        // ShaderManager();

        void compileAllShaders();
        void compileShader(GLuint type, const std::string& source, std::string& name);
        GLuint getShader(const std::string& shaderName);
        GLuint createPipeline(const GLuint vertexShaderID, const GLuint fragmentShaderID);
        GLuint getPipeline(const std::string& vertexShaderName, const std::string& fragmentShaderName);

        // Setter methodes for uniforms (int, float, vec3, mat4)
        void setUniformInt(GLuint pipeline, const char* name, int value);
        void setUniformFloat(GLuint pipeline, const char* name, float value);
        void setUniformVec2(GLuint pipeline, const char* name, glm::vec2 value);
        void setUniformVec3(GLuint pipeline, const char* name, glm::vec3 value);
        void setUniformMat4(GLuint pipeline, const char* name, glm::mat4 value);
    private:
        std::unordered_map<int, ShaderInfo> mShaders;
        std::unordered_map<int, PipelineInfo> mPipelines;

        void checkShaderCompileStatus(const GLuint shaderObject);
};

#endif // SHADERMANAGER_HPP