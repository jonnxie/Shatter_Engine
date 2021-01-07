//
// Created by maybe on 2020/11/16.
//

#ifndef SHATTER_ENGINE_SHATTER_ITEM_H
#define SHATTER_ENGINE_SHATTER_ITEM_H

//#define GLFW_INCLUDE_VULKAN
#include <glm.hpp>
//#include <glfw3.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#include <unordered_map>
#include <gtx/hash.hpp>
#include <memory>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription = {};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }

    bool operator==(const Vertex &other) const {
        return pos == other.pos && color == other.color && texCoord == other.texCoord;
    }

};

struct QueueFamilyIndices {
    int graphicsFamily = -1;
    int presentFamily = -1;
    int computeFamily = -1;

    bool isComplete() {
        return graphicsFamily >= 0 && presentFamily >= 0 && computeFamily >= 0;
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};


class Shatter_Core : public std::enable_shared_from_this<Shatter_Core>{
public:
    virtual uint32_t Find_MemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) = 0;
    virtual VkCommandBuffer beginSingleTimeCommands() = 0;
    virtual void endSingleTimeCommands(VkCommandBuffer commandBuffer) = 0;
    virtual void AllocateDescriptorSets(const std::vector<VkDescriptorSetLayout>& des_set_layout,VkDescriptorSet* set) = 0;
//    virtual bool hasStencilComponent(VkFormat format) = 0;
    virtual glm::mat4 Get_View() = 0;
    virtual glm::mat4 Get_Proj() = 0;
    virtual VkRenderPass Get_RenderPass() = 0;
    virtual VkExtent2D Get_Extent2D() = 0;
};

namespace std {
    template<>
    struct hash<Vertex> {
        size_t operator()(Vertex const &vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^
                   (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}


/*
 *读glsl文件随后创建shader的模块
 */
std::vector<char> readFile(const std::string &filename);

/*
 *创建shader的着色器模块
 */
VkShaderModule createShaderModule(const std::vector<char> &code,VkDevice device);

/*
 * 限定extent的范围
 */
VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities,unsigned int width,unsigned int heigh);

/*
 * 选定呈现模式
 */
VkPresentModeKHR Choose_SwapPresent_Mode(const std::vector<VkPresentModeKHR>& availablePresentModes);

/*
 * 选定表面格式
 */
VkSurfaceFormatKHR Choose_SwapSurface_Format(const std::vector<VkSurfaceFormatKHR> &availableFormats);

/*
 * 检验深度模板数据格式
 */
bool hasStencilComponent(VkFormat format);

#endif //SHATTER_ENGINE_SHATTER_ITEM_H
