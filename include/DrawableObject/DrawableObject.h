#include "glm/glm.hpp"

class DrawableObject
{


    public:

    DrawableObject();
    ~DrawableObject();
    glm::mat4 GetModelMatrix() const;
};
