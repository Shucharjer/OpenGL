#include "Render/Framebuffer.h"

Framebuffer::Framebuffer()
{
    glGenFramebuffers(1, &m_object);
    glBindFramebuffer(GL_FRAMEBUFFER, m_object);
    
}

GLuint Framebuffer::GenerateColorBuffer(GLenum target, GLint internal_format, int width, int height, GLint color_format, GLenum type)
{
    GLuint buffer;
    glGenTextures(1, &buffer);
    glBindTexture(target, buffer);
    glTexImage2D(target, 0, internal_format, width, height, 0, color_format, type, NULL);
    return buffer;
}

GLuint Framebuffer::GenerateRenderBuffer(GLenum buffer_type, GLenum component_type, int width, int height)
{
    GLuint buffer;
    glGenRenderbuffers(1, &buffer);
    glBindRenderbuffer(buffer_type, buffer);
    glRenderbufferStorage(buffer_type, component_type, width, height);
    return buffer;
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &m_object);
}
