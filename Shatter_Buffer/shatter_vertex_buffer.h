//
// Created by maybe on 2020/12/5.
//

#ifndef SHATTER_ENGINE_SHATTER_VERTEX_BUFFER_H
#define SHATTER_ENGINE_SHATTER_VERTEX_BUFFER_H

#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>
#include "shatter_buffer.h"
#include "../Shatter_Model/shatter_model_include.h"
#include <memory>
#include <iostream>
#include <cstring>

namespace shatter {
    namespace buffer {


        class Shatter_Vertex_Buffer : public Shatter_Buffer {
        public:
            static std::shared_ptr<Shatter_Vertex_Buffer> Create_Vertex_Buffer(VkDevice *device,
                                                                               const std::shared_ptr<model::Shatter_Model> &model);

            Shatter_Vertex_Buffer() = default;

            ~Shatter_Vertex_Buffer() = default;

            bool Init_Vertex_Buffer(VkDevice *device,
                                    const std::shared_ptr<model::Shatter_Model> &model);

        private:

        };

    };
};

#endif //SHATTER_ENGINE_SHATTER_VERTEX_BUFFER_H
