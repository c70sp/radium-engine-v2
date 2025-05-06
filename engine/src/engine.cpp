// 3rd party libs
#include <glad/glad.h>

// Own libs
#include "engine.hpp"
#include "utils.hpp"

Engine::Engine(){
    initEngine();
}

void Engine::getOpenGLVersionInfo(){
    std::cout << "" << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "" << std::endl;
}

int Engine::initEngine(){
    std::cout << "Engine init :)" << std::endl;

    if(!glfwInit()){
        std::cerr << "Failed to init GLFW." << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, 1);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_SAMPLES, 4);

    mWindow = glfwCreateWindow(mScreenWidth, mScreenHeight, "Title", NULL, NULL);
    if(mWindow == NULL){
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(mWindow);
    glfwSwapInterval(1);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to init GLAD." << std::endl;
        glfwTerminate();
        return -1;
    }

    getOpenGLVersionInfo();

    shaderManager.compileAllShaders();

    return 0;
}

void Engine::render(){
    renderer.render(ecs, *this);
}

GLuint Engine::getPipeline(const std::string& vertexShaderName, const std::string& fragmentShaderName){
    return shaderManager.getPipeline(vertexShaderName, fragmentShaderName);
}

//? vvvvvvvvvv TERMINATION vvvvvvvvvv

void Engine::terminateAllInstances(){
    // This is just to prevent A LOT of 1282 errors from OpenGL because of still ongoing operations from these instances
    // Also makes life easier, since it deletes all of the pipelines, ECS components like buffers and co.
    ecs.~ECSManager();
    meshBuilder.~MeshBuilder();
    renderer.~RenderSystem();
    shaderManager.~ShaderManager();
}

void Engine::cleanUp(){
    glfwMakeContextCurrent(NULL);
    glfwDestroyWindow(mWindow);

    glfwTerminate();
}

void Engine::terminate(){
    terminateAllInstances();
    cleanUp();
}