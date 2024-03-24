#include "Logger.h"
#include "Render/Shader/Shader.h"
#include <cstddef>
#include <fstream>
#include <sstream>

Shader::Shader(const char* path, GLenum type)
{
    std::ifstream shader_file;
    std::string shader_source_str;
    const char* shader_source;

    shader_file.exceptions(std::fstream::badbit | std::fstream::failbit);

    try
    {
        shader_file.open(path);
        std::stringstream stream;
        stream << shader_file.rdbuf();
        shader_file.close();
        shader_source_str = stream.str();
    }
    catch (std::ifstream::failure e)
    {
        Logger::Output("failed to open shader file at ", path, '\n');
    }

    shader_source = shader_source_str.c_str();
    m_Shader = glCreateShader(type);
    glShaderSource(m_Shader, 1, &shader_source, NULL);
    glCompileShader(m_Shader);

    int success;
    char info[256];
    glGetShaderiv(m_Shader, GL_COMPILE_STATUS, &success);
    if (!success) {
	    glGetShaderInfoLog(m_Shader, 256, NULL, info);
	    Logger::Output("failed to compile shader\n", info, '\n');
    }
}

Shader::~Shader()
{
    if (m_Shader)
    {
        glDeleteShader(m_Shader);
        m_Shader = NULL;
    }
}
