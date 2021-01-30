#ifndef PROJECT_BASE_RENDERERSKYBOX_H
#define PROJECT_BASE_RENDERERSKYBOX_H

#include <learnopengl/camera.h>

#include <learnopengl/shader_m.h>

class RendererSkyBox {
public:
    RendererSkyBox(Shader shader, Camera &cam);
    ~RendererSkyBox();

    void set_cube_map_texture_id(unsigned int cubeMapTextureId);

    void Draw();
private:
    Shader shader;
    Camera &camera;
    unsigned int cube_map_texture_id;

    unsigned int skyboxVAO;
    void init_data();
};

#endif //PROJECT_BASE_RENDERERSKYBOX_H
