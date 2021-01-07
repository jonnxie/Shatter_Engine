//
// Created by maybe on 2020/11/21.
//

#ifndef VULKAN_TOTURIOL_SHATTER_RENDER_H
#define VULKAN_TOTURIOL_SHATTER_RENDER_H

#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtx/hash.hpp>
#include <vector>
#include <fstream>
#include <glm.hpp>
#include <array>
#include <unordered_map>
#include "../Shatter_Model/shatter_model_include.h"
#include "../Shatter_App/shatter_app_include.h"
#include "../Shatter_Item/shatter_item.h"


//#ifdef NDEBUG
//const bool enableValidationLayers = false;
//#else
const bool enableValidationLayers = true;
//#endif

namespace shatter::drawable{
    class Shatter_Drawable;
}


namespace shatter{
    namespace render {


//        typedef std::function<void(VkCommandBuffer)> cm;

        class base_render {
        public:
            static base_render& Get_Render();

            base_render(const base_render&) = delete;
            base_render& operator = (const base_render&) = delete;

            void Init();

            void Loop();

            void Cleanup();

        private:
            base_render() = default;
            ~base_render() = default;
            void Init_Window();

            void Init_Vulkan();

            void Create_Instance();

            void Setup_DebugCallback();

            void Create_Surface();

            void Pick_PhysicalDevice();

            void Create_LogicalDevice();

            void Create_SwapChain();

            void Create_ImageViews();

            void Create_RenderPass();

            void Create_Framebuffers();

            void Create_GraphicsCommandPool();

            void Create_ComputeCommandPool();

            void Create_DepthResources();

            void Create_DescriptorPool();

            void Create_GraphicsCommandBuffers();

            void Create_ComputeCommandBuffer();

            void Create_Semaphores();

            void Recreate_SwapChain();

            void Cleanup_SwapChain();

            void Draw();

            SwapChainSupportDetails Query_SwapChain_Support(VkPhysicalDevice device);

            VkFormat Find_Supported_Format(const std::vector<VkFormat> &candidates, VkImageTiling tiling,
                                           VkFormatFeatureFlags features);

            VkFormat Find_Depth_Format();

            bool isDeviceSuitable(VkPhysicalDevice device);

            bool Check_DeviceExtension_Support(VkPhysicalDevice device);

            QueueFamilyIndices Find_QueueFamilies(VkPhysicalDevice device);

            std::vector<const char *> Get_RequiredExtensions();



            bool Check_ValidationLayer_Support();

        public:
            //        static bool hasStencilComponent(VkFormat format);
            VkCommandBuffer beginSingleTimeCommands() ;
            void endSingleTimeCommands(VkCommandBuffer commandBuffer) ;
            uint32_t Find_MemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) ;
            VkRenderPass Get_RenderPass() {return renderPass;};
            VkExtent2D Get_Extent2D() {return swapChainExtent;};
//            glm::mat4 Get_View() {return app::Shatter_App::Get_App().Get_Camera()->Get_View();};
//            glm::mat4 Get_Proj() {return app::Shatter_App::Get_App().Get_Camera()->Get_Proj();};
            void AllocateDescriptorSets(const std::vector<VkDescriptorSetLayout>& des_set_layout,
                                        VkDescriptorSet* set);
            VkDevice* Get_Device(){return &device;};
            //        void Register_Command(cm command);
            void Add_Drawable(drawable::Shatter_Drawable* drawable);
            void Create_Command_Buffer();
            GLFWwindow* Get_Window(){return window;};
        public:
            static VKAPI_ATTR VkBool32 VKAPI_CALL
            debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj,
                          size_t location, int32_t code, const char *layerPrefix, const char *msg, void *userData) {
                std::cerr << "validation layer: " << msg << std::endl;

                return VK_FALSE;
            }

        public:
            static void onWindowResized(GLFWwindow *window, int width, int height);

        private:
            //        std::shared_ptr<app::Shatter_App> app;
//            std::vector<cm> cm_vec;
            std::vector<drawable::Shatter_Drawable*> drawable_vec;
            GLFWwindow *window;

            VkInstance instance;
            VkDebugReportCallbackEXT callback;
            /*
            * 表示一个可以用来展示然后渲染图形数据的对象（即表面）的句柄
            */
            VkSurfaceKHR surface;

            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
            VkDevice device;

            VkQueue graphicsQueue;
            VkQueue presentQueue;
            VkQueue computeQueue;

            VkSwapchainKHR swapChain;
            /*
            * 图像代表交换链中的项
            */
            std::vector<VkImage> swapChainImages;
            VkFormat swapChainImageFormat;
            VkExtent2D swapChainExtent;
            std::vector<VkImageView> swapChainImageviews;
            std::vector<VkFramebuffer> swapChainFramebuffers;

            VkRenderPass renderPass;
            //        VkDescriptorSetLayout descriptorSetLayout;
            //        VkPipelineLayout pipelineLayout;
            //        VkPipeline graphicsPipeline;

            VkCommandPool graphic_commandPool;
            VkCommandPool compute_commandPool;

            VkImage depthImage;
            VkDeviceMemory depthImageMemory;
            VkImageView depthImageView;

            VkDescriptorPool descriptorPool;

            std::vector<VkCommandBuffer> commandBuffers;
            VkCommandBuffer computecommandBuffer;

            VkSemaphore imageAvailableSemaphore;
            VkSemaphore renderFinishedSemaphore;

        };

    };
};


#endif //VULKAN_TOTURIOL_SHATTER_RENDER_H

