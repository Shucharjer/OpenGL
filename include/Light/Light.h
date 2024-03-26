#pragma once
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Render/Shader/ShaderProgram.h"
#include "SpotLight.h"
#include "list"
#include "vector"


class LightManager
{
private:
    static LightManager* m_instance;
    std::list<DirectionalLight*> m_dir_lights;
    std::list<PointLight*> m_point_lights;
    std::list<SpotLight*> m_spot_lights;
public:
    LightManager();
    ~LightManager();
    bool Add(DirectionalLight& dir_light);
    bool Add(PointLight& point_light);
    bool Add(SpotLight& spot_light);
    void Remove(DirectionalLight& dir_light);
    void Remove(PointLight& point_light);
    void Remove(SpotLight& spot_light);
    void SetUniforms(ShaderProgram& program);
};

