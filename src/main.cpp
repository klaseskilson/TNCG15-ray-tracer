#include <Light.h>
#include "Box.h"
#include "Camera.h"
#include "Scene.h"

int main() {
    Scene scene;

    Box b(glm::vec3(0.0f, -2.0f, 5.0f), 2);
    Light areaLight;
    scene.importTriangles(b.getTriangles());
    scene.importTriangles(areaLight.getTriangles());

    Camera cam(true);
    cam.setFov(M_PI / 1.5);

    // limit rendering numbers for debugging, comment out for magic resutl
    cam.setSpp(1);
    cam.setSubPixels(1);

    cam.createImage(scene);
    return 0;
}