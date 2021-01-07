//
// Created by maybe on 2020/11/28.
//

#include "shatter_cp.h"
#include "../Shatter_Render/render.h"

namespace shatter::pipeline{


    Shatter_CP::Shatter_CP():
            m_create_info{}
    {

    }
    Shatter_CP::~Shatter_CP(){

    }
    bool Shatter_CP::Init_ComputePipeline(VkDevice* device){
        bool val = false;
        do{
            m_create_info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
            val = true;
        }while(false);
        return val;
    }

    void Shatter_CP::Generate_Pipeline(){
        if (vkCreateComputePipelines(*render::base_render::Get_Render().Get_Device(),
                                     VK_NULL_HANDLE,
                                     1,
                                     &m_create_info,
                                     nullptr, &m_pipeline) !=
            VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics pipeline!");
        }
    }



}








