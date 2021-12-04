#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_TRIANGLE_FAN);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string name,
    glm::vec3 leftBottomCorner2,
    float width, 
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner2;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_TRIANGLE_FAN);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangleOutline(
    const std::string name,
    glm::vec3 leftBottomCorner2,
    float width,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner2;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
        //square->SetDrawMode(GL_LINE_STRIP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateCircle(
    std::string name, 
    float radius, 
    glm::vec3 color)
{
    const float PI = 3.1415926f;

    std::vector<VertexFormat> result;

    float increment = 2.0f * PI / 10000;

    for (float currAngle = 0.0f; currAngle <= 2.0f * PI; currAngle += increment)
    {
        result.push_back(VertexFormat(glm::vec3(radius * cos(currAngle) + 0, radius * sin(currAngle) + 0, 0), color));
    }

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices;
    for (int i = 0; i < result.size(); i++) {
        indices.push_back(i);
    }

    square->SetDrawMode(GL_TRIANGLE_FAN);
    square->InitFromData(result, indices);

    return square;
}
