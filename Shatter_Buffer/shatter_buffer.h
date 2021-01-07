//
// Created by maybe on 2020/11/21.
//

#ifndef SHATTER_ENGINE_SHATTER_BUFFER_H
#define SHATTER_ENGINE_SHATTER_BUFFER_H

#include <vulkan/vulkan.h>
#include <glfw3.h>
#include <iostream>
#include <memory>
#include "../Shatter_Item/shatter_item.h"
//#include "../Shatter_Model/shatter_model_include.h"
#include "../Shatter_Render/shatter_render_include.h"


namespace shatter {
    namespace buffer {


        class Shatter_Buffer : public std::enable_shared_from_this<Shatter_Buffer> {
        public:
            Shatter_Buffer();

            ~Shatter_Buffer();

            void createBuffer(VkDeviceSize size,
                              VkBufferUsageFlags usage,
                              VkMemoryPropertyFlags properties,
                              VkBuffer &buffer,
                              VkDeviceMemory &bufferMemory);

            void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        public:
            void Set_Device(VkDevice *device) { m_device = device; };

            VkBuffer Get_Buffer() { return m_buffer; };

            VkDeviceMemory Get_Memory() { return m_memory; };

            const VkDeviceSize Get_Buffer_Size() { return m_buffer_size; };

            const uint32_t Get_Element_Number() { return m_element_number; };
        protected:
            VkDeviceSize m_buffer_size;
            uint32_t m_element_number;
            VkDevice *m_device;
            VkBuffer m_buffer;
            VkDeviceMemory m_memory;

        };

    };
};

#endif //SHATTER_ENGINE_SHATTER_BUFFER_H
