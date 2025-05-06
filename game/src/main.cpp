#define GLM_ENABLE_EXPERIMENTAL

// 3rd party libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

// C++ STL
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Own libs
#include "engine.hpp"
#include "utils.hpp"

Engine engine;
uint32_t mesh1 = engine.ecs.createEntity();
glm::mat4 mesh1mm;

float timelol = 0.0f;

void preDraw(){
    GLuint mesh1pipeline = engine.ecs.meshPool.getComponent(mesh1)->pipeline;

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);

    glViewport(0, 0, engine.mScreenWidth, engine.mScreenHeight);
    glClearColor(0.12f, 0.12f, 0.12f, 1.0f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(mesh1pipeline);

    // ? vvvvvvvvvvvvvvv Matrix Calc vvvvvvvvvvvvvvv
    // ? Model Matrix
    float rotationSpeed = engine.fileHandler.getVar<float>("C:/dev/projects/C++/OpenGL/Radium Engine att2/test.cfg", "rotationSpeed", 0.0f);

    mesh1mm = glm::translate(mesh1mm, glm::vec3(0.0f, 0.0f, 0.0f));
    mesh1mm = glm::rotate(mesh1mm, glm::radians(rotationSpeed), glm::vec3(0, 1, 0));
    mesh1mm = glm::scale(mesh1mm, glm::vec3(1.0f));
    engine.shaderManager.setUniformMat4(mesh1pipeline, "u_ModelMatrix", mesh1mm);

    // ? Projection Matrix
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)engine.mScreenWidth / (float)engine.mScreenHeight, 0.1f, 1000.0f);
    engine.shaderManager.setUniformMat4(mesh1pipeline, "u_ProjectionMatrix", projectionMatrix);

    timelol += 0.1f;
    engine.shaderManager.setUniformFloat(mesh1pipeline, "time", timelol);

    float centerX = engine.fileHandler.getVar<float>("C:/dev/projects/C++/OpenGL/Radium Engine att2/test.cfg", "u_centerX", 2.0f);
    float centerY = engine.fileHandler.getVar<float>("C:/dev/projects/C++/OpenGL/Radium Engine att2/test.cfg", "u_centerY", 2.0f);
    engine.shaderManager.setUniformVec2(mesh1pipeline, "u_center", glm::vec2(centerX, centerY));
    
    float zoom = engine.fileHandler.getVar<float>("C:/dev/projects/C++/OpenGL/Radium Engine att2/test.cfg", "u_zoom", 1.5f);
    engine.shaderManager.setUniformFloat(mesh1pipeline, "u_zoom", zoom);

    int u_maxIterations = engine.fileHandler.getVar<int>("C:/dev/projects/C++/OpenGL/Radium Engine att2/test.cfg", "u_maxIterations", 1.5f);
    engine.shaderManager.setUniformInt(mesh1pipeline, "u_maxIterations", u_maxIterations);

    glUseProgram(0);
}

void mainLoop(){
    while(!glfwWindowShouldClose(engine.mWindow)){
        engine.fileHandler.checkChanges();
        preDraw();
        
        engine.render();
        glfwSwapBuffers(engine.mWindow);
        glfwPollEvents();
    }
}

void keyPress(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(int argc, char* argv[]){
    /**
     * Engine engine();
     * ^ Macht dann alles, also erstellt Fenster und stellt alles ein.
     * Erstellt auch ECS Manager und hält reference zu diesen.
     * Dann hier:
     * uint32_t entity = ecs.createEntity();
     * ecs.transformPool.addComponent(entity, TransformComponent{pos, rot, scale}); oder so ähnlich
     * ecs.meshPool.addComponent(entity.MeshComponent{});
     * 
     * dann hier der mainLoop, dort muss nur noch glClear, dann der eigene Code, dann glfwSwapBuffer and glfwPollEvents passieren
     */
    TransformComponent trans = TransformComponent{glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f), glm::vec3(1.0f)};
    engine.ecs.transformPool.addComponent(mesh1, trans);

    mesh1mm = engine.ecs.transformPool.getComponent(mesh1)->modelMatrix;
    mesh1mm = glm::translate(mesh1mm, glm::vec3(0.0f, 0.0f, -3.0f));

    MeshComponent mesh = MeshComponent{};
    mesh.pipeline = engine.getPipeline("v_vert.glsl", "f_mandelbrot.glsl");
    engine.ecs.meshPool.addComponent(mesh1, mesh);

    //! =======================================================

    std::cout << "Starting..." << std::endl;

    // init comes from engine creation

    // vertex spec is handled completely differently, via the ECS

    // shader compilation and pipeline linking and their respective management is now handled via the shaderManager

    engine.fileHandler.watchFile("C:/dev/projects/C++/OpenGL/Radium Engine att2/test.cfg");

    glfwSetKeyCallback(engine.mWindow, keyPress);
    mainLoop();
    
    engine.terminate();

    std::cout << "Goodbye :(" << std::endl;
    return 0;
}