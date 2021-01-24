#include "maze.h"

RendererSkyBox *SkyBoxRenderer;

Maze::Maze(unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;
    this->camera.Position = glm::vec3(3.0f, 12.0f, -8.0f);
}

void Maze::init()
{
    //load shaders
    ResourceManager::LoadShader(FileSystem::getPath("resources/shaders/vertex_shader.vs").c_str(),
                                FileSystem::getPath("resources/shaders/fragment_shader.fs").c_str(),
                                nullptr,
                                "sprite");
    ResourceManager::LoadShader(FileSystem::getPath("resources/shaders/vertex_shader.vs").c_str(),
                                FileSystem::getPath("resources/shaders/fragment_shader_box.fs").c_str(),
                                nullptr,
                                "sprite");

    //load textures

    // +X (right)
    // -X (left)
    // +Y (top)
    // -Y (bottom)
    // +Z (front)
    // -Z (back)

    std::vector<std::string> faces
            {
                    FileSystem::getPath("resources/textures/skybox/Yokohama2/posx.jpg"),
                    FileSystem::getPath("resources/textures/skybox/Yokohama2/negx.jpg"),
                    FileSystem::getPath("resources/textures/skybox/Yokohama2/posy.jpg"),
                    FileSystem::getPath("resources/textures/skybox/Yokohama2/negy.jpg"),
                    FileSystem::getPath("resources/textures/skybox/Yokohama2/posz.jpg"),
                    FileSystem::getPath("resources/textures/skybox/Yokohama2/negz.jpg"),
            };

    unsigned int skyBoxID = ResourceManager::loadCubemap(faces);
    SkyBoxRenderer->set_cube_map_texture_id(skyBoxID);

}
