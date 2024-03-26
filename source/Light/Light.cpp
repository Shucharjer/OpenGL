#include "Light/Light.h"
#include "Light/BaseLight.h"
#include "Light/DirectionalLight.h"
#include "Light/PointLight.h"
#include "Light/SpotLight.h"
#include "Render/Shader/ShaderProgram.h"
#include "Logger.h"
#include <string>

LightManager* LightManager::m_instance = nullptr;

LightManager::LightManager()
{
    if (m_instance)
    {
        Logger::Output("have already create an instance\n");
        return;
    }
    m_instance = this;
}

LightManager::~LightManager()
{
    m_instance = nullptr;
}

bool LightManager::Add(DirectionalLight& dir_light)
{
    if (m_instance != this) return false;
    m_dir_lights.push_back(&dir_light);
    return true;
}

bool LightManager::Add(PointLight& point_light)
{
    if (m_instance != this) return false;
    m_point_lights.push_back(&point_light);
    return true;
}

bool LightManager::Add(SpotLight& spot_light)
{
    if (m_instance != this) return false;
    m_spot_lights.push_back(&spot_light);
    return true;
}

void LightManager::Remove(DirectionalLight& dir_light)
{
    if (m_instance != this) return;
    m_dir_lights.remove(&dir_light);
}

void LightManager::Remove(PointLight& point_light)
{
    if (m_instance != this) return;
    m_point_lights.remove(&point_light);
}

void LightManager::Remove(SpotLight& spot_light)
{
    if (m_instance != this) return;
    m_spot_lights.remove(&spot_light);
}

void LightManager::SetUniforms(ShaderProgram& program)
{
    program.SetInt("dir_light_count", m_dir_lights.size());
    if (m_dir_lights.size())
    {
        for (int i = 0; i < m_dir_lights.size(); i++)
        {
            
        }
    }

    program.SetInt("point_light_count", m_point_lights.size());
    if (m_point_lights.size())
    {
        int i = 0;
        for (PointLight* light : m_point_lights)
        {
            program.SetVec3(std::string("point_lights[") + std::to_string(i) + "].position", light->position);
            program.SetVec3(std::string("point_lights[") + std::to_string(i) + "].ambient", light->ambient);
            program.SetVec3(std::string("point_lights[") + std::to_string(i) + "].diffuse", light->diffuse);
            program.SetVec3(std::string("point_lights[") + std::to_string(i) + "].specular", light->specular);
            program.SetFloat(std::string("point_lights[") + std::to_string(i) + "].constant", light->constant);
            program.SetFloat(std::string("point_lights[") + std::to_string(i) + "].linear", light->linear);
            program.SetFloat(std::string("point_lights[") + std::to_string(i) + "].quadratic", light->quadratic);
            i++;
        }
    }

    program.SetInt("spot_light_count", m_spot_lights.size());
    if (m_spot_lights.size())
    {
        for (int i = 0; i < m_spot_lights.size(); i++)
        {

        }
    }
}
