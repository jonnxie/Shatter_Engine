//
// Created by maybe on 2020/12/30.
//

#include "shatter_boom_cs.h"
#include "../Shatter_Render/shatter_render_include.h"

namespace shatter::shader{

    Shatter_Boom_CS* Shatter_Boom_CS::Create_Boom_CS(const std::string& name){
        auto cs = new Shatter_Boom_CS;
        if(cs->Init_Boom_CS(name)){
            return cs;
        }else{
            throw std::runtime_error("create Shatter_Chalet_VS error!");
        };
    }

    bool Shatter_Boom_CS::Init_Boom_CS(const std::string& name){
        bool val = false;
        do{
            if(!Computer_Shader::Init_Shader(name,render::base_render::Get_Render().Get_Device())) break;
            m_descriptor_slb_vec.emplace_back(VkDescriptorSetLayoutBinding{
                                                      0,
                                                      VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                                      1,
                                                      VK_SHADER_STAGE_COMPUTE_BIT,
                                                      nullptr
                                              });
            m_descriptor_slb_vec.emplace_back(VkDescriptorSetLayoutBinding{
                                                      1,
                                                      VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                                      1,
                                                      VK_SHADER_STAGE_COMPUTE_BIT,
                                                      nullptr
                                              });
            m_descriptor_slb_vec.emplace_back(VkDescriptorSetLayoutBinding{
                                                      2,
                                                      VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                                      1,
                                                      VK_SHADER_STAGE_COMPUTE_BIT,
                                                      nullptr
                                              });
            m_descriptor_slb_vec.emplace_back(VkDescriptorSetLayoutBinding{
                                                      3,
                                                      VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                                      1,
                                                      VK_SHADER_STAGE_COMPUTE_BIT,
                                                      nullptr
                                              });
            m_descriptor_slb_vec.emplace_back(VkDescriptorSetLayoutBinding{
                                                      4,
                                                      VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                                      1,
                                                      VK_SHADER_STAGE_COMPUTE_BIT,
                                                      nullptr
                                              });
            val = true;
        }while(false);
        return val;
    }

}




