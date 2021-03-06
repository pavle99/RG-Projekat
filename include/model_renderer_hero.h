
#ifndef PROJECT_BASE_MODEL_RENDERER_HERO_H
#define PROJECT_BASE_MODEL_RENDERER_HERO_H

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

class ModelRendererHero
{
public:
    ModelRendererHero(Shader shader, Camera &camera);

    ~ModelRendererHero();

    void Draw(Model model, std::vector<glm::vec3> &pointLightPositions, glm::vec3 position, glm::vec3 size,
              glm::vec3 rotation, float angle);

private:
    Shader shader;
    Camera &camera;
};

#endif //PROJECT_BASE_MODEL_RENDERER_HERO_H
