//
// Created by maybe on 2020/11/13.
//

#ifndef VULKAN_TOTURIOL_SHATTER_APP_H
#define VULKAN_TOTURIOL_SHATTER_APP_H

#include "../Shatter_Render/shatter_render_include.h"
#include "../Shatter_Asset/shatter_asset.h"
#include "../Shatter_Item/shatter_item.h"
#include "../Shatter_Model/shatter_model_include.h"
#include "../Shatter_Pipeline/shatter_pipeline_include.h"
#include "../Shatter_Shader/shatter_shader_include.h"
#include "../Shatter_Camera/shatter_camera.h"
#include <iostream>
#include <memory>
#include <map>

namespace shatter::drawable{
    class Shatter_Drawable;
}

namespace shatter{
    namespace app{

        class Shatter_App : public std::enable_shared_from_this<Shatter_App>{
            public:
                static Shatter_App& Get_App();
                Shatter_App(const Shatter_App&) = delete;
                Shatter_App& operator=(const Shatter_App&)=delete;
                ~Shatter_App() = default;
                bool Init_App();
            public:
                static int Get_Screen_Width(){return WIDTH;};
                static int Get_Screen_Height(){return HEIGHT;};
            public:
//                std::shared_ptr<model::Shatter_Model> Get_Model(const std::string& model_name);
//                std::shared_ptr<shader::Shatter_Shader> Get_Shader(const std::string& shader_name);
//                asset::Shatter_Asset Get_Asset(){return m_asset_manager;};
//                void Set_DescriptorPool_Size(std::vector<VkDescriptorPoolSize> dps_vec){m_dps_vec = dps_vec};
//

                void Loop();
                camera::Shatter_Camera* Get_Camera(){return m_camera;};
//                render::base_render* Get_Render(){return m_render;};
                std::vector<drawable::Shatter_Drawable*>* Get_Drawable_Vec();
//                void Cleanup_Drawable();
        private:
            Shatter_App();

            private:
//                /*
//                 * 渲染器
//                 */
//                render::base_render* m_render;
//                /*
//                 * 材质
//                 */
//                asset::Shatter_Asset& m_asset_manager;
                /*
                 * 摄像机
                 */
                camera::Shatter_Camera* m_camera;
                /*
                 * 可被渲染的对象集合
                 */
                std::vector<drawable::Shatter_Drawable*> m_drawable_vec;
            private:
                float lastTime;
                bool showFPS;
                static const int WIDTH = 800;
                static const int HEIGHT = 600;
            };

    }
}

#endif //VULKAN_TOTURIOL_SHATTER_APP_H
