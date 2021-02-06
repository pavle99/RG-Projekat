#ifndef PROJECT_BASE_WHITE_BOX_RENDERER_H
#define PROJECT_BASE_WHITE_BOX_RENDERER_H

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

//class that renders all things cube-shaped
class WhiteBoxRenderer {
public:
    WhiteBoxRenderer(Shader shader, Camera& camera);
    ~WhiteBoxRenderer();

    void Draw(glm::vec3 position, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f), float rotate = 0.0f,
              glm::vec3 color = glm::vec3(1.0f));

private:
    Shader  shader;
    Camera &camera;
    unsigned int VAO;

    void init();
};

#endif //PROJECT_BASE_WHITE_BOX_RENDERER_H
