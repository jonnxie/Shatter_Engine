//
// Created by maybe on 2020/12/31.
//

#ifndef SHATTER_ENGINE_SHATTER_BOOM_GP_H
#define SHATTER_ENGINE_SHATTER_BOOM_GP_H

#include "shatter_gp.h"

namespace shatter::pipeline{

    class Shatter_Boom_GP : public Shatter_GP{
    public:
        static Shatter_Boom_GP* Create_Boom_GP();
        bool Init_Boom_GP();
    private:

    };

};

#endif //SHATTER_ENGINE_SHATTER_BOOM_GP_H
