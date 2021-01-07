//
// Created by maybe on 2020/12/31.
//

#ifndef SHATTER_ENGINE_SHATTER_BOOM_MODEL_H
#define SHATTER_ENGINE_SHATTER_BOOM_MODEL_H

#include "shatter_model.h"
#include <numeric>

#define PARTICLE_RADIUS 0.05f

namespace shatter::model{

    class Shatter_Boom_Model : public Shatter_Model{
    public:
        static std::shared_ptr<Shatter_Boom_Model> Create_Boom_Model(uint32_t particles_num);
        bool Init_Boom_Model(uint32_t particles_num);
        Shatter_Boom_Model();
        ~Shatter_Boom_Model() = default;
    public:
        VkDeviceSize Get_Model_Vertex_Size() override {return sizeof(glm::vec3) * m_position_vec.size();};
        uint64_t Get_Model_Buffer_Size() const;
        VkDeviceSize Get_Model_Index_Size() override {return 0;};
        uint32_t Get_Vertex_Number() override {return m_position_vec.size();};
        uint32_t Get_Index_Number() override {return 0;};
        uint32_t Get_Particles_Num() const {return m_particles_num;};
        std::vector<glm::vec3>* Get_Model_Vec(){return &m_position_vec;};
        std::vector<float>* Get_Temperature_Vec(){return &m_temperature_vec;};
        std::vector<uint64_t>* Get_Size_Vec(){return &size_vec;};
        std::vector<uint64_t>* Get_Offset_Vec(){return &offset_vec;};
    private:
        std::vector<glm::vec3> m_position_vec;
        std::vector<float> m_temperature_vec;
        std::vector<uint64_t> size_vec;
        std::vector<uint64_t> offset_vec;
        uint64_t m_buffer_size;
        uint32_t m_particles_num;
    };

};

#endif //SHATTER_ENGINE_SHATTER_BOOM_MODEL_H
