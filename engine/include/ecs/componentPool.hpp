#ifndef COMPONENTPOOL_HPP
#define COMPONENTPOOL_HPP

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
#include <unordered_set>
#include <unordered_map>
#include <memory>

template<typename T>
class ComponentPool{
    public:
        void addComponent(uint32_t entity, const T& component){
            components.emplace(entity, component);
        }

        void removeComponent(uint32_t entity){
            components.erase(entity);
        }

        T* getComponent(uint32_t entity){
            auto it = components.find(entity);
            if (it != components.end()) {
                return &it->second;
            } else {
                return nullptr;
            }
        }

        void printState() const {
            std::cout << "Current state of components:" << std::endl;
            for (const auto& [entity, component] : components) {
                std::cout << "Entity: " << entity << std::endl;
            }
        }

    private:
        std::unordered_map<uint32_t, T> components; // Removed 'const' qualifier from T
};

#endif // COMPONENTPOOL_HPP