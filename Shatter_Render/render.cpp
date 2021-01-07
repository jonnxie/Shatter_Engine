//
// Created by maybe on 2020/11/21.
//

#include "render.h"

#include <stb_image.h>
#include <stdexcept>
#include <cstring>
#include <set>
#include <chrono>

#include <tiny_obj_loader.h>
#include "../Shatter_Drawable/shatter_drawable_include.h"


namespace shatter::render{
    bool render_created = false;
    const std::vector<const char *> validationLayers = {
            "VK_LAYER_LUNARG_standard_validation"
    };

    const std::vector<const char *> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    VkResult CreateDebugReportCallbackEXT(VkInstance instance,
                                          const VkDebugReportCallbackCreateInfoEXT *pCreateInfo,
                                          const VkAllocationCallbacks *pAllocator,
                                          VkDebugReportCallbackEXT *pCallback) {
        auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance,
                                                                               "vkCreateDebugReportCallbackEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pCallback);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void DestroyDebugReportCallbackEXT(VkInstance instance,
                                       VkDebugReportCallbackEXT callback,
                                       const VkAllocationCallbacks *pAllocator) {
        auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance,
                                                                                "vkDestroyDebugReportCallbackEXT");
        if (func != nullptr) {
            func(instance, callback, pAllocator);
        }
    }

    base_render& base_render::Get_Render(){
        static base_render render;
        if(!render_created) {
            render_created = true;
            render.Init();
        }
        return render;
    }

    void base_render::Init(){
        Init_Window();
        Init_Vulkan();
    }

    void base_render::Loop(){
        glfwPollEvents();
        Draw();
    }

    void base_render::Cleanup(){
        Cleanup_SwapChain();

//        vkDestroySampler(device, textureSampler, nullptr);
//        vkDestroyImageView(device, textureImageView, nullptr);
//
//        vkDestroyImage(device, textureImage, nullptr);
//        vkFreeMemory(device, textureImageMemory, nullptr);

        vkDestroyDescriptorPool(device, descriptorPool, nullptr);

//        vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
//        vkDestroyBuffer(device, uniformBuffer, nullptr);
//        vkFreeMemory(device, uniformBufferMemory, nullptr);
//
//        vkDestroyBuffer(device, indexBuffer, nullptr);
//        vkFreeMemory(device, indexBufferMemory, nullptr);
//
//        vkDestroyBuffer(device, vertexBuffer, nullptr);
//        vkFreeMemory(device, vertexBufferMemory, nullptr);


        vkDestroySemaphore(device, renderFinishedSemaphore, nullptr);
        vkDestroySemaphore(device, imageAvailableSemaphore, nullptr);

        vkFreeCommandBuffers(device, compute_commandPool, 1,
                             &computecommandBuffer);
        vkDestroyCommandPool(device, graphic_commandPool, nullptr);
        vkDestroyCommandPool(device, compute_commandPool, nullptr);

        vkDestroyDevice(device, nullptr);
        DestroyDebugReportCallbackEXT(instance, callback, nullptr);
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }

    void base_render::Init_Window(){
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        window = glfwCreateWindow(app::Shatter_App::Get_Screen_Width(), app::Shatter_App::Get_Screen_Height(), "Vulkan", nullptr, nullptr);

        //在此处设置了将当前对象指针存放在窗体对象中，在回调函数中取出
        glfwSetWindowUserPointer(window, this);

        //注册回调函数
        glfwSetWindowSizeCallback(window, onWindowResized);
    }

    void base_render::Init_Vulkan(){
        Create_Instance();
        Setup_DebugCallback();
        Create_Surface();
        Pick_PhysicalDevice();
        Create_LogicalDevice();
        Create_SwapChain();
        Create_ImageViews();
        Create_RenderPass();
        Create_GraphicsCommandPool();
        Create_ComputeCommandPool();
        Create_DepthResources();
        Create_Framebuffers();
//        createTextureImage();
//        createTextureImageView();
//        createTextureSampler();
//        loadModel();
//        createVertexBuffer();
//        createIndexBuffer();
//        createUniformBuffer();
/*
 * 需要在drawable的数量确定之后创建
 */
        Create_DescriptorPool();
//        createDescriptorSet();

        Create_Semaphores();
    }

    void base_render::Create_Instance(){
        if (enableValidationLayers && !Check_ValidationLayer_Support()) {
            throw std::runtime_error("validation layers requested,but not available!");
        }

        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "NJUST Project";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Shatter Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = Get_RequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
    }
    void base_render::Setup_DebugCallback(){
        if (!enableValidationLayers) return;

        VkDebugReportCallbackCreateInfoEXT createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
        createInfo.pfnCallback = debugCallback;

        if (CreateDebugReportCallbackEXT(instance, &createInfo, nullptr, &callback) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug callback!");
        }
    }
    void base_render::Create_Surface(){
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }
    void base_render::Pick_PhysicalDevice(){
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        //选定合适的device
        for (const auto &tmp_device : devices) {
            if (isDeviceSuitable(tmp_device)) {
                physicalDevice = tmp_device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }
    void base_render::Create_LogicalDevice(){
        QueueFamilyIndices indices = Find_QueueFamilies(physicalDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<int> uniqueQueueFamilies = {indices.graphicsFamily,
                                             indices.presentFamily,
                                             indices.computeFamily};

        float queuePriority = 1.0f;
        for (int queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo = {};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures = {};
        deviceFeatures.samplerAnisotropy = VK_TRUE;

        VkDeviceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

        vkGetDeviceQueue(device, indices.computeFamily, 0,&computeQueue);
        vkGetDeviceQueue(device, indices.graphicsFamily, 0, &graphicsQueue);
        vkGetDeviceQueue(device, indices.presentFamily, 0, &presentQueue);
    }
    void base_render::Create_SwapChain(){
        SwapChainSupportDetails swapChainSupport = Query_SwapChain_Support(physicalDevice);

        VkSurfaceFormatKHR surfaceFormat = Choose_SwapSurface_Format(swapChainSupport.formats);
        VkPresentModeKHR presentMode = Choose_SwapPresent_Mode(swapChainSupport.presentModes);
        VkExtent2D extent = ::chooseSwapExtent(swapChainSupport.capabilities,600,800);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if (swapChainSupport.capabilities.maxImageCount > 0 &&
            imageCount > swapChainSupport.capabilities.maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = surface;

        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = Find_QueueFamilies(physicalDevice);
        uint32_t queueFamilyIndices[] = {(uint32_t) indices.graphicsFamily,
                                         (uint32_t) indices.presentFamily};

        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;

        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
            throw std::runtime_error("failed to create swap chain!");
        }

        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;
    }
    void base_render::Create_ImageViews(){
        swapChainImageviews.resize(swapChainImages.size());
        for (size_t i = 0; i < swapChainImages.size(); i++) {
            swapChainImageviews[i] = buffer::Shatter_Texture::Create_ImageView(&device,swapChainImages[i], swapChainImageFormat,
                                                     VK_IMAGE_ASPECT_COLOR_BIT);
        }
    }
    void base_render::Create_RenderPass(){
        VkAttachmentDescription colorAttachment = {};
        colorAttachment.format = swapChainImageFormat;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentDescription depthAttachment = {};
        depthAttachment.format = Find_Depth_Format();
        depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkAttachmentReference colorAttachmentRef = {};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkAttachmentReference depthAttachmentRef = {};
        depthAttachmentRef.attachment = 1;
        depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass = {};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;
        subpass.pDepthStencilAttachment = &depthAttachmentRef;

        VkSubpassDependency dependency = {};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        std::array<VkAttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};
        VkRenderPassCreateInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        renderPassInfo.pAttachments = attachments.data();
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;

        if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
            throw std::runtime_error("failed to create render pass!");
        }
    }
    void base_render::Create_Framebuffers(){
        swapChainFramebuffers.resize(swapChainImageviews.size());

        for (size_t i = 0; i < swapChainImageviews.size(); i++) {
            std::array<VkImageView, 2> attachments = {
                    swapChainImageviews[i],
                    depthImageView
            };

            VkFramebufferCreateInfo framebufferInfo = {};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderPass;
            framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
            framebufferInfo.pAttachments = attachments.data();
            framebufferInfo.width = swapChainExtent.width;
            framebufferInfo.height = swapChainExtent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }
    void base_render::Create_GraphicsCommandPool(){
        QueueFamilyIndices queueFamilyIndices = Find_QueueFamilies(physicalDevice);

        VkCommandPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;

        if (vkCreateCommandPool(device, &poolInfo, nullptr, &graphic_commandPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create command pool!");
        }
    }

    void base_render::Create_ComputeCommandPool() {
        QueueFamilyIndices queueFamilyIndices = Find_QueueFamilies(physicalDevice);

        VkCommandPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = queueFamilyIndices.computeFamily;

        if (vkCreateCommandPool(device, &poolInfo, nullptr, &compute_commandPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create command pool!");
        }
    }

    void base_render::Create_DepthResources(){
        VkFormat depthFormat = Find_Depth_Format();

        buffer::Shatter_Texture::Create_Image(&device,
                                             swapChainExtent.width,
                                             swapChainExtent.height,
                                             depthFormat,
                                             VK_IMAGE_TILING_OPTIMAL,
                                             VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
                                             VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                                             depthImage,
                                             depthImageMemory);
        depthImageView = buffer::Shatter_Texture::Create_ImageView(&device,depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);

        buffer::Shatter_Texture::Transition_ImageLayout(depthImage,
                                                        depthFormat,
                                                        VK_IMAGE_LAYOUT_UNDEFINED,
                                                        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
    }

    void base_render::Create_DescriptorPool(){
//        std::array<VkDescriptorPoolSize, 2> poolSizes = {};
//        poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//        poolSizes[0].descriptorCount = 1;
//        poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//        poolSizes[1].descriptorCount = 1;

        VkDescriptorPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = static_cast<uint32_t>(asset::Shatter_Asset::Get_Asset().Get_DescriptorPool_Size()->size());
        poolInfo.pPoolSizes = asset::Shatter_Asset::Get_Asset().Get_DescriptorPool_Size()->data();
        poolInfo.maxSets = asset::Shatter_Asset::Get_Asset().Get_Set_Num();

        if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }
    }

    uint32_t base_render::Find_MemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties){
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) &&
                (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }
        throw std::runtime_error("failed to find suitable memory type!");
    }
    void base_render::Create_GraphicsCommandBuffers(){
        commandBuffers.resize(swapChainFramebuffers.size());

        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = graphic_commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

        if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }

        for (size_t i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo beginInfo = {};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

            vkBeginCommandBuffer(commandBuffers[i], &beginInfo);

            VkRenderPassBeginInfo renderPassInfo = {};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = renderPass;
            renderPassInfo.framebuffer = swapChainFramebuffers[i];
            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = swapChainExtent;

            std::array<VkClearValue, 2> clearValues = {};
            clearValues[0].color = {0.92f, 0.92f, 0.92f, 1.0f};
            clearValues[1].depthStencil = {1.0f, 0};

            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            for(auto& obj : drawable_vec){
                obj->Draw(commandBuffers[i]);
            }

            vkCmdEndRenderPass(commandBuffers[i]);

            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to record command buffer!");
            }
        }
    }
    void base_render::Create_ComputeCommandBuffer(){
        VkCommandBufferAllocateInfo command_buffer_allocate_info
        {
                VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
                nullptr,
                compute_commandPool,
                VK_COMMAND_BUFFER_LEVEL_PRIMARY,
                1
        };
        if (vkAllocateCommandBuffers(device, &command_buffer_allocate_info, &computecommandBuffer) != VK_SUCCESS)
        {
            throw std::runtime_error("buffer allocation failed");
        }

        // build command buffer
        VkCommandBufferBeginInfo command_buffer_begin_info
        {
                VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                nullptr,
                VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT,
                nullptr
        };
        if (vkBeginCommandBuffer(computecommandBuffer, &command_buffer_begin_info) != VK_SUCCESS)
        {
            throw std::runtime_error("command buffer begin failed");
        }

        for(auto &i : drawable_vec){
            i->Compute(computecommandBuffer);
        }

        vkEndCommandBuffer(computecommandBuffer);
    }

    void base_render::Create_Semaphores(){
        VkSemaphoreCreateInfo semaphoreInfo = {};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
            vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS) {

            throw std::runtime_error("failed to create semaphores!");
        }
    }
    void base_render::Recreate_SwapChain(){
        vkDeviceWaitIdle(device);
        Create_SwapChain();
        Create_ImageViews();
        Create_RenderPass();
        //createGraphicsPipeline();
        Create_DepthResources();
        Create_Framebuffers();
        Create_GraphicsCommandBuffers();
    }
    void base_render::Cleanup_SwapChain(){
        vkDestroyImageView(device, depthImageView, nullptr);
        vkDestroyImage(device, depthImage, nullptr);
        vkFreeMemory(device, depthImageMemory, nullptr);

        for (size_t i = 0; i < swapChainFramebuffers.size(); i++) {
            vkDestroyFramebuffer(device, swapChainFramebuffers[i], nullptr);
        }

        vkFreeCommandBuffers(device, graphic_commandPool, static_cast<uint32_t>(commandBuffers.size()),
                             commandBuffers.data());

//        vkDestroyPipeline(device, graphicsPipeline, nullptr);
//        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
        vkDestroyRenderPass(device, renderPass, nullptr);

        for (size_t i = 0; i < swapChainImageviews.size(); i++) {
            vkDestroyImageView(device, swapChainImageviews[i], nullptr);
        }

        vkDestroySwapchainKHR(device, swapChain, nullptr);
    }
    void base_render::Draw(){
        VkSubmitInfo compute_submit_info
        {
                VK_STRUCTURE_TYPE_SUBMIT_INFO,
                nullptr,
                0,
                nullptr,
                nullptr,
                1,
                &computecommandBuffer,
                0,
                nullptr
        };
        vkQueueWaitIdle(computeQueue);
        if (vkQueueSubmit(computeQueue, 1, &compute_submit_info, VK_NULL_HANDLE) != VK_SUCCESS)
        {
            throw std::runtime_error("compute queue submission failed");
        }

        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(device, swapChain, std::numeric_limits<uint64_t>::max(),
                                                imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            Recreate_SwapChain();
            return;
        } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image1");
        }

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

        VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = {swapChain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(presentQueue, &presentInfo);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
            Recreate_SwapChain();
        } else if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }

        vkQueueWaitIdle(presentQueue);
    }

    SwapChainSupportDetails base_render::Query_SwapChain_Support(VkPhysicalDevice device){
        SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device,
                                                  surface,
                                                  &presentModeCount,
                                                  nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device,
                                                      surface,
                                                      &presentModeCount,
                                                      details.presentModes.data());
        }

        return details;
    }

    VkFormat base_render::Find_Supported_Format(const std::vector<VkFormat> &candidates, VkImageTiling tiling,
                                 VkFormatFeatureFlags features){
        for (VkFormat format : candidates) {
            VkFormatProperties props;
            vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

            if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
                return format;
            } else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
                return format;
            }

            throw std::runtime_error("failed to find supported format1");
        }
    }
    VkFormat base_render::Find_Depth_Format(){
        return Find_Supported_Format(
                {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
                VK_IMAGE_TILING_OPTIMAL,
                VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
        );
    }

    bool base_render::isDeviceSuitable(VkPhysicalDevice device){
        QueueFamilyIndices indices = Find_QueueFamilies(device);

        bool extensionsSupported = Check_DeviceExtension_Support(device);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = Query_SwapChain_Support(device);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        VkPhysicalDeviceFeatures supportedFeatures;
        vkGetPhysicalDeviceFeatures(device, &supportedFeatures);

        return indices.isComplete() && extensionsSupported && supportedFeatures.samplerAnisotropy;
    }

    bool base_render::Check_DeviceExtension_Support(VkPhysicalDevice device){
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto &extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    QueueFamilyIndices base_render::Find_QueueFamilies(VkPhysicalDevice device){
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto &queueFamily : queueFamilies) {
            if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                if(indices.graphicsFamily == -1) {
                    indices.graphicsFamily = i;
                }
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if (queueFamily.queueCount > 0 && presentSupport) {
                if(indices.presentFamily == -1) {
                    indices.presentFamily = i;
                }
            }

            if(queueFamily.queueCount > 0 && queueFamily.queueFlags &
            VK_QUEUE_COMPUTE_BIT && i != indices.presentFamily){
                indices.computeFamily = i;
            }

            if (indices.isComplete()) {
                break;
            }

            i++;
        }

        return indices;
    }

    std::vector<const char *> base_render::Get_RequiredExtensions(){
        std::vector<const char *> extensions;

        unsigned int glfwExtensionCount = 0;
        const char **glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        for (unsigned int i = 0; i < glfwExtensionCount; i++) {
            extensions.push_back(glfwExtensions[i]);
        }

        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
        }

        return extensions;
    }

    VkCommandBuffer base_render::beginSingleTimeCommands(){
        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = graphic_commandPool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        return commandBuffer;
    }

    void base_render::endSingleTimeCommands(VkCommandBuffer commandBuffer){
        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(graphicsQueue);

        vkFreeCommandBuffers(device, graphic_commandPool, 1, &commandBuffer);
    }

    bool base_render::Check_ValidationLayer_Support(){
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char *layerName : validationLayers) {
            bool layerFound = false;

            for (const auto &layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }

    void base_render::onWindowResized(GLFWwindow *window, int width, int height) {
        if (width == 0 || height == 0) return;

        auto *app = reinterpret_cast<base_render *>(glfwGetWindowUserPointer(window));
        app->Recreate_SwapChain();
    }

    void base_render::AllocateDescriptorSets(const std::vector<VkDescriptorSetLayout>& des_set_layout,
                                VkDescriptorSet* set){
        VkDescriptorSetAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = des_set_layout.size();
        allocInfo.pSetLayouts = des_set_layout.data();

        if (vkAllocateDescriptorSets(device, &allocInfo, set) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor set!");
        }
    }

//    void base_render::Register_Command(cm command){
//        cm_vec.emplace_back(std::move(command));
//    }

    void base_render::Add_Drawable(drawable::Shatter_Drawable* drawable){
        drawable_vec.emplace_back(drawable);
    }
    void base_render::Create_Command_Buffer(){
        Create_GraphicsCommandBuffers();
        Create_ComputeCommandBuffer();
    }
}




