//
// Created by maybe on 2020/11/24.
//

#ifndef SHATTER_ENGINE_SHATTER_SHADER_H
#define SHATTER_ENGINE_SHATTER_SHADER_H

#define GLFW_INCLUDE_VULKAN
#include <iostream>
#include <memory>
#include <string>
#include <vector>
//#include <glfw3.h>
#include "../Shatter_Item/shatter_item.h"


namespace shatter {

    namespace shader {

        class Shatter_Shader : public std::enable_shared_from_this<Shatter_Shader> {
        public:
             Shatter_Shader();
            ~Shatter_Shader();
        public:
            VkPipelineShaderStageCreateInfo Get_Info(){return m_shader_info;};
            void Set_Device(VkDevice* device){m_device = device;};
            std::vector<VkDescriptorSetLayoutBinding>* Get_DesSLB(){return &m_descriptor_slb_vec;};
        protected:
            VkPipelineShaderStageCreateInfo m_shader_info;
            VkShaderModule m_shader_module;
            std::vector<VkDescriptorSetLayoutBinding> m_descriptor_slb_vec;
            VkDevice* m_device;
        };


    };
};
#endif //SHATTER_ENGINE_SHATTER_SHADER_H
