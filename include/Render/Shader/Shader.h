#pragma once
#include "glad/glad.h"

class Shader
{
    private:
    GLuint m_Shader;
    public:
    Shader(const char* path, GLenum type);
    ~Shader();
    Shader(const Shader& obj) = delete;
    Shader(Shader&& obj) = delete;
    Shader& operator=(const Shader& obj) = delete;
    Shader& operator=(Shader& obj) = delete;

    GLuint Get() const { return m_Shader; }
};