//
// Created by maybe on 2020/11/21.
//

#include "shatter_buffer.h"
#include "../Shatter_Render/render.h"

namespace shatter::buffer{

    Shatter_Buffer::Shatter_Buffer():
    m_buffer{VK_NULL_HANDLE},
    m_memory{VK_NULL_HANDLE},
    m_device{nullptr},
    m_buffer_size{0},
    m_element_number{0}
    {
    }

    void Shatter_Buffer::createBuffer(VkDeviceSize size,
                                      VkBufferUsageFlags usage,
                                      VkMemoryPropertyFlags properties,
                                      VkBuffer &buffer,
                                      VkDeviceMemory &bufferMemory){
        m_buffer_size = size;
        VkBufferCreateInfo bufferInfo = {};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(*render::base_render::Get_Render().Get_Device(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to create buffer!");
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(*render::base_render::Get_Render().Get_Device(),
                                      buffer,
                                      &memRequirements);

        VkMemoryAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = render::base_render::Get_Render().Find_MemoryType(memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(*render::base_render::Get_Render().Get_Device(),
                             &allocInfo,
                             nullptr,
                             &bufferMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate buffer memory!");
        }
        vkBindBufferMemory(*render::base_render::Get_Render().Get_Device(),
                           buffer,
                           bufferMemory,
                           0);
    }

    void Shatter_Buffer::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size){
        VkCommandBuffer commandBuffer = render::base_render::Get_Render().beginSingleTimeCommands();

        VkBufferCopy copyRegion = {};
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

        render::base_render::Get_Render().endSingleTimeCommands(commandBuffer);
    }

    Shatter_Buffer::~Shatter_Buffer(){
        vkDestroyBuffer(*render::base_render::Get_Render().Get_Device(),
                        m_buffer,
                        nullptr);
        vkFreeMemory(*render::base_render::Get_Render().Get_Device(),
                     m_memory,
                     nullptr);
    }

}




