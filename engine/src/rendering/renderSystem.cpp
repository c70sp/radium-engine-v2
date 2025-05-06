// Own libs
#include "engine.hpp"
#include "rendering/renderSystem.hpp"
#include "rendering/meshBuilder.hpp"
#include "utils.hpp"

void RenderSystem::render(ECSManager& ecs, Engine& engine){
    utils::checkGLError("before render, renderSystem");
    for(uint32_t entity : ecs.entities){
        auto* mesh = ecs.meshPool.getComponent(entity);
        auto* transform = ecs.transformPool.getComponent(entity);
        if(!mesh || !transform) continue;

        if(!mesh->init){
            engine.meshBuilder.initMesh(*mesh);
        }

        // setup shaders, uniforms, etc.
        glUseProgram(mesh->pipeline);
        utils::checkGLError("after glUseProgram, renderSystem");

        glBindVertexArray(mesh->VAO);
        utils::checkGLError("after glBindVertexArray, renderSystem");

        // Validate the shader program
        GLint linkStatus;
        glGetProgramiv(mesh->pipeline, GL_LINK_STATUS, &linkStatus);
        if(linkStatus == GL_FALSE){
            GLint logLength;
            glGetProgramiv(mesh->pipeline, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<char> log(logLength);
            glGetProgramInfoLog(mesh->pipeline, logLength, &logLength, log.data());
            std::cerr << "Shader program linking failed: " << log.data() << std::endl;
            continue;
        }

        utils::checkGLError("before draw call, renderSystem");
        glDrawElements(GL_TRIANGLES, mesh->indexBufferData.size(), GL_UNSIGNED_INT, 0);
        utils::checkGLError("after draw call, renderSystem");

        glBindVertexArray(0);
        glUseProgram(0);
    }
    utils::checkGLError("after render, renderSystem");
}