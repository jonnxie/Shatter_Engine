//
// Created by maybe on 2020/12/16.
//

#ifndef SHATTER_ENGINE_SHATTER_DRAWABLE_H
#define SHATTER_ENGINE_SHATTER_DRAWABLE_H

#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>
#include <memory>
#include <iostream>
#include <glm.hpp>
#include <chrono>

#include "../Shatter_Buffer/shatter_buffer_include.h"
#include "../Shatter_Pipeline/shatter_pipeline_include.h"
#include "../Shatter_Model/shatter_model_include.h"
#include "../Shatter_Item/shatter_item.h"

namespace shatter{
    namespace drawable{

        enum class Shatter_Direction{
            X,
            Y,
            Z,
        };

        struct UniformBufferObject {
            glm::mat4 model;
            glm::mat4 view;
            glm::mat4 proj;
        };

        class Shatter_Drawable{
        public:
            bool Init_Drawable(const std::shared_ptr<model::Shatter_Model>& model);
            bool Init_Drawable(const std::shared_ptr<buffer::Shatter_Index_Buffer>& index,
                               const std::shared_ptr<buffer::Shatter_Vertex_Buffer>& vertex);
            Shatter_Drawable();
            virtual ~Shatter_Drawable() = default;


        public:

            virtual void Draw(VkCommandBuffer cb) = 0;

            virtual void Update() = 0;

            virtual void Compute(VkCommandBuffer cb) = 0;

        //    void Set_Delegate(const std::shared_ptr<Shatter_Core>& delegate){m_delegate = delegate;};

            void Set_Pipeline(pipeline::Shatter_GP* gp){m_pipeline = std::move(gp);};

            void Set_Device(VkDevice* device){m_device = device;};

            void Rotate(Shatter_Direction direction, float angle);

            void Rotate(glm::vec3 direction,float angle);

            void Scale(float scale);

            void Scale(glm::vec3 scale);

            void Translate(Shatter_Direction direction,float num);

            void Translate(glm::vec3 translate);


        protected:
            VkDevice* m_device;
            /*
             * 从模型空间变换到世界空间的矩阵，包含旋转，平移，缩放
             */
            glm::mat4 m_matrix;

            /*
             * 顶点缓冲
             */
            std::shared_ptr<buffer::Shatter_Buffer> m_vertex_buffer;

            /*
             * 索引缓冲
             */
            std::shared_ptr<buffer::Shatter_Buffer> m_index_buffer;

            /*
             * 渲染管线以及管线布局
             */
            pipeline::Shatter_GP*   m_pipeline;

            /*
             * 描述符集
             */
            VkDescriptorSet m_descriptorSet;

        //    /*
        //     * 核心委托
        //     */
        //    std::shared_ptr<Shatter_Core> m_delegate;
        };


    };
};


#endif //SHATTER_ENGINE_SHATTER_DRAWABLE_H
