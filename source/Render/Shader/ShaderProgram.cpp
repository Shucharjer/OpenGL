#include "Render/Shader/ShaderProgram.h"
#include "Render/Shader/Shader.h"
#include "Logger.h"
#include "glm/gtc/type_ptr.hpp"

ShaderProgram::ShaderProgram(const char* vert_path, const char* frag_path)
{
    Shader vert(vert_path, GL_VERTEX_SHADER);
    Shader frag(frag_path, GL_FRAGMENT_SHADER);

    m_Program = glCreateProgram();

    glAttachShader(m_Program, vert.Get());
    glAttachShader(m_Program, frag.Get());

    glLinkProgram(m_Program);

    int success;
    char info[256];
    glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
    if (!success) {
	    glGetProgramInfoLog(m_Program, 256, NULL, info);
	    Logger::Output("failed to link shader program\n", info, '\n');
    }
}
ShaderProgram::~ShaderProgram()
{
    if (m_Program)
    {
        glDeleteProgram(m_Program);
        m_Program = NULL;
    }
}

void ShaderProgram::Use()
{
	if (m_Program) glUseProgram(m_Program);
}

void ShaderProgram::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_Program, name.c_str()), (int)value);
}

void ShaderProgram::SetFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(m_Program, name.c_str()), value);
}

void ShaderProgram::SetInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(m_Program, name.c_str()), value);
}

void ShaderProgram::SetVec2(const std::string& name, float x, float y) const {
	glUniform2f(glGetUniformLocation(m_Program, name.c_str()), x, y);
}

void ShaderProgram::SetVec3(const std::string& name, float val) const {
	glUniform3f(glGetUniformLocation(m_Program, name.c_str()), val, val, val);
}

void ShaderProgram::SetVec3(const std::string& name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(m_Program, name.c_str()), x, y, z);
}

void ShaderProgram::SetVec3(const std::string& name, glm::vec3 vec) const {
	glUniform3fv(glGetUniformLocation(m_Program, name.c_str()), 1, glm::value_ptr(vec));
}

void ShaderProgram::SetVec4(const std::string& name, float x, float y, float z, float w) const {
	glUniform4f(glGetUniformLocation(m_Program, name.c_str()), x, y, z, w);
}
void ShaderProgram::SetVec4(const std::string& name, glm::vec3 vec, float w) const {
	glUniform4fv(glGetUniformLocation(m_Program, name.c_str()), 1, glm::value_ptr(glm::vec4(vec, w)));
}
void ShaderProgram::SetVec4(const std::string& name, glm::vec4 vec) const {
	glUniform4fv(glGetUniformLocation(m_Program, name.c_str()), 1, glm::value_ptr(vec));
}

void ShaderProgram::SetMat4(const std::string& name, glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_Program, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
