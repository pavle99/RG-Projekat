#include "plane_renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/camera.h>
#include <iostream>


PlaneRenderer::PlaneRenderer(Shader shader, Camera& cam)
        :camera(cam)
{
    this->shader = shader;
    this->init();
}

PlaneRenderer::~PlaneRenderer() {}


void PlaneRenderer::init() {
    //square vertices (positions, normals, tex coords)
    float vertices[] = {
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f
    };

    unsigned int VBO;

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void PlaneRenderer::Draw(std::vector<glm::vec3> pointLightPositions, Texture2D diffuse, Texture2D specular,
                        glm::vec3 position, glm::vec3 size, float rotation, glm::vec3 color, bool alpha) {
    glActiveTexture(GL_TEXTURE0);
    diffuse.Bind();

    glActiveTexture(GL_TEXTURE1);
    specular.Bind();

    this->shader.use();
    if(alpha) //current setting for transparency of the goal cube, TODO possible new non-cube goal model?
        this->shader.setFloat("alfa", 0.7);
    else
        this->shader.setFloat("alfa", 1.0);

    this->shader.setVec3("viewPos", this->camera.Position);
    this->shader.setFloat("material.shininess", 32.0f);
    this->shader.setInt("number_of_lights", (int)pointLightPositions.size());
    this->shader.setVec3("defaultColor", color);

    for(unsigned int i = 0; i < pointLightPositions.size(); i++)
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

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    projection = glm::perspective(glm::radians(this->camera.Zoom), 800.0f/600.0f , 0.1f, 100.0f);
    this->shader.setMat4("projection", projection);

    view = this->camera.GetViewMatrix();
    this->shader.setMat4("view", view);

    model = glm::translate(model , position);
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, size);
    this->shader.setMat4("model", model);

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}
