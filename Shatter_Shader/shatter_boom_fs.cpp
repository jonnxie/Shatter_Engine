//
// Created by maybe on 2020/12/31.
//

#include "shatter_boom_fs.h"
#include "../Shatter_Render/shatter_render_include.h"
namespace shatter::shader{

    Shatter_Boom_FS* Shatter_Boom_FS::Create_Boom_FS(const std::string& name){
        auto fs = new Shatter_Boom_FS;
        if(fs->Init_Boom_FS(name)){
            return fs;
        }else{
            throw std::runtime_error("create boom fs error!");
        }
    }

    bool Shatter_Boom_FS::Init_Boom_FS(const std::string& name){
        bool val = false;
        do{
            if(!Fragment_Shader::Init_Shader(name,render::base_render::Get_Render().Get_Device())) break;
            val = true;
        }while(false);
        return val;
    }

}




