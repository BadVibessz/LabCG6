#include "FileManager.h"

std::string FileManager::ReadFile(const char* path)
{
    std::ifstream file(path);
    std::string source{ std::istreambuf_iterator<char>(file), 
        std::istreambuf_iterator<char>() };
    return source;
}
