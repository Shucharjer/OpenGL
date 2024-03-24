#pragma once

#include "Render/Shader/ShaderProgram.h"
#include "Render/Vertex.h"
#include "vector"
#include "Render/Map/Texture.h"

class Mesh
{
    private:
    GLuint VAO, VBO, EBO;

    
    public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
    ~Mesh();

    void Draw(const ShaderProgram* program);
};