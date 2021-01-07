//
// Created by maybe on 2020/11/28.
//

#include "shatter_pipeline.h"

namespace shatter::pipeline{

    Shatter_Pipeline::Shatter_Pipeline():
    m_pipelinelayout{VK_NULL_HANDLE},
    m_device{nullptr},
    m_pipeline{VK_NULL_HANDLE},
    generated{false}
    {
        m_descriptorsetlayout = std::vector<VkDescriptorSetLayout>();
        m_descriptorsetlayout.resize(1);
    }

    Shatter_Pipeline::~Shatter_Pipeline(){
        for(auto m : m_descriptorsetlayout){
            vkDestroyDescriptorSetLayout(*m_device, m, nullptr);
        }
        vkDestroyPipelineLayout(*m_device, m_pipelinelayout, nullptr);
        vkDestroyPipeline(*m_device, m_pipeline, nullptr);
    }





}








