//
// Created by maybe on 2020/12/30.
//

#ifndef SHATTER_ENGINE_SHATTER_BOOM_CS_H
#define SHATTER_ENGINE_SHATTER_BOOM_CS_H

#include "shatter_cs.h"

namespace shatter::shader{

    class Shatter_Boom_CS : public Computer_Shader{
    public:
        static Shatter_Boom_CS* Create_Boom_CS(const std::string&);
        bool Init_Boom_CS(const std::string&);
    private:
    };


};


#endif //SHATTER_ENGINE_SHATTER_BOOM_CS_H
