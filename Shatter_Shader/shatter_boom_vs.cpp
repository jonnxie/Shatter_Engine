//
// Created by maybe on 2020/12/31.
//

#include "shatter_boom_vs.h"
#include "../Shatter_Render/shatter_render_include.h"
namespace shatter::shader{
    Shatter_Boom_VS* Shatter_Boom_VS::Create_Boom_VS(const std::string& name){
        auto vs = new Shatter_Boom_VS;
        if(vs->Init_Boom_VS(name)){
            return vs;
        }else{
            throw std::runtime_error("create boom vs error!");
        }
    }

    bool Shatter_Boom_VS::Init_Boom_VS(const std::string& name){
    bool val = false;
    do{
        if(!Vertex_Shader::Init_Shader(name,render::base_render::Get_Render().Get_Device())) break;
        m_descriptor_slb_vec.emplace_back(VkDescriptorSetLayoutBinding{0,
                                                                       VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                                                                       1,
                                                                       VK_SHADER_STAGE_VERTEX_BIT,
                                                                       nullptr});
        val = true;
    }while(false);
    return val;
    }
}




