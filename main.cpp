#include <iostream>
#include <vector>
#include "Shatter_Render/shatter_render_include.h"
#include "Shatter_App/shatter_app_include.h"
#include "Shatter_Pipeline/shatter_pipeline_include.h"
#include "Shatter_Drawable/shatter_drawable_include.h"

int main() {
    shatter::app::Shatter_App& app = shatter::app::Shatter_App::Get_App();
    std::shared_ptr<shatter::model::Shatter_Boom_Model> boom_model = shatter::model::Shatter_Boom_Model::Create_Boom_Model(1000);
    shatter::render::base_render& render = shatter::render::base_render::Get_Render();
    auto pipeline = shatter::pipeline::Shatter_Boom_GP::Create_Boom_GP();
    std::vector<shatter::pipeline::Shatter_Boom_CP*> cp_vec;
    cp_vec.push_back(shatter::pipeline::Shatter_Boom_CP::Create_Boom_CP("../shaders/compute_density.spv"));
    cp_vec.push_back(shatter::pipeline::Shatter_Boom_CP::Create_Boom_CP("../shaders/compute_force.spv"));
    cp_vec.push_back(shatter::pipeline::Shatter_Boom_CP::Create_Boom_CP("../shaders/integrate.spv"));

    app.Get_Drawable_Vec()->emplace_back(shatter::drawable::Shatter_Drawable_Boom::Create_Drawable_Boom
    (boom_model,
     pipeline,
     cp_vec
     ));
    render.Add_Drawable((*app.Get_Drawable_Vec())[0]);
    render.Create_Command_Buffer();
    try {
        app.Loop();
        delete pipeline;
        for(auto i : cp_vec){
            delete i;
        }
        shatter::render::base_render::Get_Render().Cleanup();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}