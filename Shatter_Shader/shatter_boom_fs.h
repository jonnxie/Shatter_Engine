//
// Created by maybe on 2020/12/31.
//

#ifndef SHATTER_ENGINE_SHATTER_BOOM_FS_H
#define SHATTER_ENGINE_SHATTER_BOOM_FS_H

#include "shatter_fs.h"

namespace shatter::shader{
    class Shatter_Boom_FS : public Fragment_Shader{
    public:
        static Shatter_Boom_FS* Create_Boom_FS(const std::string&);
        bool Init_Boom_FS(const std::string&);
    private:

    };
};


#endif //SHATTER_ENGINE_SHATTER_BOOM_FS_H
