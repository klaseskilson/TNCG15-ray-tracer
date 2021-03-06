#ifndef TNCG15_CAMERA_H
#define TNCG15_CAMERA_H

#include <array>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iomanip>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/component_wise.hpp>
#include "Pixel.h"
#include "Scene.h"
#include "utilities.h"

typedef std::pair<glm::vec3, glm::vec3> CameraPos;

const int WIDTH = 400;
const int HEIGHT = 400;

const CameraPos CAMERA_POS_1 (glm::vec3(0.0f, 0.0f, 0.0f),
                              glm::vec3(0.0f, 0.0f, 1.0f));
const CameraPos CAMERA_POS_2 (glm::vec3(0.0f, 2.5f, 2.5f),
                              glm::vec3(-0.3f, -0.3f, 0.3f));

const int MAX_DEPTH = 5;

class Camera {
public:
    Camera(bool cameraPosition = true);
    ~Camera() {};
    void createImage(Scene&, std::string filename = "rayTracedImage.ppm");
    void setFov(float fov);

    void setSpp(int spp);

    void setSubPixels(int subPixels);

private:
    void createPixels();
    double castRays(Scene&);
    ColorDouble castRay(Scene &scene, Ray &ray, int depth = 0);
    void writeToFile(const std::string, const double&);

    CameraPos getCamera();

    //2D 1000x1000 array of type Pixel
    std::array<std::array<Pixel, WIDTH>, HEIGHT> pixels;
    Ray getRayFromPixelCoords(const double w, const double h);

    // FOV in radians
    float fov = ((float) M_PI) / 1.5f;

    //A bool to flip between the cameras
    bool eyeBeingUsed;

    // sample per pixel
    int spp = 50;

    // sub-pixels
    int subPixels = 3;
};
#endif //TNCG15_CAMERA_H
