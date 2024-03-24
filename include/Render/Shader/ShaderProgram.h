#pragma once
#include "glad/glad.h"
#include "string"
#include "glm/glm.hpp"

class ShaderProgram
{
    private:
    GLuint m_Program;
    public:
    ShaderProgram(const char* vert_path, const char* frag_path);
    ~ShaderProgram();
    void Use();
    void SetBool(const std::string& name, bool value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetInt(const std::string& name, int value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string& name, float val) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetVec3(const std::string& name, glm::vec3 vec) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    void SetVec4(const std::string& name, glm::vec3 vec, float w) const;
    void SetVec4(const std::string& name, glm::vec4 vec) const;
    void SetMat4(const std::string& name, glm::mat4& mat) const;
};
