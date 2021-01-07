//
// Created by maybe on 2020/12/5.
//

#include "shatter_index_buffer.h"


namespace shatter::buffer{
    std::shared_ptr<Shatter_Index_Buffer> Shatter_Index_Buffer::Create_Index_Buffer(VkDevice* device,
                                                                                    const std::shared_ptr<model::Shatter_Model>& model){
        auto vertex_buffer = std::make_shared<Shatter_Index_Buffer>();
        vertex_buffer->Set_Device(device);
        if(vertex_buffer->Init_Index_Buffer(model)){
            return vertex_buffer;
        }else{
            throw std::runtime_error("create vertex_buffer error!");
        }
    }

    bool Shatter_Index_Buffer::Init_Index_Buffer(const std::shared_ptr<model::Shatter_Model>& model){
        bool val = false;
        do{
//            std::shared_ptr<model::Shatter_Chalet_Model> tmp_model;
            if(model->Get_Type() == model::Model_Type::Boom_Model) {
                val = true;
            }
        }while(false);
        return val;
    }


}

