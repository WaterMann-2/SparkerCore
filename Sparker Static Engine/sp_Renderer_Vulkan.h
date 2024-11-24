#pragma once

#include "sp_Debug.h"
#include "sp_Window.h"


const bool VALIDATION_LAYERS_ENABLED = true;

const vector<const char*> RequestedLayers = { "VK_LAYER_KHRONOS_validation" };

namespace Sparker_Engine {
	namespace Renderer {
		
		class sp_Vulkan2 {

		public:


		private:



		public: // Static functions
			static void CreateInstance(VkInstance& instance, VkApplicationInfo* appInfo, VkInstanceCreateInfo* createInfo);

			static void SetupDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT& debugMesenger);

			static void CreateSurface(VkInstance& instance, VkSurfaceKHR& surface, SpWindow& window);

		private: // Static utility functions
			inline static bool checkValidationLayerSupport(vector<const char*> requestedLayers);
			inline static vector<const char*> getRequiredextensions();
			inline static VkDebugUtilsMessengerCreateInfoEXT populateDebugMessenger();
		};

	}
}