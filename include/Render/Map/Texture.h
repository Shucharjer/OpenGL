#include "glad/glad.h"
#include "string"
#include "assimp/types.h"

struct Texture
{
    GLuint id;
    std::string type;
    aiString path;
};
