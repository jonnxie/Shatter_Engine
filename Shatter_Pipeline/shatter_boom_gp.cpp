//
// Created by maybe on 2020/12/31.
//

#include "shatter_boom_gp.h"
#include "../Shatter_Shader/shatter_shader_include.h"
#include "../Shatter_Render/shatter_render_include.h"

namespace shatter::pipeline{

    Shatter_Boom_GP* Shatter_Boom_GP::Create_Boom_GP(){
        auto gp = new Shatter_Boom_GP;
        if(gp->Init_Boom_GP()){
            return gp;
        }else{
            throw std::runtime_error("create boom_gp error!");
        }
    }

    bool Shatter_Boom_GP::Init_Boom_GP(){
        bool val = false;
        do{
            if(!Init_GraphicsPipeline(render::base_render::Get_Render().Get_Device())){
                break;
            }

            auto boom_vs = shader::Shatter_Boom_VS::Create_Boom_VS("../shaders/vert.spv");
            auto boom_fs = shader::Shatter_Boom_FS::Create_Boom_FS("../shaders/frag.spv");
//            std::vector<VkPipelineShaderStageCreateInfo> ssci_vec;
//            ssci_vec.push_back(boom_vs->Get_Info());
//            ssci_vec.push_back(boom_fs->Get_Info());
            /* ShaderStageCreateInfo*/
            VkPipelineShaderStageCreateInfo shaderStages[] = {boom_vs->Get_Info(),boom_fs->Get_Info()};
            m_create_info.stageCount = 2;
            m_create_info.pStages = shaderStages;


            /*VertexInputStateCreateInfo*/
            VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
            vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

            VkVertexInputBindingDescription bindingDescription{
                    0,
                    sizeof(glm::vec3),
                    VK_VERTEX_INPUT_RATE_VERTEX
            };

            VkVertexInputAttributeDescription attributeDescriptions{
                    0,
                    0,
                    VK_FORMAT_R32G32_SFLOAT,
                    0
            };

            vertexInputInfo.vertexBindingDescriptionCount = 1;
            vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
            vertexInputInfo.vertexAttributeDescriptionCount = 1;
            vertexInputInfo.pVertexAttributeDescriptions = &attributeDescriptions;

            Set_Vertex_Input_Info(&vertexInputInfo);


            /*InputAssemblyStateCreateInfo*/
            VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
            inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
            inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
            inputAssembly.primitiveRestartEnable = VK_FALSE;
            Set_Assembly_State(&inputAssembly);


            /*ViewportStateCreateInfo*/
            VkViewport viewport = {};
            viewport.x = 0.0f;
            viewport.y = 0.0f;
            viewport.width = (float) render::base_render::Get_Render().Get_Extent2D().width;
            viewport.height = (float) render::base_render::Get_Render().Get_Extent2D().height;
            viewport.minDepth = 0.0f;
            viewport.maxDepth = 1.0f;

            VkRect2D scissor = {};
            scissor.offset = {0, 0};
            scissor.extent = render::base_render::Get_Render().Get_Extent2D();

            VkPipelineViewportStateCreateInfo viewportState = {};
            viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
            viewportState.viewportCount = 1;
            viewportState.pViewports = &viewport;
            viewportState.scissorCount = 1;
            viewportState.pScissors = &scissor;
            Set_Viewport_State(&viewportState);


            /*RasterizationStateCreateInfo*/
            VkPipelineRasterizationStateCreateInfo rasterizer = {};
            rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
            rasterizer.depthClampEnable = VK_FALSE;
            rasterizer.rasterizerDiscardEnable = VK_FALSE;
            rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
            rasterizer.lineWidth = 1.0f;
            rasterizer.cullMode = VK_CULL_MODE_NONE;
            rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
            rasterizer.depthBiasEnable = VK_FALSE;
            Set_Rasterization_State(&rasterizer);


            /*MultisampleStateCreateInfo*/
            VkPipelineMultisampleStateCreateInfo multisampling = {};
            multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
            multisampling.sampleShadingEnable = VK_FALSE;
            multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
            Set_Multisample_State(&multisampling);


            /*DepthStencilStateCreateInfo*/
            VkPipelineDepthStencilStateCreateInfo depthStencil = {};
            depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
            depthStencil.depthTestEnable = VK_TRUE;
            depthStencil.depthWriteEnable = VK_TRUE;
            depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
            depthStencil.depthBoundsTestEnable = VK_FALSE;
            depthStencil.stencilTestEnable = VK_FALSE;
            Set_Depth_Stencil_State(&depthStencil);


            /*ColorBlendStateCreateInfo*/
            VkPipelineColorBlendAttachmentState colorBlendAttachment =
            {
                    VK_FALSE,
                     VK_BLEND_FACTOR_ONE,
                     VK_BLEND_FACTOR_ZERO,
                     VK_BLEND_OP_ADD,
                     VK_BLEND_FACTOR_ONE,
                     VK_BLEND_FACTOR_ZERO,
                     VK_BLEND_OP_ADD,
                     VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
            };
//                colorBlendAttachment.colorWriteMask =
//                        VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
//                        VK_COLOR_COMPONENT_A_BIT;
//                colorBlendAttachment.blendEnable = VK_FALSE;

            VkPipelineColorBlendStateCreateInfo colorBlending = {};
            colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
            colorBlending.logicOpEnable = VK_FALSE;
            colorBlending.logicOp = VK_LOGIC_OP_COPY;
            colorBlending.attachmentCount = 1;
            colorBlending.pAttachments = &colorBlendAttachment;
            colorBlending.blendConstants[0] = 0.0f;
            colorBlending.blendConstants[1] = 0.0f;
            colorBlending.blendConstants[2] = 0.0f;
            colorBlending.blendConstants[3] = 0.0f;
            Set_Color_Blend_State(&colorBlending);


            /*PipelineLayoutCreateInfo*/
            VkDescriptorSetLayoutBinding slb = (*boom_vs->Get_DesSLB())[0];
//            std::array<VkDescriptorSetLayoutBinding, 1> bindings = {*(boom_vs->Get_DesSLB())->data()};
            VkDescriptorSetLayoutCreateInfo layoutInfo = {};
            layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
            layoutInfo.bindingCount = 1;
            layoutInfo.pBindings = &slb;

            if (vkCreateDescriptorSetLayout(*(render::base_render::Get_Render().Get_Device()),
                                            &layoutInfo,
                                            nullptr,
                                            m_descriptorsetlayout.data()) != VK_SUCCESS) {
                throw std::runtime_error("failed to create descriptor set layout!");
            }

            VkPipelineLayoutCreateInfo pipelineLayoutInfo = {
                    VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                    nullptr,
                    0,
                    1,
                    m_descriptorsetlayout.data(),
                    0,
                    nullptr};

            if (vkCreatePipelineLayout(*render::base_render::Get_Render().Get_Device(),
                                       &pipelineLayoutInfo,
                                       nullptr,
                                       &m_pipelinelayout) != VK_SUCCESS) {
                throw std::runtime_error("failed to create pipeline layout!");
            }
            Set_PipelineLayout(m_pipelinelayout);



            Set_Render_Pass(render::base_render::Get_Render().Get_RenderPass());
            Set_Subpass(0);
            Set_Base_Pipeline_Handle(VK_NULL_HANDLE);


            Generate_Pipeline();
            val = true;
        }while(false);
        return val;
    }


}






