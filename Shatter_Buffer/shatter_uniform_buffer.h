//
// Created by maybe on 2020/12/2.
//

#ifndef SHATTER_ENGINE_SHATTER_UNIFORM_BUFFER_H
#define SHATTER_ENGINE_SHATTER_UNIFORM_BUFFER_H

#include "shatter_buffer.h"
//#include "../Shatter_Model/shatter_model_include.h"

namespace shatter{
    namespace buffer{

        class Shatter_Uniform_Buffer : public Shatter_Buffer {
        public:
            static std::shared_ptr<Shatter_Uniform_Buffer> Create_Uniform_Buffer(VkDevice* device,
                                                                                VkDeviceSize size);
            Shatter_Uniform_Buffer();
            ~Shatter_Uniform_Buffer() = default;
            bool Init_Uniform_Buffer(VkDeviceSize size);
        public:
            VkDeviceSize Get_Uniform_Size(){return Shatter_Buffer::Get_Buffer_Size();};
        protected:
        };

    };
};




#endif //SHATTER_ENGINE_SHATTER_UNIFORM_BUFFER_H
