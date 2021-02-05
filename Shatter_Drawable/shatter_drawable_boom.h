//
// Created by maybe on 2020/12/31.
//

#ifndef SHATTER_ENGINE_SHATTER_DRAWABLE_BOOM_H
#define SHATTER_ENGINE_SHATTER_DRAWABLE_BOOM_H

#include "shatter_drawable.h"
#include "../Shatter_App/shatter_app_include.h"
#include "../Shatter_Input/shatter_input_include.h"
#include <glfw3.h>

namespace shatter{
    namespace drawable {


    class Shatter_Drawable_Boom : public Shatter_Drawable ,public input::Shatter_Input{
    public:
        static Shatter_Drawable_Boom *Create_Drawable_Boom(const std::shared_ptr<model::Shatter_Model> &model,
                                                           pipeline::Shatter_Boom_GP *pipeline,
                                                           std::vector<pipeline::Shatter_Boom_CP *> cp_pipeline);

        bool Init_Drawable_Boom(const std::shared_ptr<model::Shatter_Model> &model);

        void Set_CP(std::vector<pipeline::Shatter_Boom_CP *> cp);

    public:
        void Draw(VkCommandBuffer cb) override;

        void Update() override;

        void Compute(VkCommandBuffer cb) override;

    public:
        void key_event_callback(int key, int action) override;

    private:

        std::vector<pipeline::Shatter_Boom_CP *> m_cp_pipeline;

        //与xy平面夹角
        float alpha = 45;
        //与x轴夹角
        float gamma = 45;

        std::shared_ptr<buffer::Shatter_Uniform_Buffer> m_uniform_buffer;

        uint32_t m_particles_num;

        /*
        * 描述符集,此处描述符集是在绘制管线中使用
        */
        VkDescriptorSet m_descriptorSet_1;
    };

    };
};

#endif //SHATTER_ENGINE_SHATTER_DRAWABLE_BOOM_H
