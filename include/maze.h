#ifndef PROJECT_BASE_MAZE_H
#define PROJECT_BASE_MAZE_H

#include <vector>
#include "learnopengl/shader_m.h"
#include "resource_manager.h"
#include "maze_level.h"
#include "RendererSkyBox.h"
#include "model_renderer_hero.h"
#include "white_box_renderer.h"


class Maze
{
public:
    Maze(unsigned int width, unsigned int height);

    void init();

    void ProcessInput(float delta_time, Camera_Movement direction);

    void ProcessMouseMovement(float xoffset, float yoffset);

    void ProcessScroll(float yoffset);

    void Move(int direction);

    void Draw();

private:
    unsigned int width, height;
    Camera camera;
    std::vector<MazeLevel> Levels;
    int currentLevel;

};

#endif //PROJECT_BASE_MAZE_H
