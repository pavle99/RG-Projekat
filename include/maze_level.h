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
#include "plane_renderer.h"
#include "plane.h"


class MazeLevel
{
public:
    //stores walls
    std::vector<Cube> Cubes;
    //stores floors
    std::vector<Plane> Planes;
    //position for goal
    glm::vec3 GoalPos;
    //position needed for rendering hero model
    glm::vec3 HeroPos;
    //hero rotation
    float HeroRotation;
    //light positions
    std::vector<glm::vec3> Lights;
    //size of each cube
    float CubeSize;

    MazeLevel()
    {}

    //load from file and initializes the
    void Load(const char *file);

    void Draw(CubeRenderer &cube_renderer, PlaneRenderer &plane_renderer);

    bool Move(int direction);

    bool IsComplete();

    void update();

private:
    std::vector<std::vector<unsigned int>> mazeMap;
    //Don't need endPointMap, there's only one end point.
    //std::vector<std::vector<unsigned int>> endPointMap;
    //hero coordinates
    unsigned int heroX;
    unsigned int heroY;
    //maze dimensions
    unsigned int mapX;
    unsigned int mapY;
    //initializing the level's structure
    void init();

};


#endif //PROJECT_BASE_MAZE_LEVEL_H
