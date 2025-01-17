#pragma once
#include "sp_Debug.h"

namespace Sparker_Engine {
	namespace Graphics{
		struct QueueFamilyIndices {
			optional<uint32_t> graphicsFamily;
			optional<uint32_t> presentFamily;


			bool isComplete();
		};
	}
}