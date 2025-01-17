#include "sp_Queue_Families.h"

bool Sparker_Engine::Graphics::QueueFamilyIndices::isComplete() {
	return graphicsFamily.has_value() && presentFamily.has_value();
}