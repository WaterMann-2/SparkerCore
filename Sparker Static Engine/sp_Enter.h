#pragma once

#include <iostream>
#include <string>

#include <GLFW/glfw3.h>

#include "sp_EnterInfo.h"

#include "sp_Vulkan.h"
#include "sp_Window.h"

class sp_Enter{

public: 

	sp_Enter(sp_EnterInfo& info, sp_Vulkan& vulkan, SpWindow& window, SpInput& input);
};

