#ifndef PROJECT_BASE_PLANE_H
#define PROJECT_BASE_PLANE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "texture.h"
#include "plane_renderer.h"

class Plane
{
public:
    glm::vec3 Position, Size, Color;
    bool alpha;
    Texture2D diffuse;
    Texture2D specular;

    Plane();

    Plane(glm::vec3 pos, glm::vec3 size, Texture2D diffuse, Texture2D specular, glm::vec3 color = glm::vec3(1.0f),
          bool alpha = false);

    virtual void Draw(PlaneRenderer &renderer, std::vector<glm::vec3> &lightPositions);
};

#endif //PROJECT_BASE_PLANE_H
