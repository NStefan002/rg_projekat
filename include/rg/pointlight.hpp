#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#define POINTLIGHT_H
#include <glm/glm.hpp>

class PointLight
{
  public:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;

    PointLight() {}
};

#endif
