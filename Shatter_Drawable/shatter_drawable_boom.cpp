//
// Created by maybe on 2020/12/31.
//

#include "shatter_drawable_boom.h"

namespace shatter::drawable{

    Shatter_Drawable_Boom* Shatter_Drawable_Boom::Create_Drawable_Boom(const std::shared_ptr<model::Shatter_Model>& model,
                                                                        pipeline::Shatter_Boom_GP* pipeline,
                                                                        std::vector<pipeline::Shatter_Boom_CP*> cp_pipeline)
    {
        auto drawable = new Shatter_Drawable_Boom;
        drawable->Set_Pipeline(pipeline);
        drawable->Set_CP(std::move(cp_pipeline));
        if(drawable->Init_Drawable_Boom(model)){
            return drawable;
        }else{
            throw std::runtime_error("create drawable boom!");
        }
    }

    bool Shatter_Drawable_Boom::Init_Drawable_Boom(const std::shared_ptr<model::Shatter_Model>& model){
        bool val = false;
        do{
            if(!Shatter_Drawable::Init_Drawable(model)) break;
            m_particles_num = model->Get_Vertex_Number();
            std::vector<VkDescriptorSetLayout> sl_vec = m_cp_pipeline[0]->Get_DescriptorSet_Layout();
            render::base_render::Get_Render().AllocateDescriptorSets(sl_vec,&m_descriptorSet);
            auto tmp_model = std::dynamic_pointer_cast<model::Shatter_Boom_Model>(model);
            std::vector<uint64_t>* size_vec = tmp_model->Get_Size_Vec();
            std::vector<uint64_t>* offset_vec = tmp_model->Get_Offset_Vec();

            VkDescriptorBufferInfo descriptor_buffer_infos[]
                    {
                            {
                                    m_vertex_buffer->Get_Buffer(),
                                    (*offset_vec)[0],
                                    (*size_vec)[0]
                            },
                            {
                                    m_vertex_buffer->Get_Buffer(),
                                    (*offset_vec)[1],
                                    (*size_vec)[1]
                            },
                            {
                                    m_vertex_buffer->Get_Buffer(),
                                    (*offset_vec)[2],
                                    (*size_vec)[2]
                            },
                            {
                                    m_vertex_buffer->Get_Buffer(),
                                    (*offset_vec)[3],
                                    (*size_vec)[3]
                            },
                            {
                                    m_vertex_buffer->Get_Buffer(),
                                    (*offset_vec)[4],
                                    (*size_vec)[4]
                            }
                    };

            VkWriteDescriptorSet write_descriptor_sets[]
                    {
                            {
                                    VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                                    nullptr,
                                    m_descriptorSet,
                                    0,
                                    0,
                                    1,
                                    VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                    nullptr,
                                    descriptor_buffer_infos,
                                    nullptr
                            },
                            {
                                    VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                                    nullptr,
                                    m_descriptorSet,
                                    0,
                                    1,
                                    1,
                                    VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                    nullptr,
                                    descriptor_buffer_infos + 1,
                                    nullptr
                            },
                            {
                                    VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                                    nullptr,
                                    m_descriptorSet,
                                    0,
                                    2,
                                    1,
                                    VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                    nullptr,
                                    descriptor_buffer_infos + 2,
                                    nullptr
                            },
                            {
                                    VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                                    nullptr,
                                    m_descriptorSet,
                                    0,
                                    3,
                                    1,
                                    VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                    nullptr,
                                    descriptor_buffer_infos + 3,
                                    nullptr
                            },
                            {
                                    VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                                    nullptr,
                                    m_descriptorSet,
                                    0,
                                    4,
                                    1,
                                    VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                                    nullptr,
                                    descriptor_buffer_infos + 4,
                                    nullptr
                            }
                    };
            vkUpdateDescriptorSets(*render::base_render::Get_Render().Get_Device(),
                                   5,
                                   write_descriptor_sets,
                                   0,
                                   nullptr);


            render::base_render::Get_Render().AllocateDescriptorSets(m_pipeline->Get_DescriptorSet_Layout(),
                                                                     &m_descriptorSet_1);
            m_uniform_buffer = buffer::Shatter_Uniform_Buffer::Create_Uniform_Buffer(render::base_render::Get_Render().Get_Device(),
                                                                                     sizeof(UniformBufferObject));

            VkDescriptorBufferInfo bufferInfo = {};
            bufferInfo.buffer = m_uniform_buffer->Get_Buffer();
            bufferInfo.offset = 0;
            bufferInfo.range = sizeof(UniformBufferObject);

            std::array<VkWriteDescriptorSet, 1> descriptorWrites = {};

            descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[0].dstSet = m_descriptorSet_1;
            descriptorWrites[0].dstBinding = 0;
            descriptorWrites[0].dstArrayElement = 0;
            descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrites[0].descriptorCount = 1;
            descriptorWrites[0].pBufferInfo = &bufferInfo;

            vkUpdateDescriptorSets(*render::base_render::Get_Render().Get_Device(),
                                   static_cast<uint32_t>(descriptorWrites.size()),
                                   descriptorWrites.data(),
                                   0,
                                   nullptr);

            val = true;
        }while(false);
        return val;
    }

