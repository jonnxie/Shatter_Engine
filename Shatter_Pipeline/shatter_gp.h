//
// Created by maybe on 2020/11/23.
//

#ifndef SHATTER_ENGINE_SHATTER_GP_H
#define SHATTER_ENGINE_SHATTER_GP_H

#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>
#include <memory>
#include <iostream>
#include <vector>
#include "shatter_pipeline.h"

namespace shatter {

    namespace pipeline {

        class Shatter_GP : public Shatter_Pipeline{
        public:
            Shatter_GP();
            ~Shatter_GP();
            bool Init_GraphicsPipeline(VkDevice* device);
        public:
            void Generate_Pipeline() override;

        protected:
            void Set_Vertex_Input_Info(VkPipelineVertexInputStateCreateInfo* createinfo);
            void Set_Shader_Stage(std::vector<VkPipelineShaderStageCreateInfo>& shader_stage_vec);
            void Set_Assembly_State(VkPipelineInputAssemblyStateCreateInfo* assembly_state);
            void Set_Tessellation_State(VkPipelineTessellationStateCreateInfo* pTessellationState);
            void Set_Viewport_State(VkPipelineViewportStateCreateInfo* viewport_state);
            void Set_Rasterization_State(VkPipelineRasterizationStateCreateInfo* rasterizer);
            void Set_Multisample_State(VkPipelineMultisampleStateCreateInfo* multisampling);
            void Set_Depth_Stencil_State(VkPipelineDepthStencilStateCreateInfo* depthStencil);
            void Set_Color_Blend_State(VkPipelineColorBlendStateCreateInfo* colorBlending);
            void Set_Dynamic_State(VkPipelineDynamicStateCreateInfo* pDynamicState);
            /*
             * 配置管线布局
             */
            void Set_PipelineLayout(VkPipelineLayout pipelineLayout);

            void Set_Render_Pass(VkRenderPass renderPass);

            void Set_Subpass(uint32_t subpass);

            void Set_Base_Pipeline_Handle(VkPipeline basePipelineHandle);

            void Set_Base_Pipeline_Index(int32_t basePipelineIndex);

        protected:
            VkGraphicsPipelineCreateInfo m_create_info;
        };

    };
};
#endif //SHATTER_ENGINE_SHATTER_GP_H
