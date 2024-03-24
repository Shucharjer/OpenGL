#pragma once
#include "Timer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Config.h"

#include "Camera.h"
#include "Player.h"
#include "Input/Input.h"

struct DisplayConfig
{
    bool fullscreen;
    bool vsync;

    int width;
    int height;

    int port_width;
    int port_height;

    const char* name = "Unique Engine";
};

class IApplication
{
    protected:

    static IApplication* m_instance;
    static Config* m_config;
    static GLFWwindow* m_window;

    public:
    static Camera* g_camera;
    static Player* g_player;

    static Timer g_timer;
    static DisplayConfig g_display_config;

    IApplication(Config* config);
    ~IApplication();

    IApplication(const IApplication& obj) = delete;
    IApplication(IApplication&& obj) = delete;
    IApplication& operator=(const IApplication& obj) = delete;
    IApplication& operator=(IApplication&& obj) = delete;
    
    void Init();
    void Run();

    virtual void OnInit() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;

    static bool g_ignore_cursor_once;
    static bool g_ignore_input;
    static double g_cursor_pos_x;
    static double g_cursor_pos_y;
};