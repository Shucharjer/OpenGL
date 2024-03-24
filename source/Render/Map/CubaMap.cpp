#include "Render/Map/CubeMap.h"
#include "Render/Shader/ShaderProgram.h"



CubeMap::CubeMap()
    : VAO(NULL), VBO(NULL), m_texture(NULL)
{
    
}

CubeMap::~CubeMap()
{
    glDeleteTextures(1, &m_texture);
}

void CubeMap::Draw(ShaderProgram& program)
{
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
