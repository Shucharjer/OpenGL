#include "Render/Map/MappingManager.h"
#include "Render/Map/CubeMap.h"
#include "Render/Shader/ShaderProgram.h"
#include "stb_image.h"
#include "vector"
#include <cstddef>

float CubeVertices[] = {
// positions          
-1.0f,  1.0f, -1.0f,
-1.0f, -1.0f, -1.0f,
 1.0f, -1.0f, -1.0f,
 1.0f, -1.0f, -1.0f,
 1.0f,  1.0f, -1.0f,
-1.0f,  1.0f, -1.0f,

-1.0f, -1.0f,  1.0f,
-1.0f, -1.0f, -1.0f,
-1.0f,  1.0f, -1.0f,
-1.0f,  1.0f, -1.0f,
-1.0f,  1.0f,  1.0f,
-1.0f, -1.0f,  1.0f,

 1.0f, -1.0f, -1.0f,
 1.0f, -1.0f,  1.0f,
 1.0f,  1.0f,  1.0f,
 1.0f,  1.0f,  1.0f,
 1.0f,  1.0f, -1.0f,
 1.0f, -1.0f, -1.0f,

-1.0f, -1.0f,  1.0f,
-1.0f,  1.0f,  1.0f,
 1.0f,  1.0f,  1.0f,
 1.0f,  1.0f,  1.0f,
 1.0f, -1.0f,  1.0f,
-1.0f, -1.0f,  1.0f,

-1.0f,  1.0f, -1.0f,
 1.0f,  1.0f, -1.0f,
 1.0f,  1.0f,  1.0f,
 1.0f,  1.0f,  1.0f,
-1.0f,  1.0f,  1.0f,
-1.0f,  1.0f, -1.0f,

-1.0f, -1.0f, -1.0f,
-1.0f, -1.0f,  1.0f,
 1.0f, -1.0f, -1.0f,
 1.0f, -1.0f, -1.0f,
-1.0f, -1.0f,  1.0f,
 1.0f, -1.0f,  1.0f
};

std::vector<std::string> Faces_JPG{"right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"};
std::vector<std::string> Faces_PNG{"right.png", "left.png", "top.png", "bottom.png", "front.png", "back.png"};

//////////////////////////////////////////////
MappingManager* MappingManager::m_instance = nullptr;

std::list<std::string> MappingManager::m_texture_paths;
std::list<Texture*> MappingManager::m_texture_list;

bool MappingManager::m_cube_data_created = false;
GLuint MappingManager::m_cube_vao;
GLuint MappingManager::m_cube_vbo;
std::list<std::string> MappingManager::m_cubemap_paths;
std::list<CubeMap*> MappingManager::m_cube_list;

MappingManager::MappingManager()
{
    if (m_instance)
    {
        return;
    }
    m_instance = this;
}

MappingManager::~MappingManager()
{
    if (m_cube_data_created)
    {
        glDeleteBuffers(1, &m_cube_vbo);
        glDeleteBuffers(1, &m_cube_vao);
    }

    for (Texture* i : m_texture_list)
    {
        glDeleteTextures(1, &i->id);
        m_texture_paths.remove(i->path.C_Str());
        delete i;
        i = nullptr;
    }
    m_texture_list.clear();

    for (CubeMap* i : m_cube_list)
    {
        glDeleteTextures(1, &i->m_texture);
        m_cubemap_paths.remove(i->m_folder_path);
        delete i;
        i = nullptr;
    }
    m_cube_list.clear();
}

bool MappingManager::ReadTexture2DDirectly(const char *path, GLenum target, bool gamma)
{
    GLint format, sFormat;
    int width, height, channels;
    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);

    if (!data) return false;

    if (gamma)
    {
        switch (channels)
        {
        case 1:
	        sFormat = format = GL_RED;
	        break;
        case 3:
	        format = GL_RGB;
	        sFormat = GL_SRGB;
	        break;
        case 4:
	        format = GL_RGBA;
	        sFormat = GL_SRGB_ALPHA;
	        break;
        default:
	        return false;
        }   
    }
    else
    {
        switch (channels)
        {
        case 1:
	        sFormat = format = GL_RED;
	        break;
        case 3:
	        sFormat = format = GL_RGB;
	        break;
        case 4:
	        sFormat = format = GL_RGBA;
	        break;
        default:
	        return false;
        }
    }

    glTexImage2D(target, 0, sFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    return true;
}

bool MappingManager::CreateTexture2D(const char* path, GLenum target, bool gamma)
{
    bool read = true;
    for (std::string& i : m_texture_paths)
    {
        if (!strcmp(path, i.data()))
        {
            read = false;
            break;
        }
    }

    if (read)
    {
        GLint format, sFormat;
        int width, height, channels;
        unsigned char* data = stbi_load(path, &width, &height, &channels, 0);

        if (!data) return false;

        if (gamma)
        {
            switch (channels)
            {
            case 1:
	            sFormat = format = GL_RED;
	            break;
            case 3:
	            format = GL_RGB;
	            sFormat = GL_SRGB;
	            break;
            case 4:
	            format = GL_RGBA;
	            sFormat = GL_SRGB_ALPHA;
	            break;
            default:
	            return false;
            }   
        }
        else
        {
            switch (channels)
            {
            case 1:
	            sFormat = format = GL_RED;
	            break;
            case 3:
	            sFormat = format = GL_RGB;
	            break;
            case 4:
	            sFormat = format = GL_RGBA;
	            break;
            default:
	            return false;
            }
        }

        glTexImage2D(target, 0, sFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);

        m_texture_paths.push_back(path);

        return true;
    }
    else
    {
        return false;
    }
}



CubeMap* MappingManager::CreateCubeMap(const char *folder_path, bool is_jpg, bool gamma)
{
    CubeMap* ptr = new CubeMap;

    bool read = true;

    for (std::string& i : m_cubemap_paths)
    {
        if (!strcmp(folder_path, i.data()))
        {
            read = false;
            break;
        }
    }

    if (!m_cube_data_created)
    {
        m_cube_data_created = true;

        glGenVertexArrays(1, &m_cube_vao);
        glGenBuffers(1, &m_cube_vbo);
        glBindVertexArray(m_cube_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_cube_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), &CubeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    }

    ptr->VAO = m_cube_vao;
    ptr->VBO = m_cube_vbo;
    
    if (read)
    {
        m_cubemap_paths.push_back(folder_path);

        glGenTextures(1, &ptr->m_texture);
        glBindTexture(GL_TEXTURE_CUBE_MAP, ptr->m_texture);

        for (unsigned int i = 0; i < 6; i++)
        {
            if (is_jpg)
            {
                ReadTexture2DDirectly((std::string(folder_path) + Faces_JPG[i]).data(), GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, gamma);
            }
            else
            {
                ReadTexture2DDirectly((std::string(folder_path) + Faces_PNG[i]).data(), GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, gamma);
            }
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        }
    }

    return ptr;
}

void MappingManager::DeleteTexture2D(Texture* ptr)
{
    if (!ptr) return;

    m_texture_paths.remove(ptr->path.C_Str());
    m_texture_list.remove(ptr);

    delete ptr;
    ptr = nullptr;
}

void MappingManager::DeleteCubeMap(CubeMap *ptr)
{
    if (!ptr) return;

    m_cubemap_paths.remove(ptr->m_folder_path);
    m_cube_list.remove(ptr);

    delete ptr;
    ptr = nullptr;
}