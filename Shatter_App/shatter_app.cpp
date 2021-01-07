//
// Created by maybe on 2020/11/13.
//

#include "shatter_app.h"
#include "../Shatter_Drawable/shatter_drawable_include.h"

namespace shatter::app{
    bool app_created = false;
    Shatter_App& Shatter_App::Get_App(){
        static Shatter_App app;
        if(!app_created) {
            app_created = true;
            if (!app.Init_App()) {
                throw std::runtime_error("create app error!");
            }
        }
        return app;
    }

    bool Shatter_App::Init_App(){
        bool val = false;
        do{
//            m_render = render::base_render::Create_Render();

//            m_asset_manager = asset::Shatter_Asset::Get_Asset(m_render->Get_Device());

            m_camera = new camera::Shatter_Camera();

            val = true;
        }while(false);
        return val;
    }

    Shatter_App::Shatter_App():
    lastTime(0.0),
    showFPS(false),
    m_camera{nullptr}
    {
        m_drawable_vec = std::vector<drawable::Shatter_Drawable*>();
//        m_dps_vec = std::vector<VkDescriptorPoolSize>();
    }
//    Shatter_App::~Shatter_App(){
//        model_map.clear();
//    }

//    std::shared_ptr<model::Shatter_Model> Shatter_App::Get_Model(const std::string& model_name){
//        return m_asset_manager->Get_Model(model_name);
//    }
//
//    std::shared_ptr<shader::Shatter_Shader> Shatter_App::Get_Shader(const std::string& shader_name){
//        return m_asset_manager->Get_Shader(shader_name);
//    }

    void Shatter_App::Loop(){
        while (!glfwWindowShouldClose(render::base_render::Get_Render().Get_Window())) {
            for(auto& i : m_drawable_vec){
                i->Update();
            }
            render::base_render::Get_Render().Loop();
        }
        vkDeviceWaitIdle(*render::base_render::Get_Render().Get_Device());
        for(auto i : m_drawable_vec){
            delete i;
        }
    }

    std::vector<drawable::Shatter_Drawable*>* Shatter_App::Get_Drawable_Vec(){
        return &m_drawable_vec;
    }

//    void Shatter_App::Cleanup_Drawable(){
//        for(auto i : m_drawable_vec){
//            delete i;
//        }
//    }

}





