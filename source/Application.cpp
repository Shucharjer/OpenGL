#include "Application.h"
#include "IApplication.h"
#include "Input/Input.h"
#include "Logger.h"
#include "Render/Framebuffer.h"
#include "Render/Map/MappingManager.h"
#include "Render/Shader/ShaderProgram.h"
#include <GLFW/glfw3.h>
#include <cstddef>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/fwd.hpp>
#include <imgui.h>

float CubeVertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

GLFWwindow* application_window;

Application::Application(Config* config)
    : IApplication(config)
{

}

GLuint VAO, VBO;
GLuint Ambient;
GLuint Specular;
GLuint hdr_fbo;

void Application::OnInit()
{
    application_window = m_window;

    skybox_shader = new ShaderProgram("resource/shader/skybox.vsh", "resource/shader/skybox.fsh");
    skybox = MappingManager::CreateCubeMap("resource/skybox/", true);

    depth_shader = new ShaderProgram("resource/shader/depth.vsh", "resource/shader/depth.fsh");
    nonlight_shader = new ShaderProgram("resource/shader/light/none.vsh", "resource/shader/light/none.fsh");
    flat_shader = new ShaderProgram("resource/shader/light/flat.vsh", "resource/shader/light/flat.fsh");
    gouraud_shader = new ShaderProgram("resource/shader/light/gouraud.vsh", "resource/shader/light/gouraud.fsh");
    phong_shader = new ShaderProgram("resource/shader/light/phong.vsh", "resource/shader/light/phong.fsh");
    bilnn_phong_shader = new ShaderProgram("resource/shader/light/blinn_phong.vsh", "resource/shader/light/blinn_phong.fsh");
    hdr_shader = new ShaderProgram("resource/shader/hdr.vsh", "resource/shader/hdr.fsh");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), &CubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

    glGenTextures(1, &Ambient);
    glBindTexture(GL_TEXTURE_2D, Ambient);
    MappingManager::ReadTexture2D("resource/texture/container2.png", GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenTextures(1, &Specular);
    glBindTexture(GL_TEXTURE_2D, Specular);
    MappingManager::ReadTexture2D("resource/texture/container2.png", GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);



    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Application::~Application()
{
    MappingManager::DeleteCubeMap(skybox);
    delete skybox_shader;
    delete depth_shader;
    delete nonlight_shader;
    delete flat_shader;
    delete gouraud_shader;
    delete phong_shader;
    delete bilnn_phong_shader;

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
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
bool DrawWithHDR = false;

int UseShader = 0;
typedef enum { Shading_None, Shading_Depth, Shading_Flat, Shading_Gouraud, Shading_Phong, Shading_Blinn_Phong } Shading;

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
        ImGui::Checkbox("Skybox", &DrawSkybox);
        ImGui::SameLine();
        ImGui::Checkbox("Vsync", &g_display_config.vsync);
        ImGui::SameLine();
        ImGui::Checkbox("Multi-Sample Anti-Aliasing", &g_display_config.msaa);
        ImGui::SameLine();
        ImGui::Checkbox("Hight Dynamic Range", &g_display_config.hdr);
        
        ImGui::RadioButton("Depth", &UseShader, Shading_Depth);
        ImGui::SameLine();
        ImGui::RadioButton("No Light", &UseShader, Shading_None);
        ImGui::SameLine();
        ImGui::RadioButton("Flat", &UseShader, Shading_Flat);
        ImGui::SameLine();
        ImGui::RadioButton("Gouraud", &UseShader, Shading_Gouraud);
        ImGui::SameLine();
        ImGui::RadioButton("Phong", &UseShader, Shading_Phong);
        ImGui::SameLine();
        ImGui::RadioButton("Blinn-Phong", &UseShader, Shading_Blinn_Phong);
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

void DrawBox(ShaderProgram& program)
{
    for (GLuint i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.25 * i));
        model = glm::translate(model, cubePositions[i] * 5.0f);
        model = glm::rotate(model, glm::radians(15.f * i), glm::vec3(1.0f, 0.3f, 0.5f));
        program.SetMat4("model", model);
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Ambient);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
}


void Application::Render()
{
    glEnable(GL_DEPTH_TEST);
    
    glm::mat4 model(1.0f);
    glm::mat4 view = g_camera->GetViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(g_camera->fov),
    (float)g_display_config.port_width / (float)g_display_config.port_height, g_display_config.near, g_display_config.far);
    // shadow

    // object
    if (DrawWithHDR)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, hdr_buffer->GetObject());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    // draw objects not transparent
    if (UseShader == Shading_None)
    {
        nonlight_shader->Use();
        nonlight_shader->SetMat4("view", view);
        nonlight_shader->SetMat4("proj", proj);
        nonlight_shader->SetInt("texture_ambient", 0);
        DrawBox(*nonlight_shader);
    }
    else if (UseShader == Shading_Depth)
    {
        depth_shader->Use();
        depth_shader->SetMat4("view", view);
        depth_shader->SetMat4("proj", proj);
        depth_shader->SetFloat("near", g_display_config.near);
        depth_shader->SetFloat("far", g_display_config.far);
        DrawBox(*depth_shader);
    }
    else if (UseShader == Shading_Flat)
    {

    }
    else if (UseShader == Shading_Gouraud)
    {

    }
    else if (UseShader == Shading_Phong)
    {

    }
    else if (UseShader == Shading_Blinn_Phong)
    {

    }

    // draw objects transparent
    // ...

    // hdr texture is draw at z 0, so we need to draw skybox after draw hdr texture
    if (DrawSkybox)
    {
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_FALSE);
        skybox_shader->Use();
        glm::mat4 skybox_view = glm::mat4(glm::mat3(view));
        skybox_shader->SetMat4("view", skybox_view);
        skybox_shader->SetMat4("proj", proj);
        skybox_shader->SetInt("skybox_texture", 0);
        skybox->Draw(*skybox_shader);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);
    }
}

