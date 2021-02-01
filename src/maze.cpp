#include "maze.h"

RendererSkyBox *skybox_renderer;
CubeRenderer *cube_renderer;
PlaneRenderer *plane_renderer;

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
                                "cube");

    ResourceManager::LoadShader("resources/shaders/vertex_shader.vs",
                                "resources/shaders/fragment_shader_plane.fs",
                                "plane");

    ResourceManager::LoadShader("resources/shaders/vertex_shader_skybox.vs",
                                "resources/shaders/fragment_shader_skybox.fs",
                                "skybox");

    //create render objects
    skybox_renderer = new RendererSkyBox(ResourceManager::GetShader("skybox"), this->camera);
    cube_renderer = new CubeRenderer(ResourceManager::GetShader("cube"), this->camera);
    plane_renderer = new PlaneRenderer(ResourceManager::GetShader("plane"), this->camera);

    //load textures
    ResourceManager::LoadTexture("resources/textures/wall.jpg", false, "wall");
    ResourceManager::LoadTexture("resources/textures/wall.jpg", false, "wallspec");
    ResourceManager::LoadTexture("resources/textures/floor.jpg", false, "floor");
    ResourceManager::LoadTexture("resources/textures/floor.jpg", false, "floorspec");
    ResourceManager::LoadTexture("resources/textures/goal.png", true, "goal");
    ResourceManager::LoadTexture("resources/textures/goal.png", true, "goalspec");

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
    skybox_renderer->set_cube_map_texture_id(skyBoxID);

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

void Maze::ProcessScroll(float yoffset){
    this->camera.ProcessMouseScroll(yoffset);
}

void Maze::Draw(){

    if(Levels[currentLevel].IsComplete() && currentLevel + 1 < Levels.size())
        currentLevel++;

    Levels[currentLevel].Draw(*cube_renderer, *plane_renderer);

    //Drawing the goal from the outside
    cube_renderer->Draw(Levels[currentLevel].Lights, ResourceManager::GetTexture("goal"),
                        ResourceManager::GetTexture("goalspec"),Levels[currentLevel].GoalPos,
                        glm::vec3(Levels[currentLevel].CubeSize), 0.0f,
                        glm::vec3(0.0f, 1.0f, 0.0f), true);

    //current solution until we get a model for our hero
    //TODO GET HERO MODEL
    cube_renderer->Draw(Levels[currentLevel].Lights, ResourceManager::GetTexture("goal"),
                        ResourceManager::GetTexture("goalspec"),Levels[currentLevel].HeroPos,
                        glm::vec3(Levels[currentLevel].CubeSize), Levels[currentLevel].HeroRotation);
    //FIXME SKYBOX NOT RENDERING PROPERLY
    skybox_renderer->Draw();
}