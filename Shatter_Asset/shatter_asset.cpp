//
// Created by maybe on 2020/11/14.
//

#include "shatter_asset.h"
#include "../Shatter_Model/shatter_model_include.h"

namespace shatter::asset{
    bool asset_created = false;

    Shatter_Asset& Shatter_Asset::Get_Asset(){
        static Shatter_Asset asset;
        if(!asset_created) {
            asset_created = true;
            if (!asset.Init_Asset()) {
                throw std::runtime_error("create asset error");
            }
        }
        return asset;
    }
    std::vector<VkDescriptorPoolSize>* Shatter_Asset::Get_DescriptorPool_Size(){
        return &m_dps_vec;
    }

    void Shatter_Asset::update_drawable_num(){
        m_maxSets++;
    }
    void Shatter_Asset::update_Uniform_Buffer(){
        for(auto &i : m_dps_vec){
            if(i.type == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER){
                i.descriptorCount++;
                return;
            }
        }
        m_dps_vec.emplace_back(VkDescriptorPoolSize{VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,1});
    }

    void Shatter_Asset::update_Storage_Buffer(){
        for(auto &i : m_dps_vec){
            if(i.type == VK_DESCRIPTOR_TYPE_STORAGE_BUFFER){
                i.descriptorCount++;
                return;
            }
        }
        m_dps_vec.emplace_back(VkDescriptorPoolSize{VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,1});
    }

    void Shatter_Asset::update_Image_Sampler(){
        for(auto &i : m_dps_vec){
            if(i.type == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER){
                i.descriptorCount++;
                return;
            }
        }
        m_dps_vec.emplace_back(VkDescriptorPoolSize{VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,1});
    }

    Shatter_Asset::Shatter_Asset():
//    m_device{nullptr},
    m_maxSets{0}
    {
        model_map = std::map<std::string,std::shared_ptr<model::Shatter_Model>>();
//        shader_map = std::map<std::string,std::shared_ptr<shader::Shatter_Shader>>();
        m_dps_vec = std::vector<VkDescriptorPoolSize>();
//        for(auto i : model_file_name){
//            update_drawable_num();
//            update_Image_Sampler();
//            update_Uniform_Buffer();
//        }
    }


    bool Shatter_Asset::Init_Asset(){
        bool val = false;
        do{
//            for(const std::string& filename : model_file_name){
//                Push_Model(filename,model::Shatter_Chalet_Model::Create_Chalet_Model(filename));
//            }

//            for(const std::string& filename : vertex_shader_file_name){
//                Push_Shader(filename,shader::Shatter_Chalet_VS::Create_Chalet_VS(filename,device));
//            }
//
//            for(const std::string& filename : fragment_shader_file_name){
//                Push_Shader(filename,shader::Shatter_Chalet_FS::Create_Chalet_FS(filename,device));
//            }

            val = true;
        }while(false);
        return val;
    }

}





