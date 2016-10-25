#include "Box.h"


Box::Box(glm::vec3 position, float length) {
    glm::vec3 frontUpperRight(position.x+length, position.y+length, position.z+length),
            frontBottomRight(position.x+length, position.y, position.z+length);
    glm::vec3 frontBottomLeft(position.x, position.y, position.z+length),
            frontUpperLeft(position.x, position.y+length, position.z+length);
    glm::vec3 backUpperLeft(position.x, position.y+length, position.z+length),
            backUpperRight(position.x+length, position.y, position.z+(length*2));
    glm::vec3 backBottomRight(position.x+length, position.y, position.z+(length)),
            backBottomLeft(position.x, position.y, position.z+length);

    float rotation = (float)M_PI / 30.0f;
    frontUpperRight = glm::rotateY(frontUpperRight, rotation);
    frontBottomRight = glm::rotateY(frontBottomRight, rotation);
    frontBottomLeft = glm::rotateY(frontBottomLeft, rotation);
    frontUpperLeft = glm::rotateY(frontUpperLeft, rotation);

    const Surface Red(ColorDouble(1.0f, 0.0f, 0.0f));
    const Surface Green(ColorDouble(0.0f, 1.0f, 0.0f));
    const Surface Blue(ColorDouble(0.0f, 0.0f, 1.0f));
    const Surface Yellow(ColorDouble(1.0f, 1.0f, 0.0f));
    const Surface Purple(ColorDouble(1.0f, 0.0f, 1.0f));
    const Surface Teal(ColorDouble(0.0f, 1.0f, 1.0f));

    //Box floor
    triangles.push_back(Triangle(frontBottomRight, backBottomRight, frontBottomLeft, Red));
    triangles.push_back(Triangle(frontBottomRight, frontBottomLeft, backBottomLeft, Red));
    //Box Front
    triangles.push_back(Triangle(frontBottomRight, frontUpperRight, frontUpperLeft, Green));
    triangles.push_back(Triangle(frontBottomRight, frontBottomLeft, frontUpperLeft, Green));
    //Box Right Side
    triangles.push_back(Triangle(frontUpperRight, frontBottomRight, backBottomRight, Blue));
    triangles.push_back(Triangle(frontUpperRight, backUpperRight, backBottomRight, Blue));
    //Box Left Side
    triangles.push_back(Triangle(frontUpperLeft, frontBottomLeft, backBottomLeft, Yellow));
    triangles.push_back(Triangle(frontUpperLeft, backUpperLeft, backBottomLeft, Yellow));
    //Box Back Side
    triangles.push_back(Triangle(backBottomRight, backUpperRight, backUpperLeft, Purple));
    triangles.push_back(Triangle(backBottomRight, backBottomLeft, backUpperLeft, Purple));
    //Box Roof
    triangles.push_back(Triangle(frontUpperRight, backUpperRight, backUpperLeft, Teal));
    triangles.push_back(Triangle(frontUpperRight, frontUpperLeft, backUpperLeft, Teal));

}

const std::vector<Triangle> &Box::getTriangles() const {
    return triangles;
}
