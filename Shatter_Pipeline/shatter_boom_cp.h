//
// Created by maybe on 2020/12/30.
//

#ifndef SHATTER_ENGINE_SHATTER_BOOM_CP_H
#define SHATTER_ENGINE_SHATTER_BOOM_CP_H

#include "shatter_cp.h"

namespace shatter::pipeline{
    class Shatter_Boom_CP :public Shatter_CP{
    public:
        static Shatter_Boom_CP* Create_Boom_CP(const std::string& name);
        bool Init_Boom_CP(const std::string& name);
    private:
    };

};

#endif //SHATTER_ENGINE_SHATTER_BOOM_CP_H
