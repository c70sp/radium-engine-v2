#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

// C++ STL
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <sstream>

struct FileData{
    std::filesystem::file_time_type lastWriteTime;
    bool dirty = true;
    std::unordered_map<std::string, std::string> variables;
};

class FileHandler{
    public:
        void watchFile(const std::string& location);
        void watchFolder(const std::string& location);

        void checkChanges();



        //!? vvvvvvvvvvvvvvv GET VAR TEMPLATE vvvvvvvvvvvvvvv
        template<typename T>
        T getVar(const std::string& location, const std::string& varName, const T& fallBack){
            auto it = files.find(location);
            if(it == files.end()){
                std::cerr << "Tried to get var of unwatched file \"" << location << "\"!" << std::endl;
                return fallBack;
            }

            FileData& data = it->second;
            if(data.dirty) parseFile(location);

            if(auto it = data.variables.find(varName); it != data.variables.end()){
                std::istringstream ss(it->second);
                T value;
                if(ss >> value) return value;
            }

            return fallBack; // couldn't find or couldn't parse
        }
        //!? ^^^^^^^^^^^^^^^ GET VAR TEMPLATE ^^^^^^^^^^^^^^^



    private:
        void parseFile(const std::string& location);

        std::unordered_map<std::string, FileData> files; // string with location, last change date
        // The maps will mainly be useful for shit like shaders, where looking up shit once per frame is not good
        // maybe seperate for shaders
};

#endif // FILEHANDLER_HPP