
#ifndef PROJECT_BASE_MODEL_RENDERER_HERO_H
#define PROJECT_BASE_MODEL_RENDERER_HERO_H

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

//class that renders the character we control in the labyrinth, TODO better name?

class ModelRendererHero{
public:
    ModelRendererHero(Shader shader, Camera& camera);
    ~ModelRendererHero();

    void Draw(Model model, glm::vec3 position, glm::vec3 size, glm::vec3 rotation, float angle);
private:
    Shader shader;
    Camera& camera;
};

#endif //PROJECT_BASE_MODEL_RENDERER_HERO_H
