//
// Created by maybe on 2020/12/5.
//

#include "shatter_vertex_buffer.h"

namespace shatter::buffer{

    std::shared_ptr<Shatter_Vertex_Buffer> Shatter_Vertex_Buffer::Create_Vertex_Buffer(VkDevice* device,
                                                        const std::shared_ptr<model::Shatter_Model>& model){
        auto vertex_buffer = std::make_shared<Shatter_Vertex_Buffer>();
        vertex_buffer->Set_Device(device);
        if(vertex_buffer->Init_Vertex_Buffer(device,model)){
            return vertex_buffer;
        }else{
            throw std::runtime_error("create vertex_buffer error!");
        }
    }

    bool Shatter_Vertex_Buffer::Init_Vertex_Buffer(VkDevice* device,
                                                   const std::shared_ptr<model::Shatter_Model>& model){
        bool val = false;
        do{
            if(model->Get_Type() == model::Model_Type::Boom_Model){
                auto tmp_model = std::dynamic_pointer_cast<model::Shatter_Boom_Model>(model);

                /*
                 * 需要包含所有的数据的容量不仅仅是位置
                 */
                VkDeviceSize bufferSize = tmp_model->Get_Model_Buffer_Size();

                m_element_number = tmp_model->Get_Vertex_Number();
                VkBuffer stagingBuffer;
                VkDeviceMemory stagingBufferMemory;
                createBuffer(bufferSize,
                             VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                             VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                             stagingBuffer,
                             stagingBufferMemory);
                void *data;
                vkMapMemory(*render::base_render::Get_Render().Get_Device(),
                            stagingBufferMemory,
                            0,
                            bufferSize,
                            0,
                            &data);
                std::memset(data,0,(size_t)bufferSize);
                memcpy(data,
                       tmp_model->Get_Model_Vec()->data(),
                       (size_t) (*tmp_model->Get_Size_Vec())[0]);
                vkUnmapMemory(*render::base_render::Get_Render().Get_Device(), stagingBufferMemory);

                void *data1;
                vkMapMemory(*render::base_render::Get_Render().Get_Device(),
                            stagingBufferMemory,
                            (*tmp_model->Get_Offset_Vec())[4],
                            (*tmp_model->Get_Size_Vec())[4],
                            0,
                            &data1);
                std::memset(data1,0,(size_t)(*tmp_model->Get_Size_Vec())[4]);
                memcpy(data1,
                       tmp_model->Get_Temperature_Vec()->data(),
                       (size_t) (*tmp_model ->Get_Size_Vec())[4]);
                vkUnmapMemory(*render::base_render::Get_Render().Get_Device(), stagingBufferMemory);

                createBuffer(bufferSize,
                             VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                             VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                             m_buffer,
                             m_memory);
                copyBuffer(stagingBuffer, m_buffer, bufferSize);

                vkDestroyBuffer(*render::base_render::Get_Render().Get_Device(), stagingBuffer, nullptr);
                vkFreeMemory(*render::base_render::Get_Render().Get_Device(), stagingBufferMemory, nullptr);
                val = true;
            }
        }while(false);
        return val;
    };

};






