
#ifndef PROJECT_BASE_CUBE_H
#define PROJECT_BASE_CUBE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "texture.h"
#include "cube_renderer.h"

class Cube {
public:
    glm::vec3 Position, Size, Color;
    bool alpha;
    Texture2D diffuse;
    Texture2D specular;
    Texture2D Sprite;

    Cube();
    Cube(glm::vec3 pos, glm::vec3 size, Texture2D diffuse, Texture2D specular,glm::vec3 color = glm::vec3(1.0f), bool alpha = false);
    Cube(glm::vec3 pos, glm::vec3 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));

    virtual void Draw(CubeRenderer &renderer, std::vector<glm::vec3> lightPositions);
};

#endif //PROJECT_BASE_CUBE_H
