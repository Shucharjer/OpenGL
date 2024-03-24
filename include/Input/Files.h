#pragma once
#include "string"
#include "vector"
namespace Files
{
    void GetAllFiles(const std::string folder_path, std::vector<std::string>& files);
    void GetAllFormatFiles(const std::string folder_path, std::vector<std::string>& files, const char* format);
}