//
// Created by maybe on 2020/12/19.
//

#ifndef SHATTER_ENGINE_SHATTER_TEXTURE_H
#define SHATTER_ENGINE_SHATTER_TEXTURE_H

#include "shatter_buffer.h"

#include <string>

namespace shatter {
    namespace buffer {

        class Shatter_Texture : public Shatter_Buffer {
        public:
            static std::shared_ptr<Shatter_Texture> Create_Texture(VkDevice *device,
                                                                   const std::string &texture_name);

            Shatter_Texture();

            ~Shatter_Texture();

            bool Init_Texture(const std::string &texture_name);

        public:
            static VkImageView
            Create_ImageView(VkDevice *device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

            static void Create_Image(VkDevice *device,
                                     uint32_t width,
                                     uint32_t height,
                                     VkFormat format,
                                     VkImageTiling tiling,
                                     VkImageUsageFlags usage,
                                     VkMemoryPropertyFlags properties,
                                     VkImage &image,
                                     VkDeviceMemory &imageMemory);

            static void Transition_ImageLayout(VkImage image,
                                               VkFormat format,
                                               VkImageLayout oldLayout,
                                               VkImageLayout newLayout);

        protected:
            void createImage(uint32_t width,
                             uint32_t height,
                             VkFormat format,
                             VkImageTiling tiling,
                             VkImageUsageFlags usage,
                             VkMemoryPropertyFlags properties,
                             VkImage &image,
                             VkDeviceMemory &imageMemory);

            void transitionImageLayout(VkImage image,
                                       VkFormat format,
                                       VkImageLayout oldLayout,
                                       VkImageLayout newLayout);

            void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

            void createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

            void createTextureSampler();

        public:
            VkImageView Get_ImageView() { return m_textureImageView; };

            VkSampler Get_Sampler() { return m_textureSampler; };
        private:
            VkImage m_textureImage;
            VkImageView m_textureImageView;
            VkSampler m_textureSampler;
        };

    };
};




#endif //SHATTER_ENGINE_SHATTER_TEXTURE_H
