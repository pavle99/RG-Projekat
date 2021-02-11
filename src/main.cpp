#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include "resource_manager.h"
#include "maze.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xPos, double yPos);

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset);

void processInput(GLFWwindow *window);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//struct PointLight
//{
//    glm::vec3 position;
//    glm::vec3 ambient;
//    glm::vec3 diffuse;
//    glm::vec3 specular;
//
//    float constant;
//    float linear;
//    float quadratic;
//};

//struct ProgramState
//{
//    glm::vec3 clearColor = glm::vec3(0);
//    bool ImGuiEnabled = false;
//    Camera camera;
//    bool CameraMouseMovementUpdateEnabled = true;
//    glm::vec3 backpackPosition = glm::vec3(0.0f);
//    float backpackScale = 1.0f;
//    PointLight pointLight;
//
//    ProgramState()
//            : camera(glm::vec3(-7.0f, 10.0f, 46.0f))
//    {}
//
//    void SaveToFile(std::string filename);
//
//    void LoadFromFile(std::string filename);
//};

//void ProgramState::SaveToFile(std::string filename)
//{
//    std::ofstream out(filename);
//    out << clearColor.r << '\n'
//        << clearColor.g << '\n'
//        << clearColor.b << '\n'
//        << ImGuiEnabled << '\n'
//        << camera.Position.x << '\n'
//        << camera.Position.y << '\n'
//        << camera.Position.z << '\n'
//        << camera.Front.x << '\n'
//        << camera.Front.y << '\n'
//        << camera.Front.z << '\n';
//}
//
//void ProgramState::LoadFromFile(std::string filename)
//{
//    std::ifstream in(filename);
//    if (in)
//    {
//        in >> clearColor.r
//           >> clearColor.g
//           >> clearColor.b
//           >> ImGuiEnabled
//           >> camera.Position.x
//           >> camera.Position.y
//           >> camera.Position.z
//           >> camera.Front.x
//           >> camera.Front.y
//           >> camera.Front.z;
//    }
//}

//ProgramState *programState;

bool cameraUnlocked = true;

Maze maze(800, 600);

//void DrawImGui(ProgramState *programState);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Maze", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

//    programState = new ProgramState;
//    programState->LoadFromFile("resources/program_state.txt");
//    if (programState->ImGuiEnabled)
//    {
//        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//    }
//    // Init Imgui
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO &io = ImGui::GetIO();
//    (void) io;


//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//    ImGui_ImplOpenGL3_Init("#version 330 core");

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //initialize maze
    maze.init();

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = (currentFrame - lastFrame) * 5;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);


        // render
        // ------
//        glClearColor(programState->clearColor.r, programState->clearColor.g, programState->clearColor.b, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        maze.Draw();

//        if (programState->ImGuiEnabled)
//            DrawImGui(programState);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //clearing all the resources
    ResourceManager::Clear();

//    programState->SaveToFile("resources/program_state.txt");
//    delete programState;
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------

//
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float sens = 0.5;
    if(cameraUnlocked)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            maze.ProcessInput(sens * deltaTime, FORWARD);

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            maze.ProcessInput(sens * deltaTime, BACKWARD);

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            maze.ProcessInput(sens * deltaTime, LEFT);

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            maze.ProcessInput(sens * deltaTime, RIGHT);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xPos, double yPos)
{
    if(cameraUnlocked)
    {
        if (firstMouse) {
            lastX = (float) xPos;
            lastY = (float) yPos;
            firstMouse = false;
        }

        float xOffset = (float) xPos - lastX;
        float yOffset = lastY - (float) yPos; // reversed since y-coordinates go from bottom to top

        lastX = (float) xPos;
        lastY = (float) yPos;

        float sens = 0.5;

        maze.ProcessMouseMovement(sens * xOffset, sens * yOffset);
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
{
    if(cameraUnlocked)
    {
        maze.ProcessScroll((float) yOffset);
    }
}

//void DrawImGui(ProgramState *programState)
//{
//    ImGui_ImplOpenGL3_NewFrame();
//    ImGui_ImplGlfw_NewFrame();
//    ImGui::NewFrame();
//
//    {
//        static float f = 0.0f;
//        ImGui::Begin("Hello window");
//        ImGui::Text("Hello text");
//        ImGui::SliderFloat("Float slider", &f, 0.0, 1.0);
//        ImGui::ColorEdit3("Background color", (float *) &programState->clearColor);
//        ImGui::DragFloat3("Backpack position", (float *) &programState->backpackPosition);
//        ImGui::DragFloat("Backpack scale", &programState->backpackScale, 0.05, 0.1, 4.0);
//
//        ImGui::DragFloat("pointLight.constant", &programState->pointLight.constant, 0.05, 0.0, 1.0);
//        ImGui::DragFloat("pointLight.linear", &programState->pointLight.linear, 0.05, 0.0, 1.0);
//        ImGui::DragFloat("pointLight.quadratic", &programState->pointLight.quadratic, 0.05, 0.0, 1.0);
//        ImGui::End();
//    }
//
//    {
//        ImGui::Begin("Camera info");
//        const Camera &c = programState->camera;
//        ImGui::Text("Camera position: (%f, %f, %f)", c.Position.x, c.Position.y, c.Position.z);
//        ImGui::Text("(Yaw, Pitch): (%f, %f)", c.Yaw, c.Pitch);
//        ImGui::Text("Camera front: (%f, %f, %f)", c.Front.x, c.Front.y, c.Front.z);
//        ImGui::Checkbox("Camera mouse update", &programState->CameraMouseMovementUpdateEnabled);
//        ImGui::End();
//    }
//
//    ImGui::Render();
//    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
//    if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
//    {
//        programState->ImGuiEnabled = !programState->ImGuiEnabled;
//        if (programState->ImGuiEnabled)
//        {
//            programState->CameraMouseMovementUpdateEnabled = false;
//            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//        } else
//        {
//            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//        }
//    }
    if ((key == GLFW_KEY_UP || key == GLFW_KEY_LEFT || key == GLFW_KEY_DOWN || key == GLFW_KEY_RIGHT) &&
        action == GLFW_PRESS)
    {
        maze.Move(key);
    }

    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        cameraUnlocked = !cameraUnlocked;
    }

    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        maze.Reload();
    }
}