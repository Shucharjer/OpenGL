#pragma once
#include "IApplication.h"
#include "Render/Shader/ShaderProgram.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"

class HDRMonitor
{
    private:
    static HDRMonitor* m_instance;
    public:
    HDRMonitor();
    HDRMonitor(const HDRMonitor& obj) = delete;
    HDRMonitor(HDRMonitor&& obj) = delete;
    HDRMonitor& operator=(const HDRMonitor& obj) = delete;
    HDRMonitor& operator=(HDRMonitor&& obj) = delete;
    ~HDRMonitor();
};

class HighDynamicRange
{
    friend class HDRMonitor;
    friend class IApplication;
private:
    // if forget to set hdr off, this obj will do it
    static HDRMonitor hdr_monitor;

    static bool hdr_enable;
    static bool bloom_enable;
    static GLuint framebuffer;
    static GLuint color_buffer;
    static GLuint depth_buffer;
    static GLuint vao;
    static GLuint vbo;
    static ShaderProgram* hdr_shader;

    static void CreateHDRFramebuffer(int width, int height);
    static void DeleteHDRFramebuffer();

    static void UseFramebuffer(int width, int height);
    static void DrawFramebuffer(float gamma = 2.2f);
    
public:
    static bool IsEnable() { return hdr_enable; }
    static void Set(bool boolean, bool bloom);
    static void ResetFramebuffer();
};



