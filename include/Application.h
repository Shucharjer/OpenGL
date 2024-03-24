#pragma once
#include "IApplication.h"
#include "Render/Shader/ShaderProgram.h"
#include <memory>
#include "Render/Map/CubeMap.h"


class Application : public IApplication
{
    private:
    ShaderProgram* skybox_shader;
    CubeMap* skybox;
    ShaderProgram* depth_shader;

    public:
    Application(Config* config);
    ~Application();

    void OnInit() override;
    void Update() override;
    void Render() override;
};
