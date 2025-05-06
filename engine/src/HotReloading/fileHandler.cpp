// C++ STL
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

// Own libs
#include "HotReloading/fileHandler.hpp"

void FileHandler::watchFile(const std::string& location){
    FileData data;
    data.lastWriteTime = std::filesystem::last_write_time(location);
    data.dirty = true;

    files.emplace(location, data);

    std::cout << "File \"" << location << "\" added to file watcher" << std::endl;
}

void FileHandler::checkChanges(){
    for(auto& [location, data] : files){
        auto current = std::filesystem::last_write_time(location);
        if(current != data.lastWriteTime){
            std::cout << "File at location \"" << location << "\" has changed." << std::endl;
            data.lastWriteTime = current;
            data.dirty = true;
        }
    }
}

void FileHandler::parseFile(const std::string& location){
    auto it = files.find(location);
    if(it == files.end()){
        std::cerr << "Tried to parse unwatched file \"" << location << "\"!" << std::endl;
        return;
    }

    FileData& data = it->second;
    data.variables.clear();

    std::ifstream myFile(location);
    std::string line;
    while(std::getline(myFile, line)){
        size_t equalPos = line.find("=");
        if(equalPos != std::string::npos){
            std::string key = line.substr(0, equalPos);
            std::string value = line.substr(equalPos + 1);

            data.variables[key] = value;
        }
    }
    data.dirty = false;
}