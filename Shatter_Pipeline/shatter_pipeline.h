//
// Created by maybe on 2020/11/28.
//

#ifndef SHATTER_ENGINE_SHATTER_PIPELINE_H
#define SHATTER_ENGINE_SHATTER_PIPELINE_H

#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>
#include <memory>
#include <iostream>

//#include "../Shatter_Vertex/shatter_vertex.h"
#include "../Shatter_Item/shatter_item.h"


namespace shatter{
    namespace pipeline{


        class Shatter_Pipeline :std::enable_shared_from_this<Shatter_Pipeline>{
        public:
            Shatter_Pipeline();
            ~Shatter_Pipeline();

        public:
            void Set_Pipeline_Device(VkDevice* device){m_device = device;};
            virtual void Generate_Pipeline() = 0;
//            /*
//             * 配置管线布局
//             */
//            void Set_Pipeline_Layout(VkPipelineLayout pipelineLayout);
            VkPipelineLayout Get_Pipeline_Layout(){return m_pipelinelayout;};
            std::vector<VkDescriptorSetLayout> Get_DescriptorSet_Layout(){return m_descriptorsetlayout;};
            VkPipeline Get_Pipeline(){return m_pipeline;};
        protected:
            VkPipelineLayout m_pipelinelayout;
            std::vector<VkDescriptorSetLayout> m_descriptorsetlayout;
            VkPipeline m_pipeline;
            VkDevice* m_device;
            bool generated;
        private:

        };

    };
};




#endif //SHATTER_ENGINE_SHATTER_PIPELINE_H
