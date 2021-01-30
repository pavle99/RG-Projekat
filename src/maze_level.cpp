#include <maze_level.h>

enum {
    WALL = 9,
    GOAL = 7,
    HERO_ON_GOAL = 5,
    HERO = 3,
    FLOOR = 1,
    AIR = 0
};

void MazeLevel::Load(const char *file){
    std::ifstream mapFile(file);

    if(mapFile){
        mapFile >> mapX >> mapY;
        this->mazeMap.resize(mapX);
        for(unsigned int i = 0; i < mapX; i++){
            this->mazeMap[i].resize(mapY);
            for(unsigned int j = 0; j < mapY; j++){
                mapFile >> mazeMap[i][j];
            }
        }
        if(mapX > 0 && mapY > 0) //(if) is not needed if correct input (file)
            this->update();
    }

}

void MazeLevel::update(){
    Cubes.clear();
    Lights.clear();

    float cubeSize = 3;

    for(unsigned int i = 0; i < mapX; i++){
        for(unsigned int j = 0; j < mapY; j++){
            glm::vec3 pos = glm::vec3(((float)i)*cubeSize, 0.0f, ((float)j)*cubeSize);
            glm::vec3 size = glm::vec3(cubeSize);
            //loading all walls
            if(mazeMap[i][j] == WALL){
                Cube cube(pos, size, ResourceManager::GetTexture("wall"), ResourceManager::GetTexture("wallspec"));
                this->Cubes.push_back(cube);
            }
            //loading the goal object, HERO_ON_GOAL has both hero and goal on it, so both must be loaded
            if (mazeMap[i][j] == GOAL || mazeMap[i][j] == HERO_ON_GOAL){
                Cube cube(pos, size, ResourceManager::GetTexture("goal"), ResourceManager::GetTexture("goalspec"),
                          glm::vec3(0.0f, 1.0f, 0.0f), true);
                this->Cubes.push_back(cube);
            }
            //updating the hero position for later rendering of the model
            if(mazeMap[i][j] == HERO || mazeMap[i][j] == HERO_ON_GOAL){
                heroX = i;
                heroY = j;
                HeroPos = pos;
            }

            if(mazeMap[i][j] != AIR){//FLOOR
                pos -= glm::vec3(0.0f, cubeSize, 0.0f);
                Cube cube(pos, size, ResourceManager::GetTexture("floor"), ResourceManager::GetTexture("floorspec"));
                this->Cubes.push_back(cube);
            }


        }
    }
    this->Lights.emplace_back(cubeSize*((float)mapX)/2.0f, cubeSize*7.0f, cubeSize*((float)mapY)/2.0f);
}

bool MazeLevel::Move(int direction){
    int directionX = 0, directionY = 0;
    int newPosX = (int)heroX;
    int newPosY = (int)heroY;
    bool canMove = true;

    switch(direction){
        case GLFW_KEY_UP:
            directionY = 1;
            break;
        case GLFW_KEY_LEFT:
            directionX = 1;
            break;
        case GLFW_KEY_DOWN:
            directionY = -1;
            break;
        case GLFW_KEY_RIGHT:
            directionX = -1;
            break;
        default:
            break;
    }

    newPosX += directionX;
    newPosY += directionY;
    unsigned int newCube = mazeMap[newPosX][newPosY];

    //checking if the new square is out of bounds
    if(newPosX < 0 || (unsigned)newPosX >= mapX || newPosY < 0 || (unsigned)newPosY >= mapY)
        canMove = false;

    //checking if the hero is running into a wall or leaving the maze
    if(newCube == WALL || newCube == AIR)
        canMove = false;

    //updating the position of the hero and the position it has left (in mazeMap)
    //not checking if hero leaves goal by moving because the level should end as the hero reaches the goal
    //should the hero even be able to move after reaching the goal? (case: final level)
    if(canMove) {
        if (newCube == GOAL)
            mazeMap[newPosX][newPosY] = HERO_ON_GOAL;
        else
            mazeMap[newPosX][newPosY] = HERO;

        mazeMap[heroX][heroY] = FLOOR;
        heroX = newPosX;
        heroY = newPosY;
    }
    //updating all the changes
    this->update();

    return canMove;
}

bool MazeLevel::IsComplete(){
    for(unsigned int i = 0; i < mapX; i++){
        for(unsigned int j = 0; j < mapY; j++){
            if(mazeMap[i][j] == HERO_ON_GOAL)
                return true;
        }
    }
    return false;
}

void MazeLevel::Draw(CubeRenderer &renderer){
    for(Cube &cube : this->Cubes){
        cube.Draw(renderer, this->Lights);
    }
}


