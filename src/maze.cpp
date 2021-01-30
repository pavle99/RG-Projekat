#include "maze.h"

RendererSkyBox *SkyBoxRenderer;
CubeRenderer *Cube_renderer;

Maze::Maze(unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;
    this->camera.Position = glm::vec3(3.0f, 12.0f, -8.0f);
    this->currentLevel = 0;
}

void Maze::init()
{

    //load shaders
    ResourceManager::LoadShader("resources/shaders/vertex_shader.vs",
                                "resources/shaders/fragment_shader_box.fs",
                                "box");

    ResourceManager::LoadShader("resources/shaders/vertex_shader_skybox.vs",
                                "resources/shaders/fragment_shader_skybox.fs",
                                "skybox");

    ResourceManager::GetShader("box").setFloat("material.diffuse", 0.8);

    //create render objects
    SkyBoxRenderer = new RendererSkyBox(ResourceManager::GetShader("skybox"), this->camera);
    Cube_renderer = new CubeRenderer(ResourceManager::GetShader("box"), this->camera);

    //load textures
    //TODO GET TEXTURES FOR WALLS, FLOOR, AND GOAL
    ResourceManager::LoadTexture("resources/textures/container.jpg", false, "wall");
    ResourceManager::LoadTexture("resources/textures/container.jpg", false, "wallspec");
    ResourceManager::LoadTexture("resources/textures/container.jpg", false, "floor");
    ResourceManager::LoadTexture("resources/textures/container.jpg", false, "floorspec");
    ResourceManager::LoadTexture("resources/textures/awesomeface.png", true, "goal");
    ResourceManager::LoadTexture("resources/textures/awesomeface.png", true, "goalspec");

    // +X (right)
    // -X (left)
    // +Y (top)
    // -Y (bottom)
    // +Z (front)
    // -Z (back)


    std::vector<std::string> faces
            {
                    "resources/textures/Yokohama2/posx.jpg",
                    "resources/textures/Yokohama2/negx.jpg",
                    "resources/textures/Yokohama2/posy.jpg",
                    "resources/textures/Yokohama2/negy.jpg",
                    "resources/textures/Yokohama2/posz.jpg",
                    "resources/textures/Yokohama2/negz.jpg",
            };

    //load cubemap
    unsigned int skyBoxID = ResourceManager::loadCubemap(faces);
    SkyBoxRenderer->set_cube_map_texture_id(skyBoxID);

    MazeLevel first, second;

    first.Load("resources/levels/1.txt");
    second.Load("resources/levels/2.txt");

    this->Levels.push_back(first);
    this->Levels.push_back(second);

}
void Maze::Move(int direction) {
    //TODO HERO ORIENTATION

    Levels[currentLevel].Move(direction);

    if(Levels[currentLevel].IsComplete() && currentLevel + 1 < Levels.size())
        currentLevel++;

}
//camera movement
void Maze::ProcessInput(float delta_time, Camera_Movement direction)
{
    this->camera.ProcessKeyboard(direction, delta_time);
}

void Maze::ProcessMouseMovement(float xoffset,float yoffset){
    this->camera.ProcessMouseMovement(xoffset, yoffset);
}

void Maze::Draw(){
    Levels[currentLevel].update();

    if(Levels[currentLevel].IsComplete() && currentLevel + 1 < Levels.size())
        currentLevel++;

    Levels[currentLevel].Draw(*Cube_renderer);

    //current solution until we get a model for our hero
    //TODO GET HERO MODEL
    Cube_renderer->Draw(Levels[currentLevel].Lights, ResourceManager::GetTexture("goal"), ResourceManager::GetTexture("goalspec"),
                       Levels[currentLevel].HeroPos);
    //FIXME SKYBOX DOESNT WORK
    SkyBoxRenderer->Draw();
}