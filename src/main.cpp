#include <iostream>
#include <Triangle.h>
#include <Ray.h>
#include "Camera.h"

int main() {
    Scene scene;
    Camera cam(true);
    cam.setSpp(5);
    cam.createImage(scene);
    return 0;
}