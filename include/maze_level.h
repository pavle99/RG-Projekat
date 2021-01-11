#ifndef PROJECT_BASE_MAZE_LEVEL_H
#define PROJECT_BASE_MAZE_LEVEL_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "resource_manager.h"
#include "cube_renderer.h"
#include "cube.h"


class MazeLevel{
public:
    //stores walls, floors, and goal cube
    std::vector<Cube> Cubes;
    //position needed for rendering hero model
    glm::vec3 HeroPos;
    //light positions
    std::vector<glm::vec3> Lights;
    //glm::vec3 goalPos; //implement this way if we decide to load goal model

    MazeLevel() {}

    //load from file and initializes the
    void Load(const char *file);

    void Draw(CubeRenderer &renderer);

    bool Move(int direction);

    bool IsComplete();

    void update();
private:
    std::vector<std::vector<unsigned int>> mazeMap;
    //hero coordinates
    unsigned int heroX;
    unsigned int heroY;
    //maze dimensions
    unsigned int mapX;
    unsigned int mapY;
};





#endif //PROJECT_BASE_MAZE_LEVEL_H
