#include "cube.h"

Cube::Cube()
        : Position(0.0f),
          Size(0.0f),
          Color(1.0f),
          alpha(false),
          diffuse(),
          specular()
{}

Cube::Cube(glm::vec3 pos, glm::vec3 size, Texture2D diffuse, Texture2D specular, glm::vec3 color, bool alpha)
        : Position(pos),
          Size(size),
          Color(color),
          alpha(alpha),
          diffuse(diffuse),
          specular(specular)
{}

void Cube::Draw(CubeRenderer &renderer, std::vector<glm::vec3> &lightPositions)
{
    renderer.Draw(lightPositions, diffuse, specular, Position, Size, 0.0f, Color, alpha);
}


