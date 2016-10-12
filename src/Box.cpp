//
// Created by Carl Englund on 2016-10-12.
//

#include "Box.h"


void Box::createBox(glm::vec3 position, float length) {

    //Vertices needs to be adapted to room positions.
    glm::vec3 frontUpperRight(position.x+length, position.y+length, position.z+length), frontBottomRight(position.x+length, position.y, position.z+length);
    glm::vec3 frontBottomLeft(position.x, position.y, position.z+length), frontUpperLeft(position.x, position.y+length, position.z+length);
    glm::vec3 backUpperLeft(position.x+length, position.y+length, position.z), backUpperRight(position.x, position.y+length, position.z);
    glm::vec3 backBottomRight(position.x+length, position.y, position.z), backBottomLeft(position.x, position.y, position.z);
    
    const ColorDouble Red(1.0f, 0.0f, 0.0f);
    const ColorDouble Green(0.0f, 1.0f, 0.0f);
    const ColorDouble Blue(0.0f, 0.0f, 1.0f);
    const ColorDouble Yellow(1.0f, 1.0f, 0.0f);
    const ColorDouble Purple(1.0f, 0.0f, 1.0f);
    const ColorDouble Teal(0.0f, 1.0f, 1.0f);

    //Box floor
    triangles[0] = Triangle(frontBottomRight, backBottomRight, frontBottomLeft, Red) ;
    triangles[1] = Triangle(frontBottomRight, frontBottomLeft, backBottomLeft, Red);
    //Box Front
    triangles[2] = Triangle(frontBottomRight, frontUpperRight, frontUpperLeft, Green);
    triangles[3] = Triangle(frontBottomRight, frontBottomLeft, frontUpperLeft, Green);
    //Box Right Side
    triangles[4] = Triangle(frontUpperRight, frontBottomRight, backBottomRight, Blue);
    triangles[5] = Triangle(frontUpperRight, backUpperRight, backBottomRight, Blue);
    //Box Left Side
    triangles[6] = Triangle(frontUpperLeft, frontBottomLeft, backBottomLeft, Yellow);
    triangles[7] = Triangle(frontUpperLeft, backUpperLeft, backBottomLeft, Yellow);
    //Box Back Side
    triangles[8] = Triangle(backBottomRight, backUpperRight, backUpperLeft, Purple);
    triangles[9] = Triangle(backBottomRight, backBottomLeft, backUpperLeft, Purple);
    //Box Roof
    triangles[10] = Triangle(frontUpperRight, backUpperRight, backUpperLeft, Teal) ;
    triangles[11] = Triangle(frontUpperRight, frontUpperLeft, backUpperLeft, Teal);

}