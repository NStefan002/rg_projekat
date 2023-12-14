#ifndef PROGRAMSTATE_H
#define PROGRAMSTATE_H

#include <rg/pointlight.hpp>
#include <rg/camera.hpp>
#include <glm/glm.hpp>

#include <string>

class ProgramState
{
  public:
    glm::vec3 backgroundColor = glm::vec3(0);
    bool imguiEnabled = false;
    Camera camera;
    bool cameraMouseMovementEnabled = true;
    PointLight pointLight;
    // objects positions
    glm::vec3 objectPosition = glm::vec3(0.f);
    float objectScale = 1.f;

    ProgramState() : camera(glm::vec3(0.f, 0.f, 3.f)) {}

    void saveToFile(std::string filename);
    void loadFromFile(std::string filename);
};

#endif
