#ifndef ECSMANAGER_HPP
#define ECSMANAGER_HPP

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
#include <cmath>
#include <unordered_set> // for keeping track of "divs"
#include <memory>

// own libs
#include "componentPool.hpp"
#include "components.hpp"

class ECSManager{
    public:
        uint32_t createEntity(){
            static uint32_t id = 0;
            entities.push_back(id);
            return id++;
        }

        void update(){};

        std::vector<uint32_t> entities;

        ComponentPool<TransformComponent> transformPool;
        ComponentPool<MeshComponent> meshPool;
    private:
};

#endif // ECSMANAGER_HPP