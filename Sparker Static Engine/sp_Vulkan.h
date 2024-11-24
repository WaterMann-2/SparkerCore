#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <limits>
#include <algorithm>
#include <chrono>

//#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#define GLFW_EXPOSE_NATIVE_WIN32
//#include <GLFW/glfw3native.h>
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vulkan/vulkan.h>

#include "sp_Debug.h"
#include "sp_VkStructs.h"
#include "sp_Window.h"
#include "sp_Utility.h"
#include "sp_Primitive.h"
#include "Camera.h"
#include "sp_Renderer_Vulkan.h"

using std::uint32_t;
using std::string;
using std::vector;
using std::to_string;
using sp_Utility::ReadFile;


#ifdef _DEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif // !_DEBUG


#define debugCallback SpDebug::VkDebugCallback

const vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

const vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

const std::vector<Vertex> vertices = {
	{{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0, 0}},
    {{0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}, {0, 0}},
    {{0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {0, 0}},
    {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 1.0f}, {0, 0}},
	{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0, 0}},
	{{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0, 0}},
	{{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0, 0}},
	{{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0, 0}}
};
const std::vector<uint32_t> indices = {
	0, 1, 2, 2, 3, 0,
	3, 2, 6, 6, 7, 3,
	0, 3, 4, 4, 3, 7,
	5, 4, 6, 4, 7, 6, 
	1, 5, 2, 2, 5, 6,
	0, 4, 5, 5, 1, 0
};

const int MAX_FRAMES_IN_FLIGHT = 3;

class sp_Vulkan{

public:

	Camera* cam;

	void vulkanStart(SpWindow iWindow);
	void vulkanCleanup();

	void drawFrame();

private:
	SpWindow window;
	GLFWwindow* glWindow;

	uint32_t extensionCount = 0;
	VkInstance instance;

	VkDebugUtilsMessengerEXT debugMessenger;

	VkPhysicalDevice physicalDevice;
	VkDevice device;

	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkSurfaceKHR surface;

	VkSwapchainKHR Swapchain;
	vector<VkImage> swapchainImages;
	VkFormat swapchainImageFormat;
	VkExtent2D swapchainExtent;

	vector<VkImageView> swapchainImageViews;

	VkRenderPass renderPass;
	VkDescriptorSetLayout descriptorSetLayout;
	VkDescriptorPool descriptorPool;
	vector<VkDescriptorSet> descriptorSets;
	VkPipelineLayout pipelineLayout;

	VkPipeline graphicsPipeline;
	vector<VkFramebuffer> swapchainFramebuffers;

	VkCommandPool commandPool;
	vector<VkCommandBuffer> commandBuffers;

	vector<VkSemaphore> imageAvailableSemaphores, renderFinishedSemaphores;
	vector<VkFence> inFlightFences;

	uint32_t currentFrame = 0;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;

	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	vector<VkBuffer> uniformBuffers;
	vector<VkDeviceMemory> uniformBuffersMemory;
	vector<void*> uniformBuffersMapped;


	//Startup

	bool checkValidationLayerSupport();
	void createInstance();
	static vector<const char*> getRequiredExtensions(bool debug);

	//Surface
	
	void createSurface();

	//Debug

	static void populateDebugMessenger(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	void setupDebugMessenger();
	static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

	static void DestroyDebugUtilsMessengerEXT( VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

	//Picking hardware

	void pickPhysicalDevice();
	bool isSuitableDevice(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	// Virtual Device

	void createLogicalDevice();


	//swapchain

	void createSwapchain();
	void recreateSwapchain();
	void cleanupSwapchain();

	SwapchainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilitites);

	//Image Views

	void createImageViews();
	inline void destroyImageViews();

	//Graphics pipeline

	void createGraphicsPipeline();
	VkShaderModule createShaderModule(const vector<char>& code);

	void createDescriptorSetLayout();
	

	void createRenderPass();
	void createFramebuffers();
	inline void destroyFramebuffers();

	void createCommandPool();
	void createCommandBuffer();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	void createSyncObjects();
	inline void destroySyncObjects();

	//Drawing
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void createVertexBuffer();
	void createIndexBuffer();

	void createDescriptorPool();
	void createDescriptorSets();

	void createUniformBuffers();
	void updateUniformBuffer(uint32_t currentImage);
	inline void cleanupUniformBuffers();

	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	void createTextureImage();


};


namespace _sp_Vulkan {

	class Swapchain {
	public:

	public:
		VkSwapchainKHR* createSwapchain(VkDevice& srcDevice, VkPhysicalDevice& srcPhysicalDevice, VkSurfaceKHR& srcSurface, GLFWwindow*& window);

		void recreateSwapchain(VkDevice& srcDevice, VkPhysicalDevice& srcPhysicalDevice, VkSurfaceKHR& srcSurface);

	private:
		bool hasBeenCreated = false;

		VkDevice* device;
		VkPhysicalDevice* physicalDevice;
		VkSurfaceKHR* surface;
		GLFWwindow* window;

		SwapchainSupportDetails pSwapSupport;
		VkSurfaceFormatKHR pSurfaceFormat;
		VkPresentModeKHR pPresentMode;
		VkExtent2D pExtent;

		VkSwapchainKHR swapchain;
		vector<VkImage> swapchainImages;

		SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice& physDevice);
		
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const vector<VkSurfaceFormatKHR>& availableFormats);

		VkPresentModeKHR chooseSwapPresentMode(const vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice& physDevice);
	};
}