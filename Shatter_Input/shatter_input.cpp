//
// Created by maybe on 2020/11/12.
//

#include "shatter_input.h"
#include "../Shatter_Render/render.h"

namespace shatter{

    namespace input{
        Shatter_Input::Shatter_Input():W_precallback(nullptr),
                        S_precallback(nullptr),
                        A_precallback(nullptr),
                        D_precallback(nullptr),
                        Space_precallback(nullptr)
        {
        };

//        std::shared_ptr<Shatter_Input> Shatter_Input::Create_Shatter_Input(){
//            auto return_value = std::make_shared<Shatter_Input>();
//            if(return_value != nullptr){
//                return return_value;
//            }else{
//                throw std::runtime_error("create Shatter_input error!");
//            }
//        }

//        void Shatter_Input::set_callback(GLFWwindow* window){
//            glfwSetKeyCallback(window,key_callback);
//        }

//        void Shatter_Input::key_event_callback(){
//
//            return;
//        }

//        void Shatter_Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
//            if(action == GLFW_PRESS){
//                Shatter_Input *app = reinterpret_cast<Shatter_Input *>(glfwGetWindowUserPointer(window));
//                app->key_event_callback();
//            }
//        }
    }

}







