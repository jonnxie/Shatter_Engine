//
// Created by maybe on 2020/11/28.
//

#ifndef SHATTER_ENGINE_SHATTER_CP_H
#define SHATTER_ENGINE_SHATTER_CP_H

#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>
#include <memory>
#include <iostream>
#include "shatter_pipeline.h"

namespace shatter::pipeline{
    class Shatter_CP : public Shatter_Pipeline{
    public:
        Shatter_CP();
        ~Shatter_CP();
        bool Init_ComputePipeline(VkDevice* device);
    public:
        void Generate_Pipeline() override;
    protected:
        void Set_PipelineShaderStage_CreateInfo(VkPipelineShaderStageCreateInfo info){m_create_info.stage = info;};
        void Set_PipelineLayout(VkPipelineLayout layout){m_create_info.layout = layout;};
    protected:
        VkComputePipelineCreateInfo m_create_info;
    };
};

#endif //SHATTER_ENGINE_SHATTER_CP_H
