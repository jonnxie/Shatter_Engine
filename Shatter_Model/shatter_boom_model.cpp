//
// Created by maybe on 2020/12/31.
//

#include "shatter_boom_model.h"
#include "../Shatter_Asset/shatter_asset_include.h"
namespace shatter::model{

    std::shared_ptr<Shatter_Boom_Model> Shatter_Boom_Model::Create_Boom_Model(uint32_t particles_num){
        auto model = std::make_shared<Shatter_Boom_Model>();
        if(model->Init_Boom_Model(particles_num)){
            asset::Shatter_Asset::Get_Asset().update_drawable_num();
            asset::Shatter_Asset::Get_Asset().update_drawable_num();
            {
                asset::Shatter_Asset::Get_Asset().update_Uniform_Buffer();
                asset::Shatter_Asset::Get_Asset().update_Storage_Buffer();
                asset::Shatter_Asset::Get_Asset().update_Storage_Buffer();
                asset::Shatter_Asset::Get_Asset().update_Storage_Buffer();
                asset::Shatter_Asset::Get_Asset().update_Storage_Buffer();
                asset::Shatter_Asset::Get_Asset().update_Storage_Buffer();
            }
            return model;
        }else{
            throw std::runtime_error("create boom_model error!");
        }
    }

    bool Shatter_Boom_Model::Init_Boom_Model(uint32_t particles_num){
        bool val = false;
        do{
            m_particles_num = particles_num;
            m_position_vec.resize(particles_num);
            m_temperature_vec.resize(particles_num);
            /*
             * 位置
             */
            offset_vec.emplace_back(0);
            size_vec.emplace_back(sizeof(glm::vec3) * m_particles_num);

            /*
             * 速度
             */
            offset_vec.emplace_back(size_vec[0]);
            size_vec.emplace_back(sizeof(glm::vec3) * m_particles_num);

            /*
             * 力
             */
            offset_vec.emplace_back(offset_vec[1] + size_vec[1]);
            size_vec.emplace_back(sizeof(glm::vec3) * m_particles_num);

            /*
             * 密度
             */
            offset_vec.emplace_back(offset_vec[2] + size_vec[2]);
            size_vec.emplace_back(sizeof(float) * m_particles_num);

            /*
             * 温度
             */
            offset_vec.emplace_back(offset_vec[3] + size_vec[3]);
            size_vec.emplace_back(sizeof(float) * m_particles_num);

            m_buffer_size = std::accumulate(size_vec.begin(),size_vec.end(),0);

            for (auto i = 0, x = 0, y = 0, z = 0; i < particles_num; i++)
            {
                m_position_vec[i].x = -0.5 + 2 * PARTICLE_RADIUS * x;
                m_position_vec[i].y = 0.5 - 2 * PARTICLE_RADIUS * y;
                m_position_vec[i].z = 0.5 - 2 * PARTICLE_RADIUS * z;
                /*
                 * 温度暂定200℃
                 */
                m_temperature_vec[i] = 200;
                x++;
                if (x >= 10)
                {
                    x = 0;
                    y++;
                    if (y >= 10)
                    {
                        y = 0;
                        z++;
                    }
                }
            }

            val = true;
        }while(false);
        return val;
    }

    Shatter_Boom_Model::Shatter_Boom_Model(){
        m_position_vec = std::vector<glm::vec3>();
        m_buffer_size = 0;
        m_particles_num = 0;
        size_vec = std::vector<uint64_t>();
        offset_vec = std::vector<uint64_t>();
        m_temperature_vec = std::vector<float>();
        m_type = Model_Type::Boom_Model;
    }

    uint64_t Shatter_Boom_Model::Get_Model_Buffer_Size() const{
        return m_buffer_size;
    }

}





