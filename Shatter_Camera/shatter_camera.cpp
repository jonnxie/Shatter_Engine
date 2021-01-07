//
// Created by maybe on 2020/12/16.
//

#include "shatter_camera.h"

namespace shatter::camera{
    void Shatter_Camera::Set_Value(Perspective aim,float value){
        switch (aim) {
            case Perspective::aspect:
                aspect = value;
            case Perspective::fovy:
                fovy = value;
            case Perspective::zFar:
                zFar = value;
            case Perspective::zNear:
                zNear = value;
            default:
                break;
        }
    }
    void Shatter_Camera::Set_Value(LookAt aim,glm::vec3 value){
        switch (aim) {
            case LookAt::eye:
                eye = value;
            case LookAt::center:
                center = value;
            case LookAt::up:
                up = value;
            default:
                break;
        }
    }
    void Shatter_Camera::Generate_LookAt(){
        view = glm::lookAt(eye, center,up);
    }
    void Shatter_Camera::Generate_Proj(){
        proj = glm::perspective(fovy, aspect, zNear, zFar);
    }
    void Shatter_Camera::Generate(){
        Generate_Proj();
        Generate_LookAt();
    }

}








