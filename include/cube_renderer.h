
#ifndef PROJECT_BASE_CUBE_RENDERER_H
#define PROJECT_BASE_CUBE_RENDERER_H

#include "texture.h"
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

//class that renders all things cube-shaped
class CubeRenderer {
public:
    CubeRenderer(Shader shader, Camera& camera);
    ~CubeRenderer();

    void Draw(std::vector<glm::vec3> &pointLightPositions, Texture2D diffuse, Texture2D specular, glm::vec3 position,
              glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f), float rotate = 0.0f,
              glm::vec3 color = glm::vec3(1.0f), bool alpha = false);

private:
    Shader  shader;
    Camera &camera;
    //unsigned int VAO;
    unsigned int VAO[6];

    void init();
};


#endif //PROJECT_BASE_BOX_RENDERER_H
