#pragma once

#include "Render/Shader/ShaderProgram.h"
#include "Texture.h"
#include "CubeMap.h"
#include "list"

class MappingManager
{
private:
    static MappingManager* m_instance;
    
    static std::list<std::string> m_texture_paths;
    static std::list<Texture*> m_texture_list;

    static bool m_cube_data_created;
    static GLuint m_cube_vao;
    static GLuint m_cube_vbo;
    static std::list<std::string> m_cubemap_paths;
    static std::list<CubeMap*> m_cube_list;
public:
    MappingManager();
    ~MappingManager();

    static bool ReadTexture2DDirectly(const char* path, GLenum target, bool gamma = false);
    
    static bool CreateTexture2D(const char* path, GLenum target, bool gamma = false);
    static void DeleteTexture2D(Texture* ptr);
    static CubeMap* CreateCubeMap(const char* folder_path, bool is_jpg, bool gamma = false);
    static void DeleteCubeMap(CubeMap* ptr);
};