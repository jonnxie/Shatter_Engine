//
// Created by maybe on 2020/11/24.
//

#include "shatter_vs.h"

namespace shatter::shader{

//    std::shared_ptr<Vertex_Shader> Vertex_Shader::Create_Vertex_Shader(const std::string& filename,VkDevice* device){
//        auto shader = std::make_shared<Vertex_Shader>();
//        if(shader != nullptr && shader->Init_Shader(filename,device)){
//            return shader;
//        }else{
//            throw std::runtime_error("shader create error");
//        }
//    }

//    Vertex_Shader::Vertex_Shader()
//    {
//
//    }

    bool Vertex_Shader::Init_Shader(const std::string& filename,VkDevice* device){
        bool val =false;
        do {
            auto shader_code = readFile(filename);
            Set_Device(device);
            m_shader_module = ::createShaderModule(shader_code, *m_device);

            m_shader_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            m_shader_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
            m_shader_info.module = m_shader_module;
            m_shader_info.pName = "main";
            val = true;
        }while(false);
        return val;
    }


}





