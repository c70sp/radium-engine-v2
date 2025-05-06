#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#define GLM_ENABLE_EXPERIMENTAL

// 3rd party libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

// C++ STL
// #include <iostream>
#include <vector>

struct TransformComponent{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale = glm::vec3(1.0f);

    glm::mat4 modelMatrix = glm::mat4(1.0f);
};

struct MeshComponent{
    std::vector<GLfloat> vertexData = {
        -1.0f, -1.0f, 0.0f, // BL
        1.0f, 0.0f, 0.0f,

        1.0f, -1.0f, 0.0f, // BR
        0.0f, 1.0f, 0.0f,

        1.0f, 1.0f, 0.0f, // TR
        0.0f, 0.0f, 1.0f,

        -1.0f, 1.0f, 0.0f, // TL
        0.5f, 0.0f, 0.7f
    };

    std::vector<GLuint> indexBufferData = {
        0, 2, 3,
        0, 1, 2
    };

    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint IBO = 0;

    GLuint pipeline = 0;

    glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);

    unsigned int size = 0;

    bool init = false;
};

#endif // COMPONENTS_HPP