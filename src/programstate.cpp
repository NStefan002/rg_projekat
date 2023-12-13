#include <rg/programstate.hpp>
#include <iostream>
#include <fstream>

void ProgramState::saveToFile(std::string filename)
{
    std::ofstream output(filename);
    output << backgroundColor.r << '\n'
           << backgroundColor.g << '\n'
           << backgroundColor.b << '\n'
           << imguiEnabled << '\n'
           << camera.Position.x << '\n'
           << camera.Position.y << '\n'
           << camera.Position.z << '\n'
           << camera.Front.x << '\n'
           << camera.Front.y << '\n'
           << camera.Front.z << '\n';
}

void ProgramState::loadFromFile(std::string filename)
{
    std::ifstream input(filename);
    input >> backgroundColor.r
          >> backgroundColor.g
          >> backgroundColor.b
          >> imguiEnabled
          >> camera.Position.x
          >> camera.Position.y
          >> camera.Position.z
          >> camera.Front.x
          >> camera.Front.y
          >> camera.Front.z;
}
