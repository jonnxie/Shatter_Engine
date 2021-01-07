//
// Created by maybe on 2020/12/16.
//

#ifndef SHATTER_ENGINE_SHATTER_CAMERA_H
#define SHATTER_ENGINE_SHATTER_CAMERA_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <memory>

namespace shatter::camera{

    enum class LookAt{
        eye,
        center,
        up,
    };

    enum class Perspective{
        fovy,
        aspect,
        zNear,
        zFar,
    };

class Shatter_Camera : public std::enable_shared_from_this<Shatter_Camera>{
    public:
        void Set_Value(Perspective aim,float value);
        void Set_Value(LookAt aim,glm::vec3 value);
        void Generate_LookAt();
        void Generate_Proj();
        void Generate();
        glm::mat4 Get_View(){return view;};
        glm::mat4 Get_Proj(){return proj;};
    private:
        float fovy;
        float aspect;
        float zNear;
        float zFar;

        glm::vec3 eye;
        glm::vec3 center;
        glm::vec3 up;

        /*
         * 摄像机矩阵
         */
        glm::mat4 view;
        /*
         * 透视投影矩阵
         */
        glm::mat4 proj;
    };

}





#endif //SHATTER_ENGINE_SHATTER_CAMERA_H
