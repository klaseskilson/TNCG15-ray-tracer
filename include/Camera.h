//
// Created by Carl Englund on 06/09/16.
//

#ifndef TNCG15_CAMERA_H
#define TNCG15_CAMERA_H

class Camera {

    public:
        void render();
        void createImage();

    private:
        //2D 1000x1000 array of type Pixel
        //Two instances of vertex one for each eye
        //A bool to flip between the eys

};
#endif //TNCG15_CAMERA_H
