#pragma once

#include "sp_Debug.h"

#include "sp_ExitInfo.h"
#include "sp_Window.h"
#include "sp_Vulkan.h"


class sp_Exit{

public:
	
	sp_Exit(sp_ExitInfo& info, SpWindow& window, sp_Vulkan& vulkan);
};

