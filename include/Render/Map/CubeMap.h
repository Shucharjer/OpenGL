#pragma once
#include "Render/Shader/ShaderProgram.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
class CubeMap
{
    friend class MappingManager;
    private:
    GLuint VAO, VBO;
    GLuint m_texture;
    std::string m_folder_path;
    public:
    CubeMap();
    ~CubeMap();
    void Draw(ShaderProgram& program);
};
