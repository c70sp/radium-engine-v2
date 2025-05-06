#ifndef ENGINE_HPP
#define ENGINE_HPP

// 3rd party libs
#include <glad/glad.h>

// Own libs
#include "ecs/ECSManager.hpp"
#include "rendering/meshBuilder.hpp"
#include "rendering/renderSystem.hpp"
#include "rendering/shaderManager.hpp"
#include "HotReloading/fileHandler.hpp"

class Engine{
    public:
        Engine();
        void render();
        void terminate();

        /**
         * GLuint getPipeline("v_vert.glsl", "f_frag.glsl");
         * gets sent to ShaderManager where the shit happens
         */

        
        ECSManager ecs;
        MeshBuilder meshBuilder;
        RenderSystem renderer;
        ShaderManager shaderManager;
        FileHandler fileHandler;
        
        GLuint getPipeline(const std::string& vertexShaderName, const std::string& fragmentShaderName);
        
        
        int mScreenWidth = 640;
        int mScreenHeight = 480;
        GLFWwindow* mWindow;
    private:
        void getOpenGLVersionInfo();
        int initEngine();

        void terminateAllInstances();
        void cleanUp();
};

#endif // ENGINE_HPP