    void Shatter_Drawable_Boom::Set_CP(std::vector<pipeline::Shatter_Boom_CP*> cp){
        m_cp_pipeline = std::move(cp);
    }

    void Shatter_Drawable_Boom::Draw(VkCommandBuffer cb){
        vkCmdBindPipeline(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline->Get_Pipeline());

        VkDeviceSize offsets = 0;
        VkBuffer bf = m_vertex_buffer->Get_Buffer();
        vkCmdBindVertexBuffers(cb, 0, 1, &bf, &offsets);
        vkCmdBindDescriptorSets(cb,
                                VK_PIPELINE_BIND_POINT_GRAPHICS,
                                m_pipeline->Get_Pipeline_Layout(),
                                0,
                                1,
                                &m_descriptorSet_1,
                                0,
                                nullptr);
        vkCmdDraw(cb, m_particles_num, 1, 0, 0);
    }


    void Shatter_Drawable_Boom::Update(){
        UniformBufferObject ubo = {};
        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time =
                std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0f;

        ubo.model = m_matrix;
        ubo.view = glm::lookAt(glm::vec3( 2.0f,
                                         2.0f,
                                         2.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.proj = glm::perspective(glm::radians(45.0f),
                                    render::base_render::Get_Render().Get_Extent2D().width /
                                    (float) render::base_render::Get_Render().Get_Extent2D().height,
                                    0.1f, 10.0f);
        ubo.proj[1][1] *= -1;

        void *data;
        vkMapMemory(*render::base_render::Get_Render().Get_Device(),
                    m_uniform_buffer->Get_Memory(),
                    0,
                    sizeof(ubo),
                    0, &data);
        memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(*render::base_render::Get_Render().Get_Device(), m_uniform_buffer->Get_Memory());
    }

    void Shatter_Drawable_Boom::Compute(VkCommandBuffer cb){
        vkCmdBindDescriptorSets(cb,
                                VK_PIPELINE_BIND_POINT_COMPUTE,
                                m_cp_pipeline[0]->Get_Pipeline_Layout(),
                                0,
                                1,
                                &m_descriptorSet,
                                0,
                                nullptr);
        vkCmdBindPipeline(cb,
                          VK_PIPELINE_BIND_POINT_COMPUTE,
                          m_cp_pipeline[0]->Get_Pipeline());
        vkCmdDispatch(cb, m_particles_num, 1, 1);
        vkCmdPipelineBarrier(cb,
                             VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
                             VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
                             0,
                             0,
                             nullptr,
                             0,
                             nullptr,
                             0,
                             nullptr);


        vkCmdBindDescriptorSets(cb,
                                VK_PIPELINE_BIND_POINT_COMPUTE,
                                m_cp_pipeline[1]->Get_Pipeline_Layout(),
                                0,
                                1,
                                &m_descriptorSet,
                                0,
                                nullptr);
        vkCmdBindPipeline(cb, VK_PIPELINE_BIND_POINT_COMPUTE, m_cp_pipeline[1]->Get_Pipeline());
        vkCmdDispatch(cb, m_particles_num, 1, 1);
        vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 0, nullptr);


        vkCmdBindDescriptorSets(cb,
                                VK_PIPELINE_BIND_POINT_COMPUTE,
                                m_cp_pipeline[2]->Get_Pipeline_Layout(),
                                0,
                                1,
                                &m_descriptorSet,
                                0,
                                nullptr);
        vkCmdBindPipeline(cb, VK_PIPELINE_BIND_POINT_COMPUTE, m_cp_pipeline[2]->Get_Pipeline());
        vkCmdDispatch(cb, m_particles_num, 1, 1);
        vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 0, nullptr);

    }


}




