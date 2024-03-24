#pragma once
#include "string"
#include "vector"

class Config
{
    private:
    const char* m_path;
    std::vector<std::string> m_cfg_content;
    
    public:
    Config(const char* path);
    ~Config();
    void ReadFile();
    void WriteFile();
    void AddContent(std::string name, std::string val_str);
    
    bool GetString(const std::string name, std::string& val);
    bool GetBool(const std::string name, bool& val);
    bool GetInt(const std::string name, int& val);
    bool GetFloat(const std::string name, float& val);

    bool GetStringRight(const std::string& name, std::string& val);
    bool GetBoolRight(const std::string& name, bool& val);
    bool GetIntRight(const std::string& name, int& val);
    bool GetFloatRight(const std::string& name, float& val);

    void TryGetString(const std::string name, std::string& val, std::string default_val);
    void TryGetBool(const std::string name, bool& val, bool default_val);
    void TryGetInt(const std::string name, int& val, int default_val);
    void TryGetFloat(const std::string name, float& val, float default_val);

    
};
