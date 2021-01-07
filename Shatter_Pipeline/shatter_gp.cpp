//
// Created by maybe on 2020/11/23.
//

#include "shatter_gp.h"
#include "../Shatter_Shader/shatter_shader_include.h"

namespace shatter::pipeline{

//     std::shared_ptr<Shatter_GP> Shatter_GP::Create_GraphicsPipeline(std::shared_ptr<Shatter_Pipeline_Delegate> delegate){
//         auto pipeline = std::make_shared<Shatter_GP>();
//         if(pipeline && !pipeline->Init_GraphicsPipeline(delegate)){
//             return pipeline;
//         }else{
//             throw std::runtime_error("craete graphicspipeline error!");
//         }
//     }
    Shatter_GP::Shatter_GP():
    m_create_info{}
    {

    }

    Shatter_GP::~Shatter_GP(){

    }

    bool Shatter_GP::Init_GraphicsPipeline(VkDevice* device){
         bool val = false;
         do{
             Set_Pipeline_Device(device);
             m_create_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
             val = true;
         }while(false);
         return val;
     }

    void Shatter_GP::Generate_Pipeline(){
        if(!generated) {
            if (vkCreateGraphicsPipelines(*m_device,
                                          VK_NULL_HANDLE,
                                          1,
                                          &m_create_info,
                                          nullptr,
                                          &m_pipeline) !=
                VK_SUCCESS) {
                throw std::runtime_error("failed to create graphics_pipeline!");
            }
        }
    }

    void Shatter_GP::Set_Vertex_Input_Info(VkPipelineVertexInputStateCreateInfo* createinfo){
        m_create_info.pVertexInputState = createinfo;
     }

    void Shatter_GP::Set_Shader_Stage(std::vector<VkPipelineShaderStageCreateInfo>& shader_stage_vec){
         m_create_info.stageCount = shader_stage_vec.size();
         m_create_info.pStages = shader_stage_vec.data();
     }

    void Shatter_GP::Set_Assembly_State(VkPipelineInputAssemblyStateCreateInfo* assembly_state){
         m_create_info.pInputAssemblyState = assembly_state;
     }

    void Shatter_GP::Set_Tessellation_State(VkPipelineTessellationStateCreateInfo* pTessellationState){
         m_create_info.pTessellationState = pTessellationState;
     }

    void Shatter_GP::Set_Viewport_State(VkPipelineViewportStateCreateInfo* viewport_state){
         m_create_info.pViewportState = viewport_state;
     }

    void Shatter_GP::Set_Rasterization_State(VkPipelineRasterizationStateCreateInfo* rasterizer){
         m_create_info.pRasterizationState = rasterizer;
     }

    void Shatter_GP::Set_Multisample_State(VkPipelineMultisampleStateCreateInfo* multisampling){
         m_create_info.pMultisampleState = multisampling;
     }

    void Shatter_GP::Set_Depth_Stencil_State(VkPipelineDepthStencilStateCreateInfo* depthStencil){
         m_create_info.pDepthStencilState = depthStencil;
     }

    void Shatter_GP::Set_Color_Blend_State(VkPipelineColorBlendStateCreateInfo* colorBlending){
         m_create_info.pColorBlendState = colorBlending;
     }

    void Shatter_GP::Set_Dynamic_State(VkPipelineDynamicStateCreateInfo* pDynamicState){
         m_create_info.pDynamicState = pDynamicState;
     }
    /*
    * 配置管线布局
    */
    void Shatter_GP::Set_PipelineLayout(VkPipelineLayout pipelineLayout){
        m_create_info.layout = pipelineLayout;
    }

    void Shatter_GP::Set_Render_Pass(VkRenderPass renderPass){
         m_create_info.renderPass = renderPass;
     }

    void Shatter_GP::Set_Subpass(uint32_t subpass){
        m_create_info.subpass = subpass;
    }

    void Shatter_GP::Set_Base_Pipeline_Handle(VkPipeline basePipelineHandle){
         m_create_info.basePipelineHandle = basePipelineHandle;
     }

    void Shatter_GP::Set_Base_Pipeline_Index(int32_t basePipelineIndex){
         m_create_info.basePipelineIndex = basePipelineIndex;
     }


}





