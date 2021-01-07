//
// Created by maybe on 2020/11/24.
//

#ifndef SHATTER_ENGINE_SHATTER_VS_H
#define SHATTER_ENGINE_SHATTER_VS_H

//#define GLFW_INCLUDE_VULKAN
#include "shatter_shader.h"
//#include <glfw3.h>


namespace shatter {
    namespace shader {
    class Vertex_Shader : public Shatter_Shader{
        public:
//            Vertex_Shader();
        public:
            bool Init_Shader(const std::string&,VkDevice*);
        private:

        };
    };
};

#endif //SHATTER_ENGINE_SHATTER_VS_H
