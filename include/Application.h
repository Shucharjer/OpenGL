#pragma once
#include "IApplication.h"
#include "Render/Framebuffer.h"
#include "Render/Shader/ShaderProgram.h"
#include <memory>
#include <queue>
#include "Render/Map/CubeMap.h"


class Application : public IApplication
{
    private:
    ShaderProgram* skybox_shader = nullptr;
    CubeMap* skybox = nullptr;

    ShaderProgram* depth_shader = nullptr;
    ShaderProgram* nonlight_shader = nullptr;
    ShaderProgram* flat_shader = nullptr;
    ShaderProgram* gouraud_shader = nullptr;
    ShaderProgram* phong_shader = nullptr;
    ShaderProgram* bilnn_phong_shader = nullptr;

    // hight dynamic range
    ShaderProgram* hdr_shader = nullptr;
    Framebuffer* hdr_buffer = nullptr;
    GLuint hdr_color_buffer;
    GLuint hdr_depth_buffer;

    // distance, object
    // std::map<float, > not_transparent_objects
    // distance, object
    // std::map<float, > transparent_objects
    public:
    Application(Config* config);
    ~Application();

    void OnInit() override;
    void Update() override;
    void Render() override;
};
