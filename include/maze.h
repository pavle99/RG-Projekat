#ifndef PROJECT_BASE_MAZE_H
#define PROJECT_BASE_MAZE_H

#include "maze_level.h"
#include "RendererSkyBox.h"

//TODO this
class Maze
{
public:
    Maze(unsigned int width, unsigned int height);

    void init();

    void processInput(float delta_time);

private:
    unsigned int width, height;
    Camera camera;
    bool game_keys[1024];

};

#endif //PROJECT_BASE_MAZE_H
