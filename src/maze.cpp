#include "maze.h"

RendererSkyBox *skybox_renderer;
CubeRenderer *cube_renderer;
PlaneRenderer *plane_renderer;
ModelRendererHero *model_renderer;
WhiteBoxRenderer *white_box_renderer;

Maze::Maze(unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;
    this->camera.Position = glm::vec3(35.0f, 22.0f, 15.0f);
    this->currentLevel = 0;
}

void Maze::init()
{

    //load shaders
    ResourceManager::LoadShader("resources/shaders/vertex_shader.vs",
                                "resources/shaders/fragment_shader_box.fs",
                                "cube");

    ResourceManager::LoadShader("resources/shaders/vertex_shader.vs",
                                "resources/shaders/fragment_shader_plane.fs",
                                "plane");

    ResourceManager::LoadShader("resources/shaders/vertex_shader_skybox.vs",
                                "resources/shaders/fragment_shader_skybox.fs",
                                "skybox");

    ResourceManager::LoadShader("resources/shaders/vertex_shader.vs",
                                "resources/shaders/fragment_shader_model.fs",
                                "model");

    ResourceManager::LoadShader("resources/shaders/vertex_shader.vs",
                                "resources/shaders/fragment_shader_white_box.fs",
                                "white_box");

    //create render objects
    skybox_renderer = new RendererSkyBox(ResourceManager::GetShader("skybox"), this->camera);
    cube_renderer = new CubeRenderer(ResourceManager::GetShader("cube"), this->camera);
    plane_renderer = new PlaneRenderer(ResourceManager::GetShader("plane"), this->camera);
    model_renderer = new ModelRendererHero(ResourceManager::GetShader("model"), this->camera);
    white_box_renderer = new WhiteBoxRenderer(ResourceManager::GetShader("white_box"), this->camera);

    //load textures
    ResourceManager::LoadTexture("resources/textures/wall.jpg", false, "wall");
    ResourceManager::LoadTexture("resources/textures/wall.jpg", false, "wallspec");
    ResourceManager::LoadTexture("resources/textures/floor.jpg", false, "floor");
    ResourceManager::LoadTexture("resources/textures/floor.jpg", false, "floorspec");
    ResourceManager::LoadTexture("resources/textures/goal.png", true, "goal");
    ResourceManager::LoadTexture("resources/textures/goal.png", true, "goalspec");

    //load models
    ResourceManager::LoadModel("resources/objects/hero/hero_obj_mtl/cartoon_hunter male.obj", "hero");


    // +X (right)
    // -X (left)
    // +Y (top)
    // -Y (bottom)
    // +Z (front)
    // -Z (back)


    std::vector<std::string> faces
            {
                    "resources/textures/Yokohama2/negx.jpg",
                    "resources/textures/Yokohama2/posx.jpg",
                    "resources/textures/Yokohama2/posy.jpg",
                    "resources/textures/Yokohama2/negy.jpg",
                    "resources/textures/Yokohama2/posz.jpg",
                    "resources/textures/Yokohama2/negz.jpg",
            };

    //load cubemap
    unsigned int skyBoxID = ResourceManager::loadCubemap(faces);
    skybox_renderer->set_cube_map_texture_id(skyBoxID);

    MazeLevel first, second, third;

//    first.Load("resources/levels/1.txt");
//    second.Load("resources/levels/2.txt");
//    third.Load("resources/levels/3.txt");

    this->FilePaths.emplace_back("resources/levels/1.txt");
    this->FilePaths.emplace_back("resources/levels/2.txt");
    this->FilePaths.emplace_back("resources/levels/3.txt");

    this->Levels.push_back(first);
    this->Levels.push_back(second);
    this->Levels.push_back(third);

    for(size_t i = 0; i < this->Levels.size(); i++)
        this->Levels[i].Load(this->FilePaths[i].c_str());

}

//moving the hero
void Maze::Move(int direction)
{

    Levels[currentLevel].Move(direction);

    if (Levels[currentLevel].IsComplete() && currentLevel + 1 < (int) Levels.size())
        currentLevel++;

}

//reloading current level
void Maze::Reload(){
    Levels[currentLevel].Load(FilePaths[currentLevel].c_str());

}


//camera movement
void Maze::ProcessInput(float delta_time, Camera_Movement direction)
{
    this->camera.ProcessKeyboard(direction, delta_time);
}

void Maze::ProcessMouseMovement(float xoffset, float yoffset)
{
    this->camera.ProcessMouseMovement(xoffset, yoffset);
}

void Maze::ProcessScroll(float yoffset)
{
    this->camera.ProcessMouseScroll(yoffset);
}

void Maze::Draw()
{

    if (Levels[currentLevel].IsComplete() && currentLevel + 1 < (int) Levels.size())
        currentLevel++;

    //Drawing the map of the level
    Levels[currentLevel].Draw(*cube_renderer, *plane_renderer);


    //Drawing the goal
    cube_renderer->Draw(Levels[currentLevel].Lights, ResourceManager::GetTexture("goal"),
                        ResourceManager::GetTexture("goalspec"), Levels[currentLevel].GoalPos,
                        glm::vec3(Levels[currentLevel].CubeSize / 2), (float) glfwGetTime() * 15,
                        glm::vec3(1.0f), true);

    //Drawing the hero model
    model_renderer->Draw(ResourceManager::GetModel("hero"), Levels[currentLevel].Lights,
                         Levels[currentLevel].HeroPos - glm::vec3(0.0f, 0.45*Levels[currentLevel].CubeSize, 0.0f),
                         glm::vec3(Levels[currentLevel].CubeSize / 25.0),glm::vec3(0.0f, 1.0f, 0.0f),
                         Levels[currentLevel].HeroRotation);

    //Drawing light sources
    for (glm::vec3 lightPos : Levels[currentLevel].Lights)
        white_box_renderer->Draw(lightPos);

    skybox_renderer->Draw();
}