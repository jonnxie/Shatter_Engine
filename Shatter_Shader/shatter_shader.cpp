//
// Created by maybe on 2020/11/24.
//

#include "shatter_shader.h"


namespace shatter::shader{


    Shatter_Shader::Shatter_Shader():
    m_shader_info{},
    m_shader_module{VK_NULL_HANDLE},
    m_device{nullptr}
    {
        m_descriptor_slb_vec = std::vector<VkDescriptorSetLayoutBinding>();
    }

    Shatter_Shader::~Shatter_Shader() {
        vkDestroyShaderModule(*m_device, m_shader_module, nullptr);
    }

}





