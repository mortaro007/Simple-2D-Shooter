#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string name, glm::vec3 leftBottomCorner2, float width, float height, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangleOutline(const std::string name, glm::vec3 leftBottomCorner2, float width, float height, glm::vec3 color, bool fill = false);
    Mesh* CreateCircle(std::string name, float radius, glm::vec3 color);

}
