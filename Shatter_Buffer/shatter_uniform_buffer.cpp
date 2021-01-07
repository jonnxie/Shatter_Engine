//
// Created by maybe on 2020/12/2.
//

#include "shatter_uniform_buffer.h"

namespace shatter::buffer{

    std::shared_ptr<Shatter_Uniform_Buffer> Shatter_Uniform_Buffer::Create_Uniform_Buffer(VkDevice* device,
                                                                VkDeviceSize size){
        auto buffer = std::make_shared<Shatter_Uniform_Buffer>();
        buffer->Set_Device(device);
        if(buffer->Init_Uniform_Buffer(size)){
            return buffer;
        }else{
            throw std::runtime_error("create uniform_buffer error!");
        }
    }

    bool Shatter_Uniform_Buffer::Init_Uniform_Buffer(VkDeviceSize size){
        bool val = false;
        do{
            createBuffer(size,
                         VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                         VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                         m_buffer,
                         m_memory);
            val = true;
        }while(false);
        return val;
    }

    Shatter_Uniform_Buffer::Shatter_Uniform_Buffer()
    {
    };

};




