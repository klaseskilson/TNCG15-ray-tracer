#include <Light.h>
#include "Box.h"
#include "Camera.h"
#include "Scene.h"

int main() {
    Scene scene;

    Sphere sphere1(glm::vec3(-2.0f, -3.0f, 10.0f), 2.0f, Surface(ColorDouble(0.0f), SPECULAR));
    scene.addSphere(sphere1);
    Sphere sphere2(glm::vec3(3.0f, -3.0f, 7.0f), 2.0f, Surface(ColorDouble(0.0f, 1.0f, 0.0f)));
    scene.addSphere(sphere2);

    Light areaLight;
    scene.importTriangles(areaLight.getTriangles());
    scene.addLight(areaLight);

    Camera cam(true);
    cam.setFov(M_PI / 1.5);

    // limit rendering numbers for debugging, comment out for magic result
    cam.setSpp(10);
    cam.setSubPixels(2);

    cam.createImage(scene);
    return 0;
}