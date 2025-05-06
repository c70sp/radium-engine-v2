#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

// Own libs
#include "ecs/ECSManager.hpp"
#include "engine.hpp"

class Engine;

class RenderSystem{
    public:
        void render(ECSManager& ecs, Engine& engine);

    private:
};

#endif // RENDERSYSTEM_HPP