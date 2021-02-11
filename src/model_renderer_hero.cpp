#include "model_renderer_hero.h"


ModelRendererHero::ModelRendererHero(Shader shader, Camera &camera)
        : camera(camera)
{
    this->shader = shader;
}

ModelRendererHero::~ModelRendererHero()
{}

void
ModelRendererHero::Draw(Model model, std::vector<glm::vec3> &pointLightPositions, glm::vec3 position, glm::vec3 size,
                        glm::vec3 rotation, float angle)
{
    this->shader.use();

    this->shader.setFloat("material.shininess", 32.0f);
    this->shader.setInt("number_of_lights", (int) pointLightPositions.size());

    for (unsigned int i = 0; i < pointLightPositions.size(); i++)
    {
        std::string tmp = "pointLights[" + std::to_string(i) + "]";

        this->shader.setVec3((tmp + ".position"), pointLightPositions[i]);
        this->shader.setVec3((tmp + ".diffuse"), 0.8f, 0.8f, 0.8f);
        this->shader.setVec3((tmp + ".specular"), 1.0f, 1.0f, 1.0f);
        this->shader.setVec3((tmp + ".ambient"), 0.07f, 0.07f, 0.07f);
        this->shader.setFloat((tmp + ".constant"), 1.0f);
        this->shader.setFloat((tmp + ".linear"), 0.09);
        this->shader.setFloat((tmp + ".quadratic"), 0.032);
    }

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
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
