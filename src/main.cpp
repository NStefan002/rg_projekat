#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include <rg/error.hpp>

#include <glm/glm.hpp>

#include <rg/camera.hpp>
#include <rg/shader.hpp>
#include <rg/filesystem.hpp>
#include <rg/mesh.hpp>
#include <rg/model.hpp>
#include <rg/pointlight.hpp>
#include <rg/programstate.hpp>

#include <stb_image.h>

void framebuf_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void proccess_input(GLFWwindow *window);
void draw_imgui();

// window
const int WinWidth = 1200;
const int WinHeight = 900;

// camera
float lastX = WinWidth / 2.f;
float lastY = WinHeight / 2.f;
bool firstMouse = true;

// timing
float deltaTime = 0.f;
float lastFrame = 0.f;

ProgramState *programState;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WinWidth, WinHeight, "RG Project", nullptr, nullptr);

    ASSERT(nullptr != window, "Failed to create window.");

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuf_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD.");
    stbi_set_flip_vertically_on_load(true);

    programState = new ProgramState();
    programState->loadFromFile("resources/program_state.txt");
    if (programState->imguiEnabled)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    // Init Imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    glEnable(GL_DEPTH_TEST);

    Shader *shader = new Shader("resources/shaders/vertex_shader.vs", "resources/shaders/fragment_shader.fs");

    Model helicopter("resources/objects/ah64d/ah64d.obj");
    helicopter.SetShaderTextureNamePrefix("material.");

    PointLight &pointLight = programState->pointLight;
    pointLight.position = glm::vec3(4.0, 4.0, 0.0);
    pointLight.ambient = glm::vec3(0.1, 0.1, 0.1);
    pointLight.diffuse = glm::vec3(1.0, 1.0, 1.0);
    pointLight.specular = glm::vec3(1.0, 1.0, 1.0);

    pointLight.constant = 1.f;
    pointLight.linear = 0.09f;
    pointLight.quadratic = 0.032f;

    // draw in wireframe
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        proccess_input(window);

        glClearColor(programState->backgroundColor.r, programState->backgroundColor.g, programState->backgroundColor.b,
                     1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        // pointLight.position = glm::vec3(4.0 * cos(currentFrame), 4.0f, 4.0 * sin(currentFrame));
        shader->setVec3("pointLight.position", pointLight.position);
        shader->setVec3("pointLight.ambient", pointLight.ambient);
        shader->setVec3("pointLight.diffuse", pointLight.diffuse);
        shader->setVec3("pointLight.specular", pointLight.specular);
        shader->setFloat("pointLight.constant", pointLight.constant);
        shader->setFloat("pointLight.linear", pointLight.linear);
        shader->setFloat("pointLight.quadratic", pointLight.quadratic);
        shader->setVec3("viewPosition", programState->camera.Position);
        shader->setFloat("material.shininess", 32.f);
        glm::mat4 projection =
            glm::perspective(glm::radians(programState->camera.Zoom), (float)WinWidth / (float)WinHeight, 0.1f, 100.0f);
        glm::mat4 view = programState->camera.GetViewMatrix();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);

        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, programState->objectPosition);
        model = glm::scale(model, glm::vec3(programState->objectScale));
        shader->setMat4("model", model);
        helicopter.Draw(*shader);

        if (programState->imguiEnabled)
        {
            draw_imgui();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    programState->saveToFile("resources/program_state.txt");
    delete programState;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void framebuf_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // exit
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    // toggle imgui
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
    {
        programState->imguiEnabled = !programState->imguiEnabled;
        if (programState->imguiEnabled)
        {
            programState->cameraMouseMovementEnabled = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    if (programState->cameraMouseMovementEnabled)
    {
        programState->camera.ProcessMouseMovement(xoffset, yoffset);
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    programState->camera.ProcessMouseScroll(yoffset);
}

void proccess_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        // move forwards
        programState->camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        // move backwards
        programState->camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        // move left
        programState->camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        // move right
        programState->camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

void draw_imgui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
        static float f = 0.0f;
        ImGui::Begin("RG Project");
        ImGui::Text("Settings");
        ImGui::SliderFloat("Float slider", &f, 0.0, 1.0);
        ImGui::ColorEdit3("Background color", (float *)&programState->backgroundColor);
        ImGui::DragFloat3("Object position", (float *)&programState->objectPosition);
        ImGui::DragFloat("Object scale", &programState->objectScale, 0.05, 0.1, 4.0);

        ImGui::DragFloat("pointLight.constant", &programState->pointLight.constant, 0.05, 0.0, 1.0);
        ImGui::DragFloat("pointLight.linear", &programState->pointLight.linear, 0.05, 0.0, 1.0);
        ImGui::DragFloat("pointLight.quadratic", &programState->pointLight.quadratic, 0.05, 0.0, 1.0);
        ImGui::End();
    }

    {
        ImGui::Begin("Camera info");
        const Camera &c = programState->camera;
        ImGui::Text("Camera position: (%f, %f, %f)", c.Position.x, c.Position.y, c.Position.z);
        ImGui::Text("(Yaw, Pitch): (%f, %f)", c.Yaw, c.Pitch);
        ImGui::Text("Camera front: (%f, %f, %f)", c.Front.x, c.Front.y, c.Front.z);
        ImGui::Checkbox("Camera mouse update", &programState->cameraMouseMovementEnabled);
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
