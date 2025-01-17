#pragma once

#include "sp_Debug.h"

#include <imconfig.h>
#include <imgui.h>
#include "imgui_impl_vulkan.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"
#include "imgui_stdlib.h"

class Sp_Gui {

public:

	void Start(VkCommandBuffer* cmdBuffer);
	void testGui();

	void update();

private:
	
	ImGuiIO io;
};