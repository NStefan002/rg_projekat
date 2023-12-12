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

#include <stb_image.h>

void framebuf_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void proccess_input(GLFWwindow *window);

const int WinWidth = 1200;
const int WinHeight = 900;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(WinWidth, WinHeight, "RG PROJEKAT", nullptr, nullptr);

    ASSERT(nullptr != window, "Failed to create window.");

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuf_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD.");
    stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    Shader shader("resources/shaders/vertex_shader.vs", "resources/shaders/fragment_shader.fs");

    while (!glfwWindowShouldClose(window))
    {
        // ...

        proccess_input(window);

        // ...

        glfwPollEvents();
    }

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
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
}

void proccess_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        // move forwards
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        // move backwards
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        // move left
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        // move right
    }
}
