#include "Config.h"
#include <string>
#include <vector>

using namespace std;

Config::Config(const char* path)
{
    m_path = path;
    ReadFile();
}

Config::~Config()
{

}

void Config::ReadFile()
{

}

void Config::WriteFile()
{

}

void Config::AddContent(std::string name, std::string val_str)
{
    m_cfg_content.push_back(name + ' ' + val_str);
}


bool Config::GetString(const std::string name, std::string& val)
{
    if (m_cfg_content.empty()) return false;

    size_t&& name_length = name.length();

    for (std::string& line : m_cfg_content)
    {
        if (!memcmp(name.data(), line.data(), name_length))
        {
            val = line.substr(name_length + 1, line.length() - name_length);
            return true;
        }
    }
    return false;
}

bool Config::GetBool(const std::string name, bool& val)
{
    if (m_cfg_content.empty()) return false;

    size_t&& name_length = name.length();

    for (std::string& line : m_cfg_content)
    {
        if (!memcmp(name.data(), line.data(), name_length))
        {
            val = atoi(line.data() + name.length());
            return true;
        }
    }
    return false;
}

bool Config::GetInt(const std::string name, int& val)
{
    if (m_cfg_content.empty()) return false;

    size_t&& name_length = name.length();

    for (std::string& line : m_cfg_content)
    {
        if (!memcmp(name.data(), line.data(), name_length))
        {

            val = atoi(line.data() + name.length());
            return true;
        }
    }
    return false;
}

bool Config::GetFloat(const std::string name, float& val)
{
    if (m_cfg_content.empty()) return false;

    size_t&& name_length = name.length();

    for (std::string& line : m_cfg_content)
    {
        if (!memcmp(name.data(), line.data(), name_length))
        {
            val = atof(line.data() + name_length);
            return true;
        }
    }
    return false;
}

bool Config::GetStringRight(const std::string& name, std::string& val)
{
    if (m_cfg_content.empty()) return false;

    size_t&& name_length = name.length();

    for (std::string& line : m_cfg_content)
    {
        if (!memcmp(name.data(), line.data(), name_length))
        {
            val = line.substr(name_length + 1, line.length() - name_length);
            return true;
        }
    }
    return false;
}
bool Config::GetBoolRight(const std::string& name, bool& val)
{
    if (m_cfg_content.empty()) return false;

    size_t&& name_length = name.length();

    for (std::string& line : m_cfg_content)
    {
        if (!memcmp(name.data(), line.data(), name_length))
        {
            val = atoi(line.data() + name.length());
            return true;
        }
    }
    return false;
}
bool Config::GetIntRight(const std::string& name, int& val)
{
    if (m_cfg_content.empty()) return false;

    size_t&& name_length = name.length();

    for (std::string& line : m_cfg_content)
    {
        if (!memcmp(name.data(), line.data(), name_length))
        {

            val = atoi(line.data() + name.length());
            return true;
        }
    }
    return false;
}
bool Config::GetFloatRight(const std::string& name, float& val)
{
    if (m_cfg_content.empty()) return false;

    size_t&& name_length = name.length();

    for (std::string& line : m_cfg_content)
    {
        if (!memcmp(name.data(), line.data(), name_length))
        {
            val = atof(line.data() + name_length);
            return true;
        }
    }
    return false;
}

void Config::TryGetString(const std::string name, std::string& val, std::string default_val)
{
    if (!GetStringRight(name, val))
    {
        val = default_val;
        m_cfg_content.push_back(name + ' ' + default_val);
    }
}
void Config::TryGetBool(const std::string name, bool& val, bool default_val)
{
    if (!GetBoolRight(name, val))
    {
        val = default_val;
        m_cfg_content.push_back(name + ' ' + std::to_string(default_val));
    }
}
void Config::TryGetInt(const std::string name, int& val, int default_val)
{
    if (!GetIntRight(name, val))
    {
        val = default_val;
        m_cfg_content.push_back(name + ' ' + std::to_string(default_val));
    }
}
void Config::TryGetFloat(const std::string name, float& val, float default_val)
{
    if (!GetFloatRight(name, val))
    {
        val = default_val;
        m_cfg_content.push_back(name + ' ' + std::to_string(default_val));
    }
}


