//
// Created by maybe on 2020/12/31.
//

#ifndef SHATTER_ENGINE_SHATTER_BOOM_VS_H
#define SHATTER_ENGINE_SHATTER_BOOM_VS_H

#include "shatter_vs.h"

namespace shatter::shader{

    class Shatter_Boom_VS : public Vertex_Shader{
    public:
        static Shatter_Boom_VS* Create_Boom_VS(const std::string&);
        bool Init_Boom_VS(const std::string&);
    private:

    };


};



#endif //SHATTER_ENGINE_SHATTER_BOOM_VS_H
