//
// Created by maybe on 2020/12/30.
//

#include "shatter_boom_cp.h"
#include "../Shatter_Shader/shatter_shader_include.h"
#include "../Shatter_Render/shatter_render_include.h"
#include <vector>

namespace shatter::pipeline{
    Shatter_Boom_CP* Shatter_Boom_CP::Create_Boom_CP(const std::string& name){
        auto cp = new Shatter_Boom_CP;
        if(cp->Init_Boom_CP(name)){
            return cp;
        }else{
            throw std::runtime_error("create shatter_boom_computerpipeline error!");
        }
    }

    bool Shatter_Boom_CP::Init_Boom_CP(const std::string& name){
        bool val = false;
        do{
            if(!Init_ComputePipeline(render::base_render::Get_Render().Get_Device())) break;
            VkDevice* device = render::base_render::Get_Render().Get_Device();

            auto boom_cs = shader::Shatter_Boom_CS::Create_Boom_CS(name);
            std::array<VkDescriptorSetLayoutBinding, 5> bindings = {(*boom_cs->Get_DesSLB())[0],
                                                                    (*boom_cs->Get_DesSLB())[1],
                                                                    (*boom_cs->Get_DesSLB())[2],
                                                                    (*boom_cs->Get_DesSLB())[3],
                                                                    (*boom_cs->Get_DesSLB())[4]};
            VkDescriptorSetLayoutCreateInfo layoutInfo = {};
            layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
            layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
            layoutInfo.pBindings = bindings.data();

            if (vkCreateDescriptorSetLayout(*device, &layoutInfo, nullptr, m_descriptorsetlayout.data()) !=
                VK_SUCCESS) {
                throw std::runtime_error("failed to create descriptor set layout!");
            }
            VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
            pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
            pipelineLayoutInfo.setLayoutCount = m_descriptorsetlayout.size();
            pipelineLayoutInfo.pSetLayouts = m_descriptorsetlayout.data();

            if (vkCreatePipelineLayout(*device, &pipelineLayoutInfo, nullptr, &m_pipelinelayout) != VK_SUCCESS) {
                throw std::runtime_error("failed to create pipeline layout!");
            }
            Set_PipelineLayout(m_pipelinelayout);

            Set_PipelineShaderStage_CreateInfo(boom_cs->Get_Info());

            Generate_Pipeline();
            val = true;
        }while(false);
        return val;
    }
}




