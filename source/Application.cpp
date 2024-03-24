#include "Application.h"
#include "IApplication.h"
#include "Input/Input.h"
#include "Render/Map/MappingManager.h"
#include "Render/Shader/ShaderProgram.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/fwd.hpp>
#include <imgui.h>

GLFWwindow* application_window;

Application::Application(Config* config)
    : IApplication(config)
{

}

void Application::OnInit()
{
    application_window = m_window;

    skybox_shader = new ShaderProgram("resource/shader/skybox_vert.glsl", "resource/shader/skybox_frag.glsl");
    skybox = MappingManager::CreateCubeMap("resource/skybox/", true);

    depth_shader = new ShaderProgram("resource/shader/depth_vert.glsl", "resource/shader/depth_frag.glsl");





    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Application::~Application()
{
    delete skybox_shader;
    delete depth_shader;
}


void ProcessKeyInput()
{
    if (KeyInput::IsPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(application_window, GL_TRUE);
    }

    glm::vec3 movement(0.0f);
    if (KeyInput::IsHold(GLFW_KEY_W))
    {
        movement += IApplication::g_camera->front;
    }
    if (KeyInput::IsHold(GLFW_KEY_S))
    {
        movement -= IApplication::g_camera->front;
    }
    if (KeyInput::IsHold(GLFW_KEY_A))
    {
        movement -= IApplication::g_camera->right;
    }
    if (KeyInput::IsHold(GLFW_KEY_D))
    {
        movement += IApplication::g_camera->right;
    }
    if (glm::length(movement) > 0.0f)
    {
        movement = glm::normalize(movement);
        if (KeyInput::IsHold(GLFW_KEY_LEFT_SHIFT))
        {
            movement *= 0.2f;
        }
        IApplication::g_camera->pos += movement * 250.0f * IApplication::g_timer.GetDeltaTime();
    }
}

bool DrawImGuiLayer = false;
bool DrawSkybox = true;
bool DrawDepth = false;
bool DrawWithVsync = true;

int UseShading = 0;
typedef enum { Shading_None, Shading_Flat, Shading_Gouraud, Shading_Phong, Shading_Blinn_Phong } Shading;

void Application::Update()
{
    ProcessKeyInput();
    g_timer.Update();

    KeyInput::Toggle(GLFW_KEY_GRAVE_ACCENT, DrawImGuiLayer);
    if (DrawImGuiLayer)
    {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        g_ignore_input = true;
        ImGui::Begin("Unique Engine");
        ImGui::Text("FPS: %d, MSPF: %f", g_timer.GetFramesInLastSecond(), 1000.0 / g_timer.GetFramesInLastSecond());
        ImGui::Text("pos: %f, %f, %f", g_camera->pos.x, g_camera->pos.y, g_camera->pos.z);
        ImGui::Text("ang: %f, %f, %f", g_camera->pitch, g_camera->yaw, g_camera->roll);
        if (ImGui::Button("Skybox"))
        {
            DrawSkybox = !DrawSkybox;
        }
        ImGui::SameLine();
        if (ImGui::Button("Vsync"))
        {
            DrawWithVsync = !DrawWithVsync;
        }
        ImGui::SameLine();
        if (ImGui::Button("Depth"))
        {
            DrawDepth = !DrawDepth;
        }
        ImGui::RadioButton("No Light", &UseShading, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Flat", &UseShading, 1);
        ImGui::SameLine();
        ImGui::RadioButton("Gouraud", &UseShading, 2);
        ImGui::SameLine();
        ImGui::RadioButton("Phong", &UseShading, 3);
        ImGui::SameLine();
        ImGui::RadioButton("Blinn-Phong", &UseShading, 4);
        ImGui::End();
    }
    else
    {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if (g_ignore_input)
        {
            g_ignore_input = false;
            g_ignore_cursor_once = true;
        }
    }
}

void Application::Render()
{
    //glEnable(GL_DEPTH_TEST);
    if (DrawWithVsync)
    {
        glfwSwapInterval(1);
    }
    else {
        glfwSwapInterval(0);
    }
    
    glm::mat4 model(1.0f);
    glm::mat4 view = g_camera->GetViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(g_camera->fov), (float)g_display_config.port_width / (float)g_display_config.port_height, 0.1f, 100.0f);
    glViewport(0, 0, g_display_config.width, g_display_config.height);
    glClearColor(0.73f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    if (DrawSkybox)
    {
        glDepthMask(GL_FALSE);
        skybox_shader->Use();
        glm::mat4 skybox_view = glm::mat4(glm::mat3(view));
        skybox_shader->SetMat4("view", skybox_view);
        skybox_shader->SetMat4("proj", proj);
        skybox_shader->SetInt("skybox_texture", 0);
        skybox->Draw(*skybox_shader);
        glDepthMask(GL_TRUE);
    }

    // shadow

    // object

    if (DrawDepth)
    {
        depth_shader->Use();
    }
    else
    if (UseShading == Shading_None)
    {

    }
    else if (UseShading == Shading_Flat)
    {

    }
    else if (UseShading == Shading_Gouraud)
    {

    }
    else if (UseShading == Shading_Phong)
    {

    }
    else if (UseShading == Shading_Blinn_Phong)
    {

    }
}
