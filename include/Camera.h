#ifndef TNCG15_CAMERA_H
#define TNCG15_CAMERA_H

#include <array>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "Pixel.h"
#include "Scene.h"

typedef std::pair<glm::vec3, glm::vec3> CameraPos;

const int WIDTH = 300;
const int HEIGHT = 300;

const CameraPos CAMERA_POS_1 (glm::vec3(0.0f, 2.5f, 0.0f),
                              glm::vec3(0.0f, 0.0f, 1.0f));
const CameraPos CAMERA_POS_2 (glm::vec3(0.0f, 2.5f, 2.5f),
                              glm::vec3(0.0f, 0.0f, -1.0f));

class Camera {
public:
    Camera(bool cameraPosition = true);
    ~Camera() {};
    void createImage(Scene&, std::string filename = "rayTracedImage.ppm");
    void setFov(float fov);

private:
    void createPixels();
    ColorDouble castRays(Scene&);
    ColorDouble castRay(Scene &scene, const Ray &ray, const ColorDouble &inc, int reflections = 3);
    void writeToFile(const std::string, const ColorDouble&);

    CameraPos getCamera();

    //2D 1000x1000 array of type Pixel
    std::array<std::array<Pixel, WIDTH> ,HEIGHT> pixels;
    Ray getRayFromPixelCoords(const int w, const int h);

    // FOV in radians
    float fov = ((float) M_PI) / 2.0f;

    //A bool to flip between the cameras
    bool eyeBeingUsed;
};
#endif //TNCG15_CAMERA_H
