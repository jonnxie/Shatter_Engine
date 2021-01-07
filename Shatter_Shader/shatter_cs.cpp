//
// Created by maybe on 2020/12/30.
//

#include "shatter_cs.h"

namespace shatter::shader{

//    Computer_Shader::Computer_Shader(){
//
//    }

    bool Computer_Shader::Init_Shader(const std::string& filename,VkDevice* device){
        bool val = false;
        do{

            auto shader_code = readFile(filename);
            Set_Device(device);
            m_shader_module = ::createShaderModule(shader_code,*device);

            m_shader_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            m_shader_info.stage = VK_SHADER_STAGE_COMPUTE_BIT;
            m_shader_info.module = m_shader_module;
            m_shader_info.pName = "main";
            val = true;
        }while(false);
        return val;
    }


}



