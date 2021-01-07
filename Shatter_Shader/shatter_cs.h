//
// Created by maybe on 2020/12/30.
//

#ifndef SHATTER_ENGINE_SHATTER_CS_H
#define SHATTER_ENGINE_SHATTER_CS_H

#include "shatter_shader.h"

namespace shatter::shader{

    class Computer_Shader : public Shatter_Shader{
    public:
    //    Computer_Shader();
    public:
        bool Init_Shader(const std::string&,VkDevice*);
    private:

    };

};


#endif //SHATTER_ENGINE_SHATTER_CS_H
