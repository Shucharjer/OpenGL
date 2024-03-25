#include "Input/Input.h"
#include "Render/HighDynamicRange.h"
#include "Render/Map/MappingManager.h"
#include "imgui.h"
#include "Reference/imgui_impl_glfw.h"
#include "Reference/imgui_impl_opengl3.h"
#include "Logger.h"
#include <GLFW/glfw3.h>
#include <string>
#include "IApplication.h"
#include "Render/HighDynamicRange.cpp"

////////////////////////////////////////////////////
// static vars
////////////////////////////////////////////////////

// singleton
IApplication* IApplication::m_instance = nullptr;
// this point is dispatched by the ctor, so it should not be managed in this class
Config* IApplication::m_config = nullptr;
// this point is created by glfwCreateWindow(), and should be released by glfwTerminate()
GLFWwindow* IApplication::m_window = nullptr;
// new, should be delete by ourselves
Camera* IApplication::g_camera = nullptr;
// new, should be delete by ourselves
Player* IApplication::g_player = nullptr;

Timer IApplication::g_timer;
DisplayConfig IApplication::g_display_config;
MappingManager IApplication::g_mapping_manager;

bool IApplication::g_ignore_cursor_once = true;
bool IApplication::g_ignore_input = false;
double IApplication::g_cursor_pos_x = 0;
double IApplication::g_cursor_pos_y = 0;

////////////////////////////////////////////////////
// funcs
////////////////////////////////////////////////////

std::map<int, KeyState>* p_key_state_map;

void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS)
    {
        (*p_key_state_map)[key].pressed = true;
        (*p_key_state_map)[key].hold = true;
    }
    else if (action == GLFW_RELEASE)
    {
        (*p_key_state_map)[key].released = true;
        (*p_key_state_map)[key].hold = false;
    }
}

void Cursor_Callback(GLFWwindow* window, double x, double y)
{
    if (IApplication::g_ignore_input) return;

    if (IApplication::g_ignore_cursor_once)
    {
        IApplication::g_cursor_pos_x = x;
        IApplication::g_cursor_pos_y = y;
        IApplication::g_ignore_cursor_once = false;
    }
    

    float xOff = x - IApplication::g_cursor_pos_x;
    float yOff = y - IApplication::g_cursor_pos_y;

    IApplication::g_cursor_pos_x = x;
    IApplication::g_cursor_pos_y = y;

    xOff *= IApplication::g_camera->sensivity;
    yOff *= IApplication::g_camera->sensivity;

    IApplication::g_camera->yaw += xOff;
    IApplication::g_camera->pitch += -yOff;

    if (IApplication::g_camera->pitch > 89.99f) IApplication::g_camera->pitch = 89.99f;
    if (IApplication::g_camera->pitch < -89.99f) IApplication::g_camera->pitch = -89.99f;

    if (IApplication::g_camera->yaw > 180.0f) IApplication::g_camera->yaw = -180.0f;
    if (IApplication::g_camera->yaw < -180.0f) IApplication::g_camera->yaw = 180.0f;

    glm::vec3 front = glm::vec3(0.0f);
    front.x = cos(glm::radians(IApplication::g_camera->pitch)) * cos(glm::radians(IApplication::g_camera->yaw));
    front.y = sin(glm::radians(IApplication::g_camera->pitch));
    front.z = cos(glm::radians(IApplication::g_camera->pitch)) * sin(glm::radians(IApplication::g_camera->yaw));
    IApplication::g_camera->front = glm::normalize(front);
    IApplication::g_camera->right = glm::cross(IApplication::g_camera->front, IApplication::g_camera->up);
}

void Framebuffer_Size_Callback(GLFWwindow* window, int width, int height)
{
    IApplication::g_display_config.width = width;
    IApplication::g_display_config.height = height;
}

IApplication::IApplication(Config* config)
{
    if (m_instance)
    {
        Logger::Output("an application instance has already run\n");
        exit(-1);
    }
    else {
        m_instance = this;
    }
    m_config = config;
}

IApplication::~IApplication()
{
    m_config->WriteFile();
    delete g_camera;
    glfwTerminate();
}

void IApplication::Init()
{
// glfw init
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
#if defined(MAC_OS)
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_config->TryGetBool("fullscreen", g_display_config.fullscreen, false);

    m_config->TryGetBool("vsync", g_display_config.vsync, false);;

    m_config->TryGetBool("hdr", g_display_config.hdr, true);

    m_config->TryGetBool("msaa", g_display_config.msaa, true);
    m_config->TryGetInt("num_samples", g_display_config.num_samples, 4);

    m_config->TryGetInt("width", g_display_config.width, 1280);
    m_config->TryGetInt("height", g_display_config.height, 960);

    m_config->TryGetInt("port_width", g_display_config.port_width, 1280);
    m_config->TryGetInt("port_height", g_display_config.port_height, 960);

    m_config->TryGetFloat("near", g_display_config.near, 0.1f);
    m_config->TryGetFloat("far", g_display_config.far, 1200.0f);

    m_config->TryGetFloat("gamma", g_display_config.gamma, 2.2f);
    
    m_window = glfwCreateWindow(g_display_config.width, g_display_config.height, g_display_config.name, nullptr, nullptr);
    if (!m_window)
    {
        Logger::Output("failed to create GLFW window\n");
        glfwTerminate();
        return;
    }
    
    glfwMakeContextCurrent(m_window);
    

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::Output("Failed to initialize GLAD\n");
        glfwTerminate();
        return;
    }

    // create imgui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // setup imgui style
    ImGui::StyleColorsDark();

    // setup platform
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    
    ImGui_ImplOpenGL3_Init("#version 330");

    g_camera = new Camera();
    p_key_state_map = &KeyInput::key_state_map;
    glfwSetKeyCallback(m_window, Key_Callback);
    glfwSetCursorPosCallback(m_window, Cursor_Callback);
    glfwSetFramebufferSizeCallback(m_window, Framebuffer_Size_Callback);
    OnInit();
}

void IApplication::Run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        
        Update();
        glfwSwapInterval(g_display_config.vsync);
        HighDynamicRange::Set(g_display_config.hdr);
        if (g_display_config.msaa) glEnable(GL_MULTISAMPLE);
        else glDisable(GL_MULTISAMPLE);
        glViewport(0, 0, g_display_config.width, g_display_config.height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.73f, 0.8f, 1.0f, 1.0f);
        if (g_display_config.hdr) HighDynamicRange::UseFramebuffer(g_display_config.width, g_display_config.height);
        Render();
        if (g_display_config.hdr) HighDynamicRange::DrawFramebuffer(g_display_config.gamma);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);
        KeyInput::Update();
    }
}
