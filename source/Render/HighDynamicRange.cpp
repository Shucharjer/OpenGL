#include "Render/HighDynamicRange.h"
#include "IApplication.h"
#include "Render/Framebuffer.h"
#include "Logger.h"
#include "Render/Shader/ShaderProgram.h"

HDRMonitor* HDRMonitor::m_instance;

HDRMonitor HighDynamicRange::hdr_monitor;

bool HighDynamicRange::enable = false;
bool HighDynamicRange::msaa = false;
int HighDynamicRange::num_samples = 4;
GLuint HighDynamicRange::framebuffer = NULL;
GLuint HighDynamicRange::color_buffer = NULL;
GLuint HighDynamicRange::depth_buffer = NULL;
GLuint HighDynamicRange::vao = NULL;
GLuint HighDynamicRange::vbo = NULL;
ShaderProgram* HighDynamicRange::hdr_shader;

HDRMonitor::HDRMonitor()
{
    if (m_instance)
    {
        return;
    }
    m_instance = this;
}

HDRMonitor::~HDRMonitor()
{
    if (HighDynamicRange::enable)
    {
        HighDynamicRange::DeleteHDRFramebuffer();
    }
}

void HighDynamicRange::Set(bool boolean)
{
    enable = boolean;
}

void HighDynamicRange::CreateHDRFramebuffer(int width, int height)
{
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // gen color buffer
    color_buffer = Framebuffer::GenerateColorBuffer(GL_TEXTURE_2D, GL_RGBA16F, width, height, GL_RGBA, GL_FLOAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // gen depth buffer
    depth_buffer = Framebuffer::GenerateRenderBuffer(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    // attach buffers to framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_buffer, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_buffer);


    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        Logger::Output("High Dynamic Range: Framebuffer not complete\n");
    }

    GLfloat quad_vertices[] = {
        // Positions                    // Texture Coords
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), &quad_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    hdr_shader = new ShaderProgram("resource/shader/hdr.vsh", "resource/shader/hdr.fsh");
}

void HighDynamicRange::DeleteHDRFramebuffer()
{
    if (!framebuffer) return;

    glDeleteTextures(1, &color_buffer);
    color_buffer = NULL;
    glDeleteBuffers(1, &depth_buffer);
    depth_buffer = NULL;
    glDeleteFramebuffers(1, &framebuffer);
    framebuffer = NULL;
    glDeleteVertexArrays(1, &vao);
    vao = NULL;
    glDeleteBuffers(1, &vbo);
    vbo = NULL;
    delete hdr_shader;
}

void HighDynamicRange::UseFramebuffer(int width, int height)
{
    if (!enable)
    {
        if (framebuffer) DeleteHDRFramebuffer();
        return;
    }

    if (!framebuffer) CreateHDRFramebuffer(width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0.73f, 0.8f, 1.0f, 1.0f);
}

void HighDynamicRange::DrawFramebuffer(float gamma)
{
    if (!enable) return;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    hdr_shader->Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, color_buffer);
    hdr_shader->SetInt("hdr_color_buffer", 0);
    // this value, exposure, will be automaticlly set one day
    hdr_shader->SetFloat("exposure", 1.0f);
    hdr_shader->SetFloat("gamma", gamma);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}