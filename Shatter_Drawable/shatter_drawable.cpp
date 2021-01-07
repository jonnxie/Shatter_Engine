//
// Created by maybe on 2020/12/16.
//

#include "shatter_drawable.h"

namespace shatter::drawable{

    bool Shatter_Drawable::Init_Drawable(const std::shared_ptr<model::Shatter_Model>& model)
    {
        auto val = false;
        do{
            m_matrix = glm::mat4(1.0f);

            m_vertex_buffer = buffer::Shatter_Vertex_Buffer::Create_Vertex_Buffer(m_device,model);

            m_index_buffer = buffer::Shatter_Index_Buffer::Create_Index_Buffer(m_device,model);

            val = true;
        }while(false);
        return val;
    }

    bool Shatter_Drawable::Init_Drawable(const std::shared_ptr<buffer::Shatter_Index_Buffer>& index,
                       const std::shared_ptr<buffer::Shatter_Vertex_Buffer>& vertex){
        auto val = false;
        do{
            m_matrix = glm::mat4(1.0f);

            m_vertex_buffer = vertex;
            m_index_buffer  = index;
            val = true;
        }while(false);
        return val;
    }

    Shatter_Drawable::Shatter_Drawable():
    m_device{nullptr},
    m_matrix(),
    m_vertex_buffer{nullptr},
    m_index_buffer{nullptr},
    m_pipeline{nullptr},
    m_descriptorSet{VK_NULL_HANDLE}
    {
    }

    void Shatter_Drawable::Rotate(Shatter_Direction direction, float angle){
        switch (direction) {
            case Shatter_Direction::X:
                Rotate(glm::vec3(1,0,0),angle);
                break;
            case Shatter_Direction::Y:
                Rotate(glm::vec3(0,1,0),angle);
                break;
            case Shatter_Direction::Z:
                Rotate(glm::vec3(0,0,1),angle);
                break;
            default:
                break;
        }
    }

    void Shatter_Drawable::Rotate(glm::vec3 direction,float angle){
        m_matrix = m_matrix * glm::rotate(glm::mat4(0.1f), angle, direction);
    }

    void Shatter_Drawable::Scale(float scale){
        m_matrix = m_matrix * glm::scale(glm::mat4(1.0f),glm::vec3(scale,scale,scale));
    }

    void Shatter_Drawable::Scale(glm::vec3 scale){
        m_matrix = m_matrix * glm::scale(glm::mat4(1.0f),scale);
    }

    void Shatter_Drawable::Translate(Shatter_Direction direction,float num){
        switch (direction) {
            case Shatter_Direction::X:
                Translate(glm::vec3(num,0,0));
                break;
            case Shatter_Direction::Y:
                Translate(glm::vec3(0,num,0));
                break;
            case Shatter_Direction::Z:
                Translate(glm::vec3(0,0,num));
                break;
            default:
                break;
        }
    }

    void Shatter_Drawable::Translate(glm::vec3 translate){
        m_matrix = m_matrix * glm::translate(glm::mat4(1.0f),translate);
    }

}


