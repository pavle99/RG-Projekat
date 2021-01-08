#include "model_renderer_hero.h"
#include "learnopengl/shader_m.h"


ModelRendererHero::ModelRendererHero(Shader shader, Camera &camera)
:camera(camera)
{
    this->shader = shader;
}

ModelRendererHero::~ModelRendererHero(){}

void ModelRendererHero::Draw(Model model, glm::vec3 position, glm::vec3 size, glm::vec3 rotation, float angle) {
    this->shader.use();

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f/600.0f, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    this->shader.setMat4("projection", projection);
    this->shader.setMat4("view", view);

    // render the loaded model
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), rotation);
    modelMatrix = glm::scale(modelMatrix, size);
    this->shader.setMat4("model", modelMatrix);
    model.Draw(this->shader);
}
