#pragma once
#include "glad/glad.h"
#include "glfw/glfw3.h"

class Framebuffer
{
private:
    GLuint m_object;
public:
    Framebuffer();
    // e.g. GL_TEXTURE_2D, GL_RGBA16F, 1920, 1080, GL_RGBA, GL_FLOAT. Need to set parameters after calling this function.
    static GLuint GenerateColorBuffer(GLenum target, GLint internal_format, int width, int height, GLint color_format, GLenum type);
    // e.g. GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1920, 1080
    static GLuint GenerateRenderBuffer(GLenum buffer_type, GLenum component_type, int width, int height);
    GLuint GetObject() { return m_object; }
    GLuint* GetAddressOf() { return &m_object; }
    ~Framebuffer();
};