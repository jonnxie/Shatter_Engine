//
// Created by maybe on 2020/11/24.
//

#include "shatter_fs.h"


namespace shatter::shader{

//    std::shared_ptr<Fragment_Shader> Fragment_Shader::Create_Fragment_Shader(const std::string& filename,VkDevice* device){
//        auto shader = std::make_shared<Fragment_Shader>();
//        if(shader != nullptr && shader->Init_Shader(filename,device)){
//            return shader;
//        }else{
//            throw std::runtime_error("shader create error");
//        }
//    }

//    Fragment_Shader::Fragment_Shader(){
//    }
    bool Fragment_Shader::Init_Shader(const std::string& filename,VkDevice* device){
        bool val = false;
        do{
            auto shader_code = readFile(filename);
            Set_Device(device);
            m_shader_module = ::createShaderModule(shader_code,*device);

            m_shader_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            m_shader_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
            m_shader_info.module = m_shader_module;
            m_shader_info.pName = "main";
        val = true;
        }while(false);
        return val;
    }


}




