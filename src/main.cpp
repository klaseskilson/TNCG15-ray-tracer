#include "Camera.h"
#include "Scene.h"

int main() {
    Scene scene;
    Camera cam(true);
    cam.setFov(M_PI / 1.5);

    // limit rendering numbers for debugging, comment out for magic resutl
    cam.setSpp(1);
    cam.setSubPixels(1);

    cam.createImage(scene);
    return 0;
}