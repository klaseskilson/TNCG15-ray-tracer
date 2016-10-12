//
// Created by Carl Englund on 2016-10-12.
//

#include "Box.h"


void Box::createBox() {

    //Vertices needs to be adapted to room positions.
    glm::vec3 frontUpperRight(5.0f, 5.0f, 5.0f), frontBottomRight(5.0f, 2.5f, 5.0f);
    glm::vec3 frontBottomLeft(2.5f, 2.5f, 5.0f), frontUpperLeft(2.5f, 5.0f, 5.0f);
    glm::vec3 backUpperLeft(5.0f, 5.0f, 2.5f), backUpperRight(2.5f, 5.0f, 2.5f);
    glm::vec3 backBottomRight(5.0f, 2.5f, 2.5f), backBottomLeft(2.5f, 2.5f, 2.5f);
    
    const ColorDouble Red(255.0f, 0.0f, 0.0f);
    const ColorDouble Green(0.0f, 255.0f, 0.0f);
    const ColorDouble Blue(0.0f, 0.0f, 255.0f);
    const ColorDouble Yellow(255.0f, 255.0f, 0.0f);
    const ColorDouble Purple(255.0f, 0.0f, 255.0f);
    const ColorDouble Teal(0.0f, 255.0f, 255.0f);

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