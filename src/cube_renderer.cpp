#include <glm/gtc/matrix_transform.hpp>
#include <learnopengl/camera.h>
#include "cube_renderer.h"
#include <iostream>
#include <utility>
#include <algorithm>


CubeRenderer::CubeRenderer(Shader shader, Camera &cam)
        : camera(cam)
{
    this->shader = shader;
    this->init();
}

CubeRenderer::~CubeRenderer()
{}


void CubeRenderer::init()
{
    //cube vertices (positions, normals, tex coords)
//    float vertices[] = {
//            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
//            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
//
//            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
//            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//
//            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//
//            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
//            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//
//            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
//            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
//            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
//            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f
//    };

    float vertices[6][48] = {
            {
                    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,
                    0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f,
                    0.5f,  -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 0.0f,
                    0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 1.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 0.0f,
                    -0.5f, 0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, 0.0f, 1.0f
            },
            {
                    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
                    0.5f,  -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
                    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
                    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
                    -0.5f, 0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
                    -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f
            },
            {
                    -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 1.0f,
                    -0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f,
                    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  0.0f, 0.0f,
                    -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 0.0f,
                    -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  1.0f, 1.0f
            },
            {
                    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
                    0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
                    0.5f,  0.5f,  -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
                    0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
                    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
                    0.5f,  -0.5f, 0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f
            },
            {
                    -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f,
                    0.5f,  -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  1.0f, 1.0f,
                    0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f,
                    0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  1.0f, 0.0f,
                    -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  0.0f, 0.0f,
                    -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.0f, 1.0f
            },
            {
                    -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
                    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
                    0.5f,  0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
                    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
                    -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
                    -0.5f, 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f
            }
    };

    for (int i = 0; i < 6; i++)
    {
        unsigned int VBO;

        glGenVertexArrays(1, &this->VAO[i]);
        glGenBuffers(1, &VBO);

        glBindVertexArray(this->VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[i]), vertices[i], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

//    unsigned int VBO;
//
//    glGenVertexArrays(1, &this->VAO);
//    glGenBuffers(1, &VBO);
//
//    glBindVertexArray(this->VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
}

void CubeRenderer::Draw(std::vector<glm::vec3> &pointLightPositions, Texture2D diffuse, Texture2D specular,
                        glm::vec3 position, glm::vec3 size, float rotation, glm::vec3 color, bool alpha)
{
    glActiveTexture(GL_TEXTURE0);
    diffuse.Bind();

    glActiveTexture(GL_TEXTURE1);
    specular.Bind();

    this->shader.use();
    if (alpha) //current setting for transparency of the goal cube
        this->shader.setFloat("alfa", 0.7);
    else
        this->shader.setFloat("alfa", 1.0);

    this->shader.setVec3("viewPos", this->camera.Position);
    this->shader.setFloat("material.shininess", 32.0f);
    this->shader.setInt("number_of_lights", (int) pointLightPositions.size());
    this->shader.setVec3("defaultColor", color);

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

    this->shader.setVec3("sunLight.direction", -1.0f, -1.0f, 0.0f);
    this->shader.setVec3("sunLight.diffuse", 0.2f, 0.2f, 0.2f);
    this->shader.setVec3("sunLight.specular", 0.4f, 0.4f, 0.4f);
    this->shader.setVec3("sunLight.ambient", 0.03f, 0.03f, 0.03f);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    projection = glm::perspective(glm::radians(this->camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
    this->shader.setMat4("projection", projection);

    view = this->camera.GetViewMatrix();
    this->shader.setMat4("view", view);

    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, size);
    this->shader.setMat4("model", model);


    if (alpha)
    {
        std::vector<std::pair<glm::vec4, int>> faces //center of each cube face
                {
                        std::make_pair(model * glm::vec4(0.0f, 0.0f, -0.5f, 1.0f), 0),
                        std::make_pair(model * glm::vec4(0.0f, 0.0f, 0.5f, 1.0f), 1),
                        std::make_pair(model * glm::vec4(-0.5f, 0.0f, 0.0f, 1.0f), 2),
                        std::make_pair(model * glm::vec4(0.5f, 0.0f, 0.0f, 1.0f), 3),
                        std::make_pair(model * glm::vec4(0.0f, -0.5f, 0.0f, 1.0f), 4),
                        std::make_pair(model * glm::vec4(0.0f, 0.5f, 0.0f, 1.0f), 5)
                };

        std::sort(faces.begin(), faces.end(),
                  [cameraPosition = this->camera.Position]
                          (const std::pair<glm::vec4, int> a, const std::pair<glm::vec4, int> b)
                  {
                      glm::vec3 aPos = glm::vec3(a.first);
                      glm::vec3 bPos = glm::vec3(b.first);

                      float d1 = glm::distance(cameraPosition, aPos);
                      float d2 = glm::distance(cameraPosition, bPos);

                      return d1 > d2;
                  });

        for (int i = 0; i < 6; i++)
        {
            glBindVertexArray(this->VAO[faces[i].second]);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    } else
        for (unsigned int i : this->VAO)
        {
            glBindVertexArray(i);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }


//    glBindVertexArray(this->VAO);
//    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}
