//
// Created by maybe on 2020/11/14.
//

#ifndef SHATTER_ENGINE_SHATTER_MODEL_H
#define SHATTER_ENGINE_SHATTER_MODEL_H

//#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>
#include "../Shatter_Item/shatter_item.h"

#include <iostream>
#include <memory>
#include <glm.hpp>

namespace shatter{
    namespace model {

        enum class Model_Type {
            Boom_Model,
        };


        class Shatter_Model : public std::enable_shared_from_this<Shatter_Model>{
        public:
            virtual VkDeviceSize Get_Model_Vertex_Size() = 0;
            virtual VkDeviceSize Get_Model_Index_Size() = 0;
            virtual uint32_t Get_Vertex_Number() = 0;
            virtual uint32_t Get_Index_Number() = 0;
            Model_Type Get_Type(){return m_type;};
            Shatter_Model();
            ~Shatter_Model();
        protected:
            Model_Type m_type;
        };

    };
};


#endif //SHATTER_ENGINE_SHATTER_MODEL_H
