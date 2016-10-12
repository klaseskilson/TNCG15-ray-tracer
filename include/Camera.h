#ifndef TNCG15_CAMERA_H
#define TNCG15_CAMERA_H

#include <array>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Pixel.h"

typedef std::pair<glm::vec3, glm::vec3> CameraPos;

const int WIDTH = 1000;
const int HEIGHT = 1000;

const CameraPos CAMERA_POS_1 (glm::vec3(0.0f, 2.5f, 0.0f),
                              glm::vec3(0.0f, 2.5f, 2.5f));
const CameraPos CAMERA_POS_2 (glm::vec3(0.0f, 2.5f, 2.5f),
                              glm::vec3(0.0f, 2.5f, 0.0f));

class Camera {
public:
    Camera(bool cameraPosition = true);
    ~Camera() {};
    void createImage(std::string filename = "rayTracedImage.ppm");
    void setFov(float fov);

private:
    void createPixels();
    //Two instances of vertex one for each eye
    CameraPos getCamera();
    Ray getRayFromPixelCoords(const int w, const int h);
    //2D 1000x1000 array of type Pixel
    std::array<std::array<Pixel, HEIGHT>, WIDTH> pixels;
    // FOV in degrees
    float fov = 60.0f;
    //A bool to flip between the eye
    bool eyeBeingUsed;
};
#endif //TNCG15_CAMERA_H
