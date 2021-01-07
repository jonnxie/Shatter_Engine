//
// Created by maybe on 2020/11/14.
//

#ifndef SHATTER_ENGINE_SHATTER_ASSET_H
#define SHATTER_ENGINE_SHATTER_ASSET_H

#include <vulkan/vulkan.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace shatter::model{
    class Shatter_Model;
}

namespace shatter {

    namespace asset {




        class Shatter_Asset {
        public:
            static Shatter_Asset& Get_Asset();
            Shatter_Asset(const Shatter_Asset&) = delete;
            Shatter_Asset& operator = (const Shatter_Asset&) = delete;
            ~Shatter_Asset() = default;
            bool Init_Asset();
        public:
//            std::shared_ptr<model::Shatter_Model> Get_Model(const std::string& filename){return model_map[filename];};
//
//            void Push_Model(const std::string& name,std::shared_ptr<model::Shatter_Model> model){model_map[name] = std::move(model);};

            std::vector<VkDescriptorPoolSize>* Get_DescriptorPool_Size();

            const uint32_t Get_Set_Num(){return m_maxSets;};

            void update_drawable_num();

            void update_Uniform_Buffer();

            void update_Storage_Buffer();

            void update_Image_Sampler();
        private:

            Shatter_Asset();
        private:
            std::map<std::string,std::shared_ptr<model::Shatter_Model>> model_map;
//            std::map<std::string,std::shared_ptr<shader::Shatter_Shader>> shader_map;
            /*
             * 预先创建的描述符池的描述符数量
             */
            std::vector<VkDescriptorPoolSize> m_dps_vec;

            uint32_t m_maxSets;
//            VkDevice* m_device;
        };

    }

}
#endif //SHATTER_ENGINE_SHATTER_ASSET_H
