//
// Created by maybe on 2020/11/12.
//

#ifndef VULKAN_TOTURIOL_SHATTER_INPUT_H
#define VULKAN_TOTURIOL_SHATTER_INPUT_H

#include <glfw3.h>
#include <iostream>
#include <map>
#include <memory>
//#include "../Shatter_Action/shatter_action.h"


namespace shatter {

    namespace input {

        typedef void(* Input_Callback_Func)();

        class Shatter_Input{
        public:
            Shatter_Input();


//            static std::shared_ptr<Shatter_Input> Create_Shatter_Input();

//            void set_callback(GLFWwindow* window);

            virtual void key_event_callback(int key, int action) = 0;

//            static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        protected:
            Input_Callback_Func W_precallback;

            Input_Callback_Func S_precallback;

            Input_Callback_Func A_precallback;

            Input_Callback_Func D_precallback;

            Input_Callback_Func Space_precallback;

        };
    }

}
#endif //VULKAN_TOTURIOL_SHATTER_INPUT_H
