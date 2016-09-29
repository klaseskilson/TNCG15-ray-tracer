#ifndef TNCG15_CAMERA_H
#define TNCG15_CAMERA_H

#include <array>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Pixel.h"

const int WIDTH = 1000;
const int HEIGHT = 1000;

class Camera {
public:
    Camera() {};
    ~Camera() {};
    void render();
    void createImage(std::string filename = "rayTracedImage.ppm");

private:
    //2D 1000x1000 array of type Pixel
    //Two instances of vertex one for each eye
    //A bool to flip between the eye

    std::array<std::array<Pixel, HEIGHT>, WIDTH> pixels;
    glm::vec3 position1, position2;
    bool eyeBeingUsed;
};
#endif //TNCG15_CAMERA_H
