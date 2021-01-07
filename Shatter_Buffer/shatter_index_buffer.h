//
// Created by maybe on 2020/12/5.
//

#ifndef SHATTER_ENGINE_SHATTER_INDEX_BUFFER_H
#define SHATTER_ENGINE_SHATTER_INDEX_BUFFER_H

#include "shatter_buffer.h"
//#include "../Shatter_Model/shatter_model_include.h"
#include <memory>

namespace shatter{
    namespace buffer {

        class Shatter_Index_Buffer : public Shatter_Buffer {
        public:
            static std::shared_ptr<Shatter_Index_Buffer> Create_Index_Buffer(VkDevice* device,
                                                                             const std::shared_ptr<model::Shatter_Model>& model);
            Shatter_Index_Buffer() = default;
            ~Shatter_Index_Buffer() = default;
            bool Init_Index_Buffer(const std::shared_ptr<model::Shatter_Model>& model);
        private:

        };

    };
};

#endif //SHATTER_ENGINE_SHATTER_INDEX_BUFFER_H
