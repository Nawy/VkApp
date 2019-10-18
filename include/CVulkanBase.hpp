#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <vector>

class CVulkanBase {

public:
    CVulkanBase(int width, int height);
    ~CVulkanBase();

    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        pWindow = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);
    }
    void initVulkan() {
        createVkInstance();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(pWindow)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        vkDestroyInstance(vkInstance, nullptr);

        glfwDestroyWindow(pWindow);

        glfwTerminate();
    }

    void createVkInstance() {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_1;

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &vkInstance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance of Vulkan");
        }

        // count extensions
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        std::cout << "available extensions: " << std::endl;
        for(const auto& extension : extensions) {
            std::cout << "\t" << extension.extensionName << std::endl; 
        }
    }

private:
    GLFWwindow* pWindow;
    VkInstance vkInstance;
    int width;
    int height;
